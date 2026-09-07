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

import com.cws.extra.test.Camera
import com.cws.extra.test.ExtraComponents
import com.cws.extra.test.Movement
import com.cws.extra.test.camera
import com.cws.extra.test.movement
import kotlin.test.BeforeTest
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertNotNull
import kotlin.test.assertTrue

class ComponentStorageTest {

    private lateinit var scene: Scene

    @BeforeTest
    fun setup() {
        // Safe bounded allocation context
        ExtraComponents.registerAll()
        scene = Scene(entityCount = 32)
    }

    @Test
    fun `test generated scene extension properties resolve to correct primitive lists`() {
        val entity = scene.createEntity()

        // Add through the standard generic scene API
        scene.add(entity, Movement(speed = 45.0f))
        scene.add(entity, Camera(fov = 90.0f))

        // 1. Verify that the sugar extensions can read data directly from the scene context
        val movementList = scene.movement
        val cameraList = scene.camera

        assertNotNull(movementList)
        assertNotNull(cameraList)
        assertEquals(1, movementList.size)
        assertEquals(1, cameraList.size)

        // 2. Look up the index via storage to verify data values match up perfectly
        val moveIdx = scene.get<Movement>(entity)

        assertEquals(45.0f, movementList.speed[moveIdx])
    }

    @Test
    fun `test pools exist only for registered storage slots`() {
        assertEquals(scene.components.storages.size, scene.components.pools.size)

        var populatedPools = 0
        scene.components.storages.indices.forEach { index ->
            val storage = scene.components.storages[index]
            val pool = scene.components.pools[index]
            assertEquals(storage != null, pool != null, "Pool and storage must match at registry slot $index")
            if (pool != null) populatedPools++
        }

        assertEquals(7, populatedPools)
        assertEquals(scene.components.pools.size - populatedPools, scene.components.pools.count { it == null })
    }

    @Test
    fun `test storage add method type safety guards against invalid casts`() {
        val entity = scene.createEntity()

        // Crucial test: Pass an illegal component type (Camera) into MovementStorage
        scene.components.add(ComponentId<Movement>(), entity, Camera(fov = 60.0f))

        // Verify that the operation was cleanly ignored and no components were registered
        assertFalse(scene.has<Movement>(entity))
        assertEquals(0, scene.movement.size)
    }

    @Test
    fun `test component addition overwrites existing values instead of appending duplicates`() {
        val entity = scene.createEntity()

        // 1. Initial assignment
        scene.add(entity, Movement(speed = 10.0f))
        val initialMoveIdx = scene.get<Movement>(entity)
        assertEquals(1, scene.movement.size)
        assertEquals(10.0f, scene.movement.speed[initialMoveIdx])

        // 2. Re-assign/Update the component for the exact same entity
        // This should trigger the generated 'else { list[componentIndex] = c }' block
        scene.add(entity, Movement(speed = 25.0f))
        val updatedMoveIdx = scene.get<Movement>(entity)

        // 3. Structural validation
        assertEquals(1, scene.movement.size, "List size must NOT grow when updating an existing component")
        assertEquals(initialMoveIdx, updatedMoveIdx, "The entity's data slot index must remain identical")
        assertEquals(25.0f, scene.movement.speed[updatedMoveIdx], "The primitive value inside the list must update cleanly")
    }

    @Test
    fun `test cross storage removal safety does not corrupt neighboring lists`() {
        val entity = scene.createEntity()

        scene.add(entity, Movement(12.0f))
        scene.add(entity, Camera(45.0f))

        // Delete only movement component
        scene.remove<Movement>(entity)

        // Verify isolation boundaries
        assertFalse(scene.has<Movement>(entity))
        assertEquals(0, scene.movement.size)

        // Camera components must remain completely unbothered
        assertTrue(scene.has<Camera>(entity))
        assertEquals(1, scene.camera.size)
    }
}
