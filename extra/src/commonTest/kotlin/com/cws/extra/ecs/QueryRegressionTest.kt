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

import com.cws.extra.lists.IntList
import com.cws.extra.test.Camera
import com.cws.extra.test.CameraList
import com.cws.extra.test.ExtraComponents
import com.cws.extra.test.Movement
import com.cws.extra.test.MovementList
import com.cws.extra.test.Renderable
import com.cws.extra.test.RenderableList
import com.cws.extra.test.Velocity
import com.cws.extra.test.VelocityList
import kotlin.test.BeforeTest
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertNotEquals
import kotlin.test.assertTrue

class QueryRegressionTest {

    private lateinit var scene: Scene

    @BeforeTest
    fun setup() {
        ExtraComponents.registerAll()
        scene = Scene(entityCount = 2)
    }

    @Test
    fun `pool version changes only for successful structural mutations`() {
        val pool = scene.components.getPoolUnsafe<Movement>()
        val initial = pool.structuralVersion
        val entity = scene.create(Movement(1f))
        val added = pool.structuralVersion

        scene.add(entity, Movement(2f))
        assertEquals(added, pool.structuralVersion)

        scene.remove<Movement>(entity)
        val removed = pool.structuralVersion
        scene.remove<Movement>(entity)

        assertNotEquals(initial, added)
        assertNotEquals(added, removed)
        assertEquals(removed, pool.structuralVersion)
    }

    @Test
    fun `all streaming terminals observe add and remove without materializing`() {
        val query = scene.query<Movement, MovementList>()
        val e0 = scene.create(Movement(10f))
        val e1 = scene.create(Movement(20f))

        var first = EntityNull
        query.first { entity, _, _ -> first = entity }
        assertEquals(e1, first)
        assertTrue(query.any())
        assertTrue(query.all { _, movements, i -> movements.speed[i] >= 10f })
        assertEquals(e0, query.last())
        assertEquals(2, query.count())
        assertEquals(null, query.__indices)

        scene.remove<Movement>(e1)
        assertEquals(1, query.count())
        assertEquals(e0, query.random())
        assertEquals(null, query.__indices)
    }

    @Test
    fun `copy terminals refresh materialized indices after dense swap removal`() {
        val e0 = scene.create(Movement(10f))
        val e1 = scene.create(Movement(20f))
        val e2 = scene.create(Movement(30f))
        val query = scene.query<Movement, MovementList>().reverse()

        scene.remove<Movement>(e1)

        val entities = query.copyEntitiesTo(IntList())
        assertEquals(setOf(e0, e2), entities.array.copyOf(entities.size).toSet())
        assertEquals(2, query.copyIndicesTo(IntList()).size)
    }

    @Test
    fun `materialized transformations are discarded by structural refresh`() {
        scene.create(Movement(30f))
        scene.create(Movement(10f))
        val query = scene.query<Movement, MovementList>()
            .filter { _, movements, i -> movements.speed[i] < 20f }
            .take(1)

        assertEquals(1, query.count())
        scene.create(Movement(40f))

        assertEquals(3, query.count())
    }

    @Test
    fun `cached sparse arrays refresh after capacity growth`() {
        val query = scene.query<Movement, MovementList>()
        repeat(32) { scene.create(Movement(it.toFloat())) }

        assertEquals(32, query.count())
        assertTrue(query.__entities === query.p.componentToEntity.array)
    }

    @Test
    fun `query becomes empty after scene clear`() {
        repeat(8) { scene.create(Movement(it.toFloat())) }
        val query = scene.query<Movement, MovementList>().take(4)

        scene.clear()

        assertTrue(query.isEmpty())
        assertEquals(0, query.count())
        assertEquals(0, query.__indices?.size)
    }

    @Test
    fun `query three refreshes every participating pool`() {
        val e0 = scene.create(Movement(1f), Velocity(1f, 1f, 1f), Camera(90f))
        val e1 = scene.create(Movement(2f), Velocity(2f, 2f, 2f))
        val query = scene.query<Movement, MovementList>()
            .with<Velocity, VelocityList>()
            .with<Camera, CameraList>()

        assertEquals(1, query.count())
        scene.add(e1, Camera(80f))
        assertEquals(2, query.count())
        scene.remove<Velocity>(e0)
        assertEquals(1, query.count())
    }

    @Test
    fun `query four refreshes materialized indices`() {
        val e0 = scene.create(Movement(1f), Velocity(1f, 1f, 1f), Camera(90f), Renderable(1))
        val e1 = scene.create(Movement(2f), Velocity(2f, 2f, 2f), Camera(80f), Renderable(2))
        val query = scene.query<Movement, MovementList>()
            .with<Velocity, VelocityList>()
            .with<Camera, CameraList>()
            .with<Renderable, RenderableList>()
            .take(1)

        scene.remove<Renderable>(e0)

        assertEquals(1, query.count())
        assertEquals(e1, query.random())
        assertEquals(-1, query.copyEntitiesTo(IntList()).findIndex { it == e0 })
    }
}
