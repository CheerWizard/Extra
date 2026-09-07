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

import com.cws.extra.memory.IExtraList
import com.cws.extra.lists.IntList
import kotlinx.coroutines.coroutineScope
import kotlinx.coroutines.launch
import kotlin.math.min

/**
 * A query for entities that have components of type [T1], [T2], [T3], and [T4].
 */
class Query4<
    T1, L1 : IExtraList,
    T2, L2 : IExtraList,
    T3, L3 : IExtraList,
    T4, L4 : IExtraList,
>(
    @PublishedApi
    internal val scene: Scene,
    @PublishedApi
    internal val id1: Int,
    @PublishedApi
    internal val id2: Int,
    @PublishedApi
    internal val id3: Int,
    @PublishedApi
    internal val id4: Int,
) {

    @PublishedApi
    internal val p1: ComponentPool
    @PublishedApi
    internal val c1: L1

    @PublishedApi
    internal val p2: ComponentPool
    @PublishedApi
    internal val c2: L2

    @PublishedApi
    internal val p3: ComponentPool
    @PublishedApi
    internal val c3: L3

    @PublishedApi
    internal val p4: ComponentPool
    @PublishedApi
    internal val c4: L4

    @PublishedApi
    internal var dp: ComponentPool

    @PublishedApi
    internal var __indices: IntList? = null
    @PublishedApi
    internal var __size: Int = 0

    @PublishedApi
    internal var __entities: IntArray
    @PublishedApi
    internal var __e1: IntArray
    @PublishedApi
    internal var __e2: IntArray
    @PublishedApi
    internal var __e3: IntArray
    @PublishedApi
    internal var __e4: IntArray
    @PublishedApi internal var __version1: Int
    @PublishedApi internal var __version2: Int
    @PublishedApi internal var __version3: Int
    @PublishedApi internal var __version4: Int

    @PublishedApi
    internal inline fun componentIndex(
        pool: ComponentPool,
        entityToComponent: IntArray,
        entity: Int,
        driverIndex: Int,
    ): Int = if (pool === dp) driverIndex else entityToComponent[entity]

    init {
        val s1 = ComponentRegistry.getRegistrationIndex(id1)
        p1 = scene.components.getPoolUnsafe(s1)
        c1 = scene.components.storages[s1]!!.list as L1

        val s2 = ComponentRegistry.getRegistrationIndex(id2)
        p2 = scene.components.getPoolUnsafe(s2)
        c2 = scene.components.storages[s2]!!.list as L2

        val s3 = ComponentRegistry.getRegistrationIndex(id3)
        p3 = scene.components.getPoolUnsafe(s3)
        c3 = scene.components.storages[s3]!!.list as L3

        val s4 = ComponentRegistry.getRegistrationIndex(id4)
        p4 = scene.components.getPoolUnsafe(s4)
        c4 = scene.components.storages[s4]!!.list as L4

        dp = when {
            p1.size <= p2.size &&
                    p1.size <= p3.size &&
                    p1.size <= p4.size -> p1

            p2.size <= p3.size &&
                    p2.size <= p4.size -> p2

            p3.size <= p4.size -> p3

            else -> p4
        }
        __size = dp.size
        __entities = dp.componentToEntity.array
        __e1 = p1.entityToComponent.array
        __e2 = p2.entityToComponent.array
        __e3 = p3.entityToComponent.array
        __e4 = p4.entityToComponent.array
        __version1 = p1.structuralVersion
        __version2 = p2.structuralVersion
        __version3 = p3.structuralVersion
        __version4 = p4.structuralVersion
    }

    @PublishedApi
    internal fun refreshIfNeeded() {
        if (__version1 == p1.structuralVersion && __version2 == p2.structuralVersion && __version3 == p3.structuralVersion && __version4 == p4.structuralVersion) return
        refresh()
    }

    @PublishedApi
    internal fun ensureIndices(forceRefresh: Boolean = false): IntList {
        if (!forceRefresh) refreshIfNeeded()
        if (!forceRefresh) __indices?.let { return it }
        val indices = __indices ?: IntList(__size).also { __indices = it }
        indices.ensureCapacity(__size)
        indices.clear()
        for (i in __size - 1 downTo 0) {
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            val i3 = componentIndex(p3, __e3, entity, i)
            val i4 = componentIndex(p4, __e4, entity, i)
            if (i1 != ComponentNull &&
                i2 != ComponentNull &&
                i3 != ComponentNull &&
                i4 != ComponentNull
            ) {
                indices.add(i)
            }
        }
        return indices
    }

    /** Forces a rebuild from current pool state. Materialized ordering/filtering is discarded. */
    fun refresh(): Query4<T1, L1, T2, L2, T3, L3, T4, L4> {
        __version1 = p1.structuralVersion
        __version2 = p2.structuralVersion
        __version3 = p3.structuralVersion
        __version4 = p4.structuralVersion
        dp = when {
            p1.size <= p2.size &&
                    p1.size <= p3.size &&
                    p1.size <= p4.size -> p1

            p2.size <= p3.size &&
                    p2.size <= p4.size -> p2

            p3.size <= p4.size -> p3

            else -> p4
        }
        __size = dp.size
        __entities = dp.componentToEntity.array
        __e1 = p1.entityToComponent.array
        __e2 = p2.entityToComponent.array
        __e3 = p3.entityToComponent.array
        __e4 = p4.entityToComponent.array
        if (__indices != null) ensureIndices(forceRefresh = true)
        return this
    }

    inline fun <reified T5, reified L5 : IExtraList> with() =
        Query5<T1, L1, T2, L2, T3, L3, T4, L4, T5, L5>(scene, id1, id2, id3, id4, ComponentId<T5>())

    fun without1(): Query3<T2, L2, T3, L3, T4, L4> = Query3(scene, id2, id3, id4)
    fun without2(): Query3<T1, L1, T3, L3, T4, L4> = Query3(scene, id1, id3, id4)
    fun without3(): Query3<T1, L1, T2, L2, T4, L4> = Query3(scene, id1, id2, id4)
    fun without4(): Query3<T1, L1, T2, L2, T3, L3> = Query3(scene, id1, id2, id3)

    inline fun filter(predicate: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int, c3: L3, i3: Int, c4: L4, i4: Int) -> Boolean): Query4<T1, L1, T2, L2, T3, L3, T4, L4> {
        val c1 = c1
        val c2 = c2
        val c3 = c3
        val c4 = c4
        ensureIndices().filterWith { i ->
            val entity = __entities[i]
            predicate(entity, c1, componentIndex(p1, __e1, entity, i), c2, componentIndex(p2, __e2, entity, i), c3, componentIndex(p3, __e3, entity, i), c4, componentIndex(p4, __e4, entity, i))
        }
        return this
    }

    inline fun <R : Comparable<R>> sortedBy(
        crossinline selector: (
            entity: Int,
            c1: L1, i1: Int,
            c2: L2, i2: Int,
            c3: L3, i3: Int,
            c4: L4, i4: Int,
        ) -> R
    ): Query4<T1, L1, T2, L2, T3, L3, T4, L4> {
        val list = ensureIndices()
        val c1 = c1
        val c2 = c2
        val c3 = c3
        val c4 = c4
        list.sortWith { iA, iB ->
            val entityA = __entities[iA]
            val i1A = componentIndex(p1, __e1, entityA, iA)
            val i2A = componentIndex(p2, __e2, entityA, iA)
            val i3A = componentIndex(p3, __e3, entityA, iA)
            val i4A = componentIndex(p4, __e4, entityA, iA)

            val entityB = __entities[iB]
            val i1B = componentIndex(p1, __e1, entityB, iB)
            val i2B = componentIndex(p2, __e2, entityB, iB)
            val i3B = componentIndex(p3, __e3, entityB, iB)
            val i4B = componentIndex(p4, __e4, entityB, iB)

            selector(entityA, c1, i1A, c2, i2A, c3, i3A, c4, i4A)
                .compareTo(selector(entityB, c1, i1B, c2, i2B, c3, i3B, c4, i4B))
        }
        return this
    }


    inline fun sortedByInt(crossinline selector: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int, c3: L3, i3: Int, c4: L4, i4: Int) -> Int): Query4<T1, L1, T2, L2, T3, L3, T4, L4> {
        val list = ensureIndices()
        val c1 = c1
        val c2 = c2
        val c3 = c3
        val c4 = c4
        list.sortByInt { i ->
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            val i3 = componentIndex(p3, __e3, entity, i)
            val i4 = componentIndex(p4, __e4, entity, i)
            selector(entity, c1, i1, c2, i2, c3, i3, c4, i4)
        }
        return this
    }

    inline fun sortedByLong(crossinline selector: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int, c3: L3, i3: Int, c4: L4, i4: Int) -> Long): Query4<T1, L1, T2, L2, T3, L3, T4, L4> {
        val list = ensureIndices()
        val c1 = c1
        val c2 = c2
        val c3 = c3
        val c4 = c4
        list.sortByLong { i ->
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            val i3 = componentIndex(p3, __e3, entity, i)
            val i4 = componentIndex(p4, __e4, entity, i)
            selector(entity, c1, i1, c2, i2, c3, i3, c4, i4)
        }
        return this
    }

    inline fun sortedByFloat(crossinline selector: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int, c3: L3, i3: Int, c4: L4, i4: Int) -> Float): Query4<T1, L1, T2, L2, T3, L3, T4, L4> {
        val list = ensureIndices()
        val c1 = c1
        val c2 = c2
        val c3 = c3
        val c4 = c4
        list.sortByFloat { i ->
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            val i3 = componentIndex(p3, __e3, entity, i)
            val i4 = componentIndex(p4, __e4, entity, i)
            selector(entity, c1, i1, c2, i2, c3, i3, c4, i4)
        }
        return this
    }

    inline fun sortedByDouble(crossinline selector: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int, c3: L3, i3: Int, c4: L4, i4: Int) -> Double): Query4<T1, L1, T2, L2, T3, L3, T4, L4> {
        val list = ensureIndices()
        val c1 = c1
        val c2 = c2
        val c3 = c3
        val c4 = c4
        list.sortByDouble { i ->
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            val i3 = componentIndex(p3, __e3, entity, i)
            val i4 = componentIndex(p4, __e4, entity, i)
            selector(entity, c1, i1, c2, i2, c3, i3, c4, i4)
        }
        return this
    }

    fun reverse(): Query4<T1, L1, T2, L2, T3, L3, T4, L4> {
        val list = ensureIndices()
        var i = 0
        var j = list.size - 1
        while (i < j) {
            val temp = list.array[i]
            list.array[i] = list.array[j]
            list.array[j] = temp
            i++
            j--
        }
        return this
    }

    fun take(n: Int): Query4<T1, L1, T2, L2, T3, L3, T4, L4> {
        val indices = ensureIndices()
        if (indices.size > n) {
            indices.size = n
        }
        return this
    }

    fun limit(n: Int) = take(n)

    inline fun first(
        block: (
            entity: Int,
            c1: L1, i1: Int,
            c2: L2, i2: Int,
            c3: L3, i3: Int,
            c4: L4, i4: Int,
        ) -> Unit
    ): Query4<T1, L1, T2, L2, T3, L3, T4, L4> {
        refreshIfNeeded()
        val indices = __indices
        val c1 = c1
        val c2 = c2
        val c3 = c3
        val c4 = c4
        val size = indices?.size ?: __size
        for (idx in 0 until size) {
            val i = indices?.get(idx) ?: (size - 1 - idx)
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            val i3 = componentIndex(p3, __e3, entity, i)
            val i4 = componentIndex(p4, __e4, entity, i)
            if (i1 != ComponentNull && i2 != ComponentNull && i3 != ComponentNull && i4 != ComponentNull) {
                block(entity, c1, i1, c2, i2, c3, i3, c4, i4)
                break
            }
        }
        return this
    }

    @PublishedApi
    internal inline fun forEachUnfiltered(block: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int, c3: L3, i3: Int, c4: L4, i4: Int) -> Unit): Query4<T1, L1, T2, L2, T3, L3, T4, L4> {
        val indices = __indices
        val c1 = c1
        val c2 = c2
        val c3 = c3
        val c4 = c4
        val size = indices?.size ?: __size
        for (idx in 0 until size) {
            val i = indices?.get(idx) ?: (size - 1 - idx)
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            val i3 = componentIndex(p3, __e3, entity, i)
            val i4 = componentIndex(p4, __e4, entity, i)
            if (i1 != ComponentNull && i2 != ComponentNull && i3 != ComponentNull && i4 != ComponentNull) {
                block(entity, c1, i1, c2, i2, c3, i3, c4, i4)
            }
        }
        return this
    }


    inline fun forEach(
        block: (
            entity: Int,
            c1: L1, i1: Int,
            c2: L2, i2: Int,
            c3: L3, i3: Int,
            c4: L4, i4: Int,
        ) -> Unit
    ): Query4<T1, L1, T2, L2, T3, L3, T4, L4> {
        refreshIfNeeded()
        if (__indices == null) return forEachUnfiltered(block)
        val indices = __indices
        val c1 = c1
        val c2 = c2
        val c3 = c3
        val c4 = c4
        val size = indices?.size ?: __size
        for (idx in 0 until size) {
            val i = indices?.get(idx) ?: (size - 1 - idx)
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            val i3 = componentIndex(p3, __e3, entity, i)
            val i4 = componentIndex(p4, __e4, entity, i)
            if (i1 != ComponentNull && i2 != ComponentNull && i3 != ComponentNull && i4 != ComponentNull) {
                block(
                    entity,
                    c1, i1,
                    c2, i2,
                    c3, i3,
                    c4, i4,
                )
            }
        }
        return this
    }


    /**
     * Iterates matching entries whose inline [predicate] returns true.
     * The predicate is inlined into the traversal and does not materialize or mutate the query.
     */
    inline fun forEachWhere(
        predicate: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int, c3: L3, i3: Int, c4: L4, i4: Int) -> Boolean,
        block: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int, c3: L3, i3: Int, c4: L4, i4: Int) -> Unit,
    ): Query4<T1, L1, T2, L2, T3, L3, T4, L4> {
        forEach { entity, c1, i1, c2, i2, c3, i3, c4, i4 ->
            if (predicate(entity, c1, i1, c2, i2, c3, i3, c4, i4)) {
                block(entity, c1, i1, c2, i2, c3, i3, c4, i4)
            }
        }
        return this
    }

    /** Returns true when [predicate] is true for every matching entry. */
    inline fun all(predicate: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int, c3: L3, i3: Int, c4: L4, i4: Int) -> Boolean): Boolean {
        forEach { entity, c1, i1, c2, i2, c3, i3, c4, i4 ->
            if (!predicate(entity, c1, i1, c2, i2, c3, i3, c4, i4)) return false
        }
        return true
    }

    /** Returns the last entity in query iteration order, or [EntityNull] when empty. */
    inline fun last(): Int {
        var result = EntityNull
        forEach { entity, _, _, _, _, _, _, _, _ -> result = entity }
        return result
    }

    /** Executes [block] for each matching entity in parallel. */
    suspend fun forEachParallel(
        chunkSize: Int = 1024,
        block: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int, c3: L3, i3: Int, c4: L4, i4: Int) -> Unit
    ): Query4<T1, L1, T2, L2, T3, L3, T4, L4> {
        refreshIfNeeded()
        val indices = __indices
        val c1 = c1
        val c2 = c2
        val c3 = c3
        val c4 = c4
        val size = indices?.size ?: __size
        coroutineScope {
            for (start in 0 until size step chunkSize) {
                val end = min(start + chunkSize, size)
                launch {
                    for (idx in start until end) {
                        val i = indices?.get(idx) ?: (size - 1 - idx)
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            val i3 = componentIndex(p3, __e3, entity, i)
            val i4 = componentIndex(p4, __e4, entity, i)
                        if (i1 != ComponentNull && i2 != ComponentNull && i3 != ComponentNull && i4 != ComponentNull) {
                            block(entity, c1, i1, c2, i2, c3, i3, c4, i4)
                        }
                    }
                }
            }
        }
        return this
    }

    /** Returns true if any entity matches the query. */
    inline fun any(): Boolean {
        refreshIfNeeded()
        val indices = __indices
        val c1 = c1
        val c2 = c2
        val c3 = c3
        val c4 = c4
        val size = indices?.size ?: __size
        for (idx in 0 until size) {
            val i = indices?.get(idx) ?: (size - 1 - idx)
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            val i3 = componentIndex(p3, __e3, entity, i)
            val i4 = componentIndex(p4, __e4, entity, i)
            if (i1 != ComponentNull && i2 != ComponentNull && i3 != ComponentNull && i4 != ComponentNull) return true
        }
        return false
    }

    /** Returns true if no entities match the query. */
    inline fun isEmpty(): Boolean = !any()

    /** Returns the number of entities matching the query. */
    inline fun count(): Int {
        var count = 0
        forEach { _, _, _, _, _, _, _, _, _ -> count++ }
        return count
    }

    /** Finds the entity with the minimum value selected by [selector]. Returns -1 if no matches. */
    inline fun <R : Comparable<R>> minEntity(crossinline selector: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int, c3: L3, i3: Int, c4: L4, i4: Int) -> R): Int {
        var minEntity = -1
        var minValue: R? = null
        forEach { entity, c1, i1, c2, i2, c3, i3, c4, i4 ->
            val value = selector(entity, c1, i1, c2, i2, c3, i3, c4, i4)
            val currentMin = minValue
            if (currentMin == null || value < currentMin) {
                minValue = value
                minEntity = entity
            }
        }
        return minEntity
    }

    /** Finds the entity with the maximum value selected by [selector]. Returns -1 if no matches. */
    inline fun <R : Comparable<R>> maxEntity(crossinline selector: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int, c3: L3, i3: Int, c4: L4, i4: Int) -> R): Int {
        var maxEntity = -1
        var maxValue: R? = null
        forEach { entity, c1, i1, c2, i2, c3, i3, c4, i4 ->
            val value = selector(entity, c1, i1, c2, i2, c3, i3, c4, i4)
            val currentMax = maxValue
            if (currentMax == null || value > currentMax) {
                maxValue = value
                maxEntity = entity
            }
        }
        return maxEntity
    }

    /** Shuffles the internal iteration order. */
    fun shuffle(): Query4<T1, L1, T2, L2, T3, L3, T4, L4> {
        ensureIndices().shuffle()
        return this
    }


    /** Copies matching entity IDs into [destination], which can be reused by the caller. */
    fun copyEntitiesTo(destination: IntList, clear: Boolean = true): IntList {
        refreshIfNeeded()
        if (clear) destination.clear()
        val indices = __indices
        if (indices != null) {
            destination.ensureCapacity(destination.size + indices.size)
            for (index in 0 until indices.size) {
                destination.addUnsafe(__entities[indices[index]])
            }
            return destination
        }
        forEach { entity, _, _, _, _, _, _, _, _ -> destination.add(entity) }
        return destination
    }

    /** Copies matching driver-pool indices into [destination]. */
    fun copyIndicesTo(destination: IntList, clear: Boolean = true): IntList {
        refreshIfNeeded()
        if (clear) destination.clear()
        val indices = __indices
        if (indices != null) {
            destination.addAll(indices)
            return destination
        }
        forEach { _, _, i1, _, i2, _, i3, _, i4 ->
            destination.add(if (dp === p1) i1 else if (dp === p2) i2 else if (dp === p3) i3 else i4)
        }
        return destination
    }


    /** Picks a random entity from the matching set. Returns -1 if empty. */
    fun random(): Int {
        refreshIfNeeded()
        val indices = __indices
        if (indices != null) {
            if (indices.size == 0) return EntityNull
            return __entities[indices[kotlin.random.Random.nextInt(indices.size)]]
        }
        var selected = EntityNull
        var seen = 0
        forEach { entity, _, _, _, _, _, _, _, _ ->
            seen++
            if (kotlin.random.Random.nextInt(seen) == 0) selected = entity
        }
        return selected
    }

    /** Returns a new [IntList] containing all matching entity IDs. */
    fun toEntities(): IntList {
        val result = IntList()
        forEach { entity, _, _, _, _, _, _, _, _ -> result.add(entity) }
        return result
    }

}
