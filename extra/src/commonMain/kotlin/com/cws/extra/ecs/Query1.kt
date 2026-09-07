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
 * A query for entities that have a specific component type [T].
 */
class Query1<T, L : IExtraList>(
    @PublishedApi
    internal val scene: Scene,
    @PublishedApi
    internal val id: Int,
) {

    @PublishedApi
    internal val p: ComponentPool
    @PublishedApi
    internal val c: L

    @PublishedApi
    internal var __indices: IntList? = null
    @PublishedApi
    internal var __size: Int = 0
    @PublishedApi
    internal var __entities: IntArray
    @PublishedApi
    internal var __version: Int

    init {
        val s1 = ComponentRegistry.getRegistrationIndex(id)
        p = scene.components.getPoolUnsafe(s1)
        c = scene.components.storages[s1]!!.list as L
        __size = p.size
        __entities = p.componentToEntity.array
        __version = p.structuralVersion
    }

    @PublishedApi
    internal fun refreshIfNeeded() {
        if (__version == p.structuralVersion) return
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
            indices.add(i)
        }
        return indices
    }

    /** Forces a rebuild from current pool state. Materialized ordering/filtering is discarded. */
    fun refresh(): Query1<T, L> {
        __version = p.structuralVersion
        __size = p.size
        __entities = p.componentToEntity.array
        if (__indices != null) ensureIndices(forceRefresh = true)
        return this
    }

    inline fun <reified T2, reified L2 : IExtraList> with() =
        Query2<T, L, T2, L2>(scene, id, ComponentId<T2>())

    inline fun filter(predicate: (entity: Int, c1: L, i1: Int) -> Boolean): Query1<T, L> {
        val c = c
        ensureIndices().filterWith { i -> predicate(__entities[i], c, i) }
        return this
    }

    inline fun <R : Comparable<R>> sortedBy(crossinline selector: (entity: Int, c: L, i: Int) -> R): Query1<T, L> {
        val list = ensureIndices()
        val c = c
        list.sortWith { iA, iB ->
            val entityA = __entities[iA]
            val entityB = __entities[iB]
            selector(entityA, c, iA).compareTo(selector(entityB, c, iB))
        }
        return this
    }


    inline fun sortedByInt(crossinline selector: (entity: Int, c: L, i: Int) -> Int): Query1<T, L> {
        val list = ensureIndices()
        val c = c
        list.sortByInt { i ->
            selector(__entities[i], c, i)
        }
        return this
    }

    inline fun sortedByLong(crossinline selector: (entity: Int, c: L, i: Int) -> Long): Query1<T, L> {
        val list = ensureIndices()
        val c = c
        list.sortByLong { i ->
            selector(__entities[i], c, i)
        }
        return this
    }

    inline fun sortedByFloat(crossinline selector: (entity: Int, c: L, i: Int) -> Float): Query1<T, L> {
        val list = ensureIndices()
        val c = c
        list.sortByFloat { i ->
            selector(__entities[i], c, i)
        }
        return this
    }

    inline fun sortedByDouble(crossinline selector: (entity: Int, c: L, i: Int) -> Double): Query1<T, L> {
        val list = ensureIndices()
        val c = c
        list.sortByDouble { i ->
            selector(__entities[i], c, i)
        }
        return this
    }

    fun reverse(): Query1<T, L> {
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

    /** Limits the number of entities in the result set to [n]. */
    fun take(n: Int): Query1<T, L> {
        val indices = ensureIndices()
        if (indices.size > n) {
            indices.size = n
        }
        return this
    }

    /** Alias for [take]. */
    fun limit(n: Int) = take(n)

    inline fun first(block: (entity: Int, c: L, i: Int) -> Unit): Query1<T, L> {
        refreshIfNeeded()
        val indices = __indices
        val c = c
        val size = indices?.size ?: __size
        for (idx in 0 until size) {
            val i = indices?.get(idx) ?: (size - 1 - idx)
            val entity = __entities[i]
            block(entity, c, i)
            break
        }
        return this
    }

    inline fun forEach(block: (entity: Int, c: L, i: Int) -> Unit): Query1<T, L> {
        refreshIfNeeded()
        val indices = __indices
        val c = c
        val size = indices?.size ?: __size
        for (idx in 0 until size) {
            val i = indices?.get(idx) ?: (size - 1 - idx)
            val entity = __entities[i]
            block(entity, c, i)
        }
        return this
    }


    /**
     * Iterates matching entries whose inline [predicate] returns true.
     * The predicate is inlined into the traversal and does not materialize or mutate the query.
     */
    inline fun forEachWhere(
        predicate: (entity: Int, c: L, i: Int) -> Boolean,
        block: (entity: Int, c: L, i: Int) -> Unit,
    ): Query1<T, L> {
        forEach { entity, c, i ->
            if (predicate(entity, c, i)) {
                block(entity, c, i)
            }
        }
        return this
    }

    /** Returns true when [predicate] is true for every matching entry. */
    inline fun all(predicate: (entity: Int, c: L, i: Int) -> Boolean): Boolean {
        forEach { entity, c, i ->
            if (!predicate(entity, c, i)) return false
        }
        return true
    }

    /** Returns the last entity in query iteration order, or [EntityNull] when empty. */
    inline fun last(): Int {
        var result = EntityNull
        forEach { entity, _, _ -> result = entity }
        return result
    }

    /** Executes [block] for each matching entity in parallel. */
    suspend fun forEachParallel(
        chunkSize: Int = 1024,
        block: (entity: Int, c: L, i: Int) -> Unit
    ): Query1<T, L> {
        refreshIfNeeded()
        val indices = __indices
        val c = c
        val size = indices?.size ?: __size
        coroutineScope {
            for (start in 0 until size step chunkSize) {
                val end = min(start + chunkSize, size)
                launch {
                    for (idx in start until end) {
                        val i = indices?.get(idx) ?: (size - 1 - idx)
            val entity = __entities[i]
                        block(entity, c, i)
                    }
                }
            }
        }
        return this
    }

    /** Returns true if any entity matches the query. */
    inline fun any(): Boolean {
        refreshIfNeeded()
        return (__indices?.size ?: __size) != 0
    }

    /** Returns true if no entities match the query. */
    inline fun isEmpty(): Boolean = !any()

    /** Returns the number of entities matching the query. */
    inline fun count(): Int {
        var count = 0
        forEach { _, _, _ -> count++ }
        return count
    }

    /** Finds the entity with the minimum value selected by [selector]. Returns -1 if no matches. */
    inline fun <R : Comparable<R>> minEntity(crossinline selector: (entity: Int, c: L, i: Int) -> R): Int {
        var minEntity = -1
        var minValue: R? = null
        forEach { entity, c, i ->
            val value = selector(entity, c, i)
            val currentMin = minValue
            if (currentMin == null || value < currentMin) {
                minValue = value
                minEntity = entity
            }
        }
        return minEntity
    }

    /** Finds the entity with the maximum value selected by [selector]. Returns -1 if no matches. */
    inline fun <R : Comparable<R>> maxEntity(crossinline selector: (entity: Int, c: L, i: Int) -> R): Int {
        var maxEntity = -1
        var maxValue: R? = null
        forEach { entity, c, i ->
            val value = selector(entity, c, i)
            val currentMax = maxValue
            if (currentMax == null || value > currentMax) {
                maxValue = value
                maxEntity = entity
            }
        }
        return maxEntity
    }

    /** Shuffles the internal iteration order. */
    fun shuffle(): Query1<T, L> {
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
        forEach { entity, _, _ -> destination.add(entity) }
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
        forEach { _, _, i -> destination.add(i) }
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
        forEach { entity, _, _ ->
            seen++
            if (kotlin.random.Random.nextInt(seen) == 0) selected = entity
        }
        return selected
    }

    /** Returns a new [IntList] containing all matching entity IDs. */
    fun toEntities(): IntList {
        val result = IntList()
        forEach { entity, _, _ -> result.add(entity) }
        return result
    }

}
