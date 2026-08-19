/*
 * Copyright 2026 CheerWizard
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.cws.extra.ecs

import com.cws.extra.io.File
import com.cws.extra.io.flush
import com.cws.extra.io.read
import com.cws.extra.io.use
import com.cws.extra.io.write
import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import com.cws.extra.memory.flip
import com.cws.extra.test.Camera
import com.cws.extra.test.Movement
import com.cws.extra.test.cameras
import com.cws.extra.test.movements
import kotlinx.coroutines.test.runTest
import kotlin.test.BeforeTest
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertNotNull
import kotlin.test.assertTrue

class SceneSerializationTest {

    private lateinit var sourceScene: Scene

    @BeforeTest
    fun setup() {
        // Allocate a dedicated source scene 
        sourceScene = Scene(capacity = 32)
    }

    @Test
    fun `test complete scene binary serialization round trip integration`() = runTest {
        // 1. Populate initial complex scene structure with unique IDs and scattered components
        val e0 = sourceScene.createEntity() // ID 0
        val e1 = sourceScene.createEntity() // ID 1
        val e2 = sourceScene.createEntity() // ID 2

        sourceScene.add(e0, Movement(speed = 14.5f))
        sourceScene.add(e1, Movement(99.0f))
        sourceScene.add(e1, Camera(fov = 110.0f))
        sourceScene.add(e2, Camera(fov = 45.0f))

        // 2. Kill an entity to intentionally fragment the inner state trackers 
        // This populates the internal 'removedEntities' recycler stack
        sourceScene.removeEntity(e0)

        // 3. Serialize our active scene context to a binary NativeBuffer array
        val serializedBuffer = sourceScene.encode()
        
        assertNotNull(serializedBuffer)
        assertTrue(serializedBuffer.limit > 0)

        // 4. Simulate saving/loading payload to disk via raw bytes
        File("test.scene").use {
            // serialize
            serializedBuffer.flip()
            write(serializedBuffer)

            // deserialize
            val deserializedBuffer = NativeBuffer(size)
            read(deserializedBuffer)
            deserializedBuffer.flip()

            // --- THE DECODING PHASE ---
            val decodedScene = deserializedBuffer.decodeScene()

            // 5. METRIC & STATE VALIDATION
            // Verify structural identity parameters matched up exactly
            assertEquals(sourceScene.entities.size, decodedScene.entities.size, "Active entity count must match")

            // Verify entity id recycler stack recovered properly (Entity 0 must be inside)
            assertFalse(decodedScene.entities.array.contains(0), "Entity 0 should be inactive")

            // Spawn a fresh entity on the deserialized scene. It must reuse ID 0 from the recycled stack!
            val recycledEntityId = decodedScene.createEntity()
            assertEquals(0, recycledEntityId, "Deserialized scene must retain entityId recycling state pools")

            // 6. QUERY & DATA CONSISTENCY CHECK
            // Run your custom generic loops on the recovered scene to ensure component lists match up
            var queryRuns = 0
            decodedScene.forEach<Movement, Camera> { entity, moveIdx, camIdx ->
                assertEquals(e1, entity, "Matching multi-component entity ID must remain identical")

                // Fetch direct values via sugar list extensions from the recovered buffers
                val recoveredSpeed = decodedScene.movements.speed[moveIdx]
                val recoveredFov = decodedScene.cameras.fov[camIdx]

                assertEquals(99.0f, recoveredSpeed)
                assertEquals(110.0f, recoveredFov)
                queryRuns++
            }
            assertEquals(1, queryRuns, "Query processing loops must yield identical execution histories on recovered scenes")
        }
    }
}