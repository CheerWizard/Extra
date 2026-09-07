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
import com.cws.extra.test.ExtraComponents
import com.cws.extra.test.Movement
import com.cws.extra.test.MovementList
import com.cws.extra.test.Velocity
import com.cws.extra.test.VelocityList
import kotlinx.atomicfu.atomic
import kotlinx.coroutines.test.runTest
import kotlin.test.BeforeTest
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertNotNull
import kotlin.test.assertTrue

class QueryTest {

    private lateinit var scene: Scene

    @BeforeTest
    fun setup() {
        ExtraComponents.registerAll()
        scene = Scene(entityCount = 64)
    }

    @Test
    fun `test query filter`() {
        scene.create(Movement(10f))
        scene.create(Movement(20f))
        scene.create(Movement(30f))

        val count = scene.query<Movement, MovementList>()
            .filter { _, list, i -> list.speed[i] > 15f }
            .count()

        assertEquals(2, count)
    }

    @Test
    fun `test query filter mutates materialized indices and preserves order`() {
        scene.create(Movement(30f))
        scene.create(Movement(10f))
        scene.create(Movement(20f))

        val query = scene.query<Movement, MovementList>()
            .sortedByFloat { _, movements, i -> movements.speed[i] }
            .filter { _, movements, i -> movements.speed[i] >= 20f }
            .take(1)

        val entities = query.copyEntitiesTo(IntList())
        assertEquals(listOf(2), entities.array.copyOf(entities.size).toList())

        repeat(20) {
            assertEquals(2, query.random())
        }
    }

    @Test
    fun `test query sortedBy`() {
        scene.create(Movement(30f))
        scene.create(Movement(10f))
        scene.create(Movement(20f))

        val sortedSpeeds = mutableListOf<Float>()
        scene.query<Movement, MovementList>()
            .sortedBy { _, list, i -> list.speed[i] }
            .forEach { _, list, i ->
                sortedSpeeds.add(list.speed[i])
            }

        assertEquals(listOf(10f, 20f, 30f), sortedSpeeds)
    }

    @Test
    fun `test query reverse`() {
        scene.create(Movement(10f))
        scene.create(Movement(20f))
        scene.create(Movement(30f))

        val reversedIds = mutableListOf<Int>()
        scene.query<Movement, MovementList>()
            .reverse()
            .forEach { entity, _, _ ->
                reversedIds.add(entity)
            }

        // Default order is 2, 1, 0 (downTo 0 in ensureIndices)
        // Reversed should be 0, 1, 2
        assertEquals(listOf(0, 1, 2), reversedIds)
    }

    @Test
    fun `test query take and limit`() {
        repeat(10) { scene.create(Movement(it.toFloat())) }

        val count = scene.query<Movement, MovementList>()
            .take(3)
            .count()

        assertEquals(3, count)
    }

    @Test
    fun `test query first`() {
        scene.create(Movement(10f))
        scene.create(Movement(20f))

        var foundSpeed = -1f
        scene.query<Movement, MovementList>()
            .filter { _, list, i -> list.speed[i] > 15f }
            .first { _, list, i ->
                foundSpeed = list.speed[i]
            }

        assertEquals(20f, foundSpeed)
    }

    @Test
    fun `test query all last and forEachWhere`() {
        scene.create(Movement(10f))
        scene.create(Movement(20f))
        scene.create(Movement(30f))

        val query = scene.query<Movement, MovementList>()
        val selected = mutableListOf<Float>()

        query.forEachWhere(
            predicate = { _, list, i -> list.speed[i] >= 20f },
            block = { _, list, i -> selected.add(list.speed[i]) },
        )

        assertEquals(listOf(30f, 20f), selected)
        assertTrue(query.all { _, list, i -> list.speed[i] >= 10f })
        assertFalse(query.all { _, list, i -> list.speed[i] > 10f })
        assertEquals(0, query.last())
        assertEquals(EntityNull, scene.query<Movement, MovementList>().take(0).last())
    }

    @Test
    fun `test scene query traversal`() {
        scene.create(Movement(10f), Velocity(1f, 2f, 3f))
        scene.create(Movement(20f))
        scene.create(Movement(30f), Velocity(4f, 5f, 6f))

        val speeds = mutableListOf<Float>()
        scene.query<Movement, MovementList, Velocity, VelocityList>().forEach {
                _, movements, movementIndex, _, _ ->
            speeds.add(movements.speed[movementIndex])
        }

        assertEquals(listOf(30f, 10f), speeds)
    }

    @Test
    fun `test primitive sorting destinations and random`() {
        scene.create(Movement(30f))
        scene.create(Movement(10f))
        scene.create(Movement(20f))

        val query = scene.query<Movement, MovementList>()
            .sortedByInt { _, movements, index -> movements.speed[index].toInt() }

        val entities = query.copyEntitiesTo(IntList())
        val indices = query.copyIndicesTo(IntList())

        assertEquals(listOf(1, 2, 0), entities.array.copyOf(entities.size).toList())
        assertEquals(listOf(1, 2, 0), indices.array.copyOf(indices.size).toList())
        assertTrue(query.random() in 0..2)
    }

    @Test
    fun `test query any and isEmpty`() {
        val query = scene.query<Movement, MovementList>()
        
        assertTrue(query.isEmpty())
        assertFalse(query.any())

        scene.create(Movement(10f))
        query.refresh()

        assertFalse(query.isEmpty())
        assertTrue(query.any())
    }

    @Test
    fun `test first and any do not materialize query`() {
        scene.create(Movement(10f))
        scene.create(Movement(20f))

        val query = scene.query<Movement, MovementList>()
        var firstEntity = EntityNull

        assertTrue(query.any())
        query.first { entity, _, _ -> firstEntity = entity }

        assertEquals(1, firstEntity)
        assertEquals(null, query.__indices)
    }

    @Test
    fun `test query refreshes automatically after structural changes`() {
        val query = scene.query<Movement, MovementList>()

        assertEquals(0, query.count())

        scene.create(Movement(10f))
        scene.create(Movement(20f))

        assertEquals(2, query.count())
    }

    @Test
    fun `test materialized query rebuilds automatically`() {
        scene.create(Movement(10f))
        val query = scene.query<Movement, MovementList>().take(1)

        scene.create(Movement(20f))

        assertEquals(2, query.count())
        assertEquals(2, query.__indices?.size)
    }

    @Test
    fun `test multi component query refreshes and changes driver pool`() {
        val e0 = scene.create(Movement(10f), Velocity(1f, 1f, 1f))
        val e1 = scene.create(Movement(20f))
        val e2 = scene.create(Movement(30f))
        val query = scene.query<Movement, MovementList>()
            .with<Velocity, VelocityList>()

        assertEquals(1, query.count())
        assertTrue(query.dp === query.p2)

        scene.add(e1, Velocity(2f, 2f, 2f))
        scene.add(e2, Velocity(3f, 3f, 3f))
        assertEquals(3, query.count())

        scene.remove<Movement>(e0)

        assertEquals(2, query.count())
        assertTrue(query.dp === query.p1)
    }

    @Test
    fun `test query minEntity and maxEntity`() {
        scene.create(Movement(30f)) // e0
        scene.create(Movement(10f)) // e1
        scene.create(Movement(20f)) // e2

        val minId = scene.query<Movement, MovementList>()
            .minEntity { _, list, i -> list.speed[i] }
        
        val maxId = scene.query<Movement, MovementList>()
            .maxEntity { _, list, i -> list.speed[i] }

        assertEquals(1, minId)
        assertEquals(0, maxId)
    }

    @Test
    fun `test query shuffle and random`() {
        repeat(10) { scene.create(Movement(it.toFloat())) }

        val query = scene.query<Movement, MovementList>()
        val randomEntity = query.random()
        
        assertTrue(randomEntity in 0..9)
        
        query.shuffle()
        
        assertTrue(query.any())
    }

    @Test
    fun `test forEachParallel`() = runTest {
        repeat(100) { scene.create(Movement(it.toFloat())) }

        val processedCount = atomic(0)
        val query = scene.query<Movement, MovementList>()
        query.forEachParallel(chunkSize = 10) { _, _, _ ->
                processedCount.incrementAndGet()
            }

        assertEquals(100, processedCount.value)
        assertEquals(null, query.__indices)
    }

    @Test
    fun `test toEntities`() {
        val e0 = scene.create(Movement(10f))
        val e1 = scene.create(Movement(20f))

        val entities = scene.query<Movement, MovementList>().toEntities()
        
        assertEquals(2, entities.size)
        assertNotNull(entities.find { it == e0 })
        assertNotNull(entities.find { it == e1 })
    }
}
