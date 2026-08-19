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
import com.cws.extra.test.Movement
import kotlin.test.BeforeTest
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertNotEquals
import kotlin.test.assertTrue

class ECSTest {

    private lateinit var scene: Scene

    @BeforeTest
    fun setup() {
        // Pre-allocate a safe fixed boundary capacity
        scene = Scene(capacity = 32)
    }

    @Test
    fun `test sequential entity id generation`() {
        val e0 = scene.createEntity()
        val e1 = scene.createEntity()
        val e2 = scene.createEntity()

        // Verify ID sequence grows predictably matching indices
        assertEquals(0, e0)
        assertEquals(1, e1)
        assertEquals(2, e2)
        assertEquals(3, scene.entities.size)
    }

    @Test
    fun `test entity id recycling via primitive pop stack`() {
        val e0 = scene.createEntity() // 0
        val e1 = scene.createEntity() // 1
        val e2 = scene.createEntity() // 2

        // Kill the middle entity (ID 1)
        // This pushes ID 1 onto the recycledIds stack and swaps ID 2 in scene.entities
        scene.removeEntity(e1)

        // Verify active entities state
        assertEquals(2, scene.entities.size)
        assertFalse(scene.entities.array.contains(1))

        // Spawn a new entity: it MUST pop and reuse the dead ID 1 instead of incrementing to 3
        val recycledEntity = scene.createEntity()
        assertEquals(1, recycledEntity, "The engine should have recycled ID 1 using the LIFO stack")
        assertEquals(3, scene.entities.size)
    }

    @Test
    fun `test multi component query filter loop with recycled ids`() {
        val e0 = scene.createEntity() // 0
        val e1 = scene.createEntity() // 1

        scene.add(e0, Movement(5.0f))
        scene.add(e1, Movement(10.0f))
        scene.add(e1, Camera(90.0f))

        // Remove entity 0 to trigger internal swaps
        scene.removeEntity(e0)

        // Verify that our generic forEach queries still target entity 1 flawlessly
        var queryRuns = 0
        scene.forEach<Movement, Camera> { entity, moveIdx, camIdx ->
            assertEquals(e1, entity)
            assertNotEquals(ComponentNull, moveIdx)
            assertNotEquals(ComponentNull, camIdx)
            queryRuns++
        }
        assertEquals(1, queryRuns, "The query should precisely capture the remaining matching entity")
    }

    @Test
    fun `test full scene reset via clear clears id tracker state`() {
        scene.createEntity()
        scene.createEntity()

        scene.clear()

        assertEquals(0, scene.entities.size)

        // After a full clear, the ID counter resets back to 0
        val freshEntity = scene.createEntity()
        assertEquals(0, freshEntity)
    }

    @Test
    fun `test removing the last added entity does not break backpointers`() {
        val e0 = scene.createEntity()
        val e1 = scene.createEntity()

        scene.add(e0, Movement(1f))
        scene.add(e1, Movement(2f)) // e1 is at the very end of MovementStorage dense list

        // Remove the last element directly (No-swap execution path)
        scene.remove<Movement>(e1)

        // Verify e0 is completely untouched and e1 is safely marked null
        assertTrue(scene.has<Movement>(e0))
        assertFalse(scene.has<Movement>(e1))

        val storage = scene.registry[getComponentID<Movement>()]
        assertEquals(0, storage.index(e0))
        assertEquals(ComponentNull, storage.index(e1))
    }

    @Test
    fun `test multiple component deletions and complex swap shuffles`() {
        val e0 = scene.createEntity()
        val e1 = scene.createEntity()
        val e2 = scene.createEntity()

        // Populate all with movements
        scene.add(e0, Movement(10f)) // dense index 0
        scene.add(e1, Movement(20f)) // dense index 1
        scene.add(e2, Movement(30f)) // dense index 2

        // Delete e0 (triggers swap: e2 moves to index 0)
        scene.remove<Movement>(e0)

        val storage = scene.registry[getComponentID<Movement>()]
        assertEquals(0, storage.index(e2)) // e2 must gracefully take slot 0
        assertEquals(1, storage.index(e1)) // e1 must remain completely unaffected at slot 1

        // Now delete e2 from its new shifted position (triggers swap: e1 moves to index 0)
        scene.remove<Movement>(e2)
        assertEquals(0, storage.index(e1)) // e1 now shifts down to slot 0 safely
    }

    @Test
    fun `test double entity deletion safety guard`() {
        val e0 = scene.createEntity()
        scene.removeEntity(e0)

        // Act of deleting it a second time should be a safe no-op or gracefully handled
        // If it isn't guarded, e0 would append to recycledIds TWICE, causing duplicate IDs later!
        scene.removeEntity(e0)

        // Let's verify our recycledIds stack didn't get polluted with duplicates
        scene.createEntity() // Should return e0

        // If double-deletion wasn't guarded, the next createEntity would STILL return e0 again,
        // giving two active allocations the exact same ID!
        val nextEntity = scene.createEntity()
        assertNotEquals(e0, nextEntity, "Engine must prevent duplicate IDs via double-deletion tracking")
    }

    @Test
    fun `test dynamic component removal during forEach structural execution`() {
        val e0 = scene.createEntity()
        val e1 = scene.createEntity()

        scene.add(e0, Movement(1f))
        scene.add(e1, Movement(2f))

        var loopCount = 0
        scene.forEach<Movement> { entity, moveIdx ->
            loopCount++
            if (entity == e0) {
                // Entity strips its own component mid-flight!
                scene.remove<Movement>(entity)
            }
        }

        // The loop should still execute completely without throwing index out of bounds exceptions
        assertEquals(2, loopCount)
        assertFalse(scene.has<Movement>(e0))
    }

    @Test
    fun `test backward forEach iteration prevents skipped entities when deleting past elements`() {
        // Create 4 sequential entities: 0, 1, 2, 3
        val e0 = scene.createEntity() // 0
        val e1 = scene.createEntity() // 1
        val e2 = scene.createEntity() // 2
        val e3 = scene.createEntity() // 3

        // Attach components so they are caught by the query
        scene.add(e0, Movement(10f))
        scene.add(e1, Movement(20f))
        scene.add(e2, Movement(30f))
        scene.add(e3, Movement(40f))

        val processedEntities = mutableListOf<Int>()

        // Execute backward query loop
        scene.forEach<Movement> { entity, moveIdx ->
            processedEntities.add(entity)

            // When we reach entity 2, delete a PAST element (entity 3 was already processed)
            // Under a forward loop, this would swap entity 0 into index 3 and skip it!
            if (entity == e2) {
                scene.removeEntity(e3)
            }
        }

        // Verify that every single active, surviving entity was processed!
        // (e3 was processed first because it's backward, e2 next, then e1 and e0)
        assertEquals(4, processedEntities.size, "All 4 entities should be visited before deletion alters the remaining history")
        assertTrue(processedEntities.contains(e0), "Entity 0 must NOT be skipped!")
        assertTrue(processedEntities.contains(e1), "Entity 1 must NOT be skipped!")
        assertTrue(processedEntities.contains(e2), "Entity 2 must NOT be skipped!")
        assertTrue(processedEntities.contains(e3), "Entity 3 must be processed before its deletion!")
    }

    @Test
    fun `test backward forEach iteration handles self deletion without skipping neighbors`() {
        val e0 = scene.createEntity()
        val e1 = scene.createEntity()
        val e2 = scene.createEntity()

        scene.add(e0, Movement(1f))
        scene.add(e1, Movement(2f))
        scene.add(e2, Movement(3f))

        val processedEntities = mutableListOf<Int>()

        scene.forEach<Movement> { entity, moveIdx ->
            processedEntities.add(entity)

            // The middle entity deletes itself mid-flight
            if (entity == e1) {
                scene.removeEntity(entity)
            }
        }

        // Verify that the self-deletion did not break the iteration of the remaining past elements
        assertTrue(processedEntities.contains(e2), "Entity 2 should be processed")
        assertTrue(processedEntities.contains(e1), "Entity 1 should be processed")
        assertTrue(processedEntities.contains(e0), "Entity 0 should not be skipped due to entity 1's self-deletion")
    }

    @Test
    fun `test backward forEach iteration handles future element deletion safely`() {
        val e0 = scene.createEntity()
        val e1 = scene.createEntity()
        val e2 = scene.createEntity()

        scene.add(e0, Movement(1f))
        scene.add(e1, Movement(2f))
        scene.add(e2, Movement(3f))

        val processedEntities = mutableListOf<Int>()

        scene.forEach<Movement> { entity, moveIdx ->
            processedEntities.add(entity)

            // When processing the last element (e2), delete a future element (e0, which is at the beginning of the list)
            if (entity == e2) {
                scene.removeEntity(e0)
            }
        }

        // Entity 0 was removed before the loop could reach it backward, so it should not be in the final list
        assertFalse(processedEntities.contains(e0), "Entity 0 should have been cleanly intercepted and omitted")
        assertTrue(processedEntities.contains(e1), "Entity 1 should still be processed normally")
    }
}