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
import com.cws.extra.test.CameraList
import com.cws.extra.test.ExtraComponents
import com.cws.extra.test.Movement
import com.cws.extra.test.MovementList
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
        ExtraComponents.registerAll()
        scene = Scene(entityCount = 32)
    }

    @Test
    fun `test sequential entity id generation`() {
        val e0 = scene.createEntity()
        val e1 = scene.createEntity()
        val e2 = scene.createEntity()

        assertEquals(0, e0)
        assertEquals(1, e1)
        assertEquals(2, e2)
        assertEquals(3, scene.entities.size)
    }

    @Test
    fun `test entity id recycling`() {
        val e0 = scene.createEntity()
        val e1 = scene.createEntity()
        val e2 = scene.createEntity()

        scene.removeEntity(e1)

        assertEquals(2, scene.entities.size)
        assertFalse(scene.entities.has(e1))

        val recycledEntity = scene.createEntity()
        assertEquals(e1, recycledEntity)
        assertEquals(3, scene.entities.size)
    }

    @Test
    fun `test multi component query filter loop with recycled ids`() {
        val e0 = scene.createEntity()
        val e1 = scene.createEntity()

        scene.add(e0, Movement(5.0f))
        scene.add(e1, Movement(10.0f))
        scene.add(e1, Camera(90.0f))

        scene.removeEntity(e0)

        var queryRuns = 0
        scene.query<Movement, MovementList, Camera, CameraList>().forEach { entity, _, _, _, _ ->
            assertEquals(e1, entity)
            queryRuns++
        }
        assertEquals(1, queryRuns)
    }

    @Test
    fun `test full scene reset via clear clears id tracker state`() {
        scene.createEntity()
        scene.createEntity()

        scene.clear()

        assertEquals(0, scene.entities.size)

        val freshEntity = scene.createEntity()
        assertEquals(0, freshEntity)
    }

    @Test
    fun `test removing the last added entity does not break backpointers`() {
        val e0 = scene.createEntity()
        val e1 = scene.createEntity()

        scene.add(e0, Movement(1f))
        scene.add(e1, Movement(2f))

        scene.remove<Movement>(e1)

        assertTrue(scene.has<Movement>(e0))
        assertFalse(scene.has<Movement>(e1))

        val pool = scene.components.getPoolUnsafe<Movement>()
        assertEquals(0, pool.getComponentIndex(e0))
        assertEquals(ComponentNull, pool.getComponentIndex(e1))
    }

    @Test
    fun `test multiple component deletions and complex swap shuffles`() {
        val e0 = scene.createEntity()
        val e1 = scene.createEntity()
        val e2 = scene.createEntity()

        scene.add(e0, Movement(10f))
        scene.add(e1, Movement(20f))
        scene.add(e2, Movement(30f))

        scene.remove<Movement>(e0)

        val pool = scene.components.getPoolUnsafe<Movement>()
        assertEquals(0, pool.getComponentIndex(e2))
        assertEquals(1, pool.getComponentIndex(e1))

        scene.remove<Movement>(e2)
        assertEquals(0, pool.getComponentIndex(e1))
    }

    @Test
    fun `multi component membership and entity removal use component pools`() {
        val entity = scene.create(Movement(4f), Camera(80f))

        assertTrue(scene.has<Movement, Camera>(entity))

        scene.removeEntity(entity)

        assertFalse(scene.has<Movement>(entity))
        assertFalse(scene.has<Camera>(entity))
        assertFalse(scene.has<Movement, Camera>(entity))
    }

    @Test
    fun `test double entity deletion safety guard`() {
        val e0 = scene.createEntity()
        scene.removeEntity(e0)
        scene.removeEntity(e0)

        val r0 = scene.createEntity()
        assertEquals(e0, r0)

        val nextEntity = scene.createEntity()
        assertNotEquals(e0, nextEntity)
    }

    @Test
    fun `test dynamic component removal during query iteration`() {
        val e0 = scene.create(Movement(1f))
        val e1 = scene.create(Movement(2f))

        var loopCount = 0
        scene.query<Movement, MovementList>().forEach { entity, _, _ ->
            loopCount++
            if (entity == e0) {
                scene.remove<Movement>(entity)
            }
        }

        assertEquals(2, loopCount)
        assertFalse(scene.has<Movement>(e0))
    }

}
