package com.cws.extra.ecs

import com.cws.extra.memory.IExtraList
import com.cws.extra.lists.IntList
import kotlinx.coroutines.coroutineScope
import kotlinx.coroutines.launch
import kotlin.math.min

/**
 * A query for entities that have components of type [T1] and [T2].
 */
class Query2<
    T1, L1 : IExtraList,
    T2, L2 : IExtraList,
>(
    @PublishedApi
    internal val scene: Scene,
    @PublishedApi
    internal val id1: Int,
    @PublishedApi
    internal val id2: Int
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
    internal var __version1: Int
    @PublishedApi
    internal var __version2: Int

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

        dp = if (p1.size <= p2.size) p1 else p2
        __size = dp.size
        __entities = dp.componentToEntity.array
        __e1 = p1.entityToComponent.array
        __e2 = p2.entityToComponent.array
        __version1 = p1.structuralVersion
        __version2 = p2.structuralVersion
    }

    @PublishedApi
    internal fun refreshIfNeeded() {
        if (__version1 == p1.structuralVersion && __version2 == p2.structuralVersion) return
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
            if (i1 != ComponentNull && i2 != ComponentNull) {
                indices.add(i)
            }
        }
        return indices
    }

    /** Forces a rebuild from current pool state. Materialized ordering/filtering is discarded. */
    fun refresh(): Query2<T1, L1, T2, L2> {
        __version1 = p1.structuralVersion
        __version2 = p2.structuralVersion
        dp = if (p1.size <= p2.size) p1 else p2
        __size = dp.size
        __entities = dp.componentToEntity.array
        __e1 = p1.entityToComponent.array
        __e2 = p2.entityToComponent.array
        if (__indices != null) ensureIndices(forceRefresh = true)
        return this
    }

    inline fun <reified T3, reified L3 : IExtraList> with() =
        Query3<T1, L1, T2, L2, T3, L3>(scene, id1, id2, ComponentId<T3>())

    fun without1(): Query1<T2, L2> = Query1(scene, id2)
    fun without2(): Query1<T1, L1> = Query1(scene, id1)

    inline fun filter(predicate: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int) -> Boolean): Query2<T1, L1, T2, L2> {
        val c1 = c1
        val c2 = c2
        ensureIndices().filterWith { i ->
            val entity = __entities[i]
            predicate(entity, c1, componentIndex(p1, __e1, entity, i), c2, componentIndex(p2, __e2, entity, i))
        }
        return this
    }

    inline fun <R : Comparable<R>> sortedBy(crossinline selector: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int) -> R): Query2<T1, L1, T2, L2> {
        val list = ensureIndices()
        val c1 = c1
        val c2 = c2
        list.sortWith { iA, iB ->
            val entityA = __entities[iA]
            val i1A = componentIndex(p1, __e1, entityA, iA)
            val i2A = componentIndex(p2, __e2, entityA, iA)

            val entityB = __entities[iB]
            val i1B = componentIndex(p1, __e1, entityB, iB)
            val i2B = componentIndex(p2, __e2, entityB, iB)

            selector(entityA, c1, i1A, c2, i2A).compareTo(selector(entityB, c1, i1B, c2, i2B))
        }
        return this
    }


    inline fun sortedByInt(crossinline selector: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int) -> Int): Query2<T1, L1, T2, L2> {
        val list = ensureIndices()
        val c1 = c1
        val c2 = c2
        list.sortByInt { i ->
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            selector(entity, c1, i1, c2, i2)
        }
        return this
    }

    inline fun sortedByLong(crossinline selector: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int) -> Long): Query2<T1, L1, T2, L2> {
        val list = ensureIndices()
        val c1 = c1
        val c2 = c2
        list.sortByLong { i ->
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            selector(entity, c1, i1, c2, i2)
        }
        return this
    }

    inline fun sortedByFloat(crossinline selector: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int) -> Float): Query2<T1, L1, T2, L2> {
        val list = ensureIndices()
        val c1 = c1
        val c2 = c2
        list.sortByFloat { i ->
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            selector(entity, c1, i1, c2, i2)
        }
        return this
    }

    inline fun sortedByDouble(crossinline selector: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int) -> Double): Query2<T1, L1, T2, L2> {
        val list = ensureIndices()
        val c1 = c1
        val c2 = c2
        list.sortByDouble { i ->
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            selector(entity, c1, i1, c2, i2)
        }
        return this
    }

    fun reverse(): Query2<T1, L1, T2, L2> {
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

    fun take(n: Int): Query2<T1, L1, T2, L2> {
        val indices = ensureIndices()
        if (indices.size > n) {
            indices.size = n
        }
        return this
    }

    fun limit(n: Int) = take(n)

    inline fun first(block: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int) -> Unit): Query2<T1, L1, T2, L2> {
        refreshIfNeeded()
        val indices = __indices
        val c1 = c1
        val c2 = c2
        val size = indices?.size ?: __size
        for (idx in 0 until size) {
            val i = indices?.get(idx) ?: (size - 1 - idx)
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            if (i1 != ComponentNull && i2 != ComponentNull) {
                block(entity, c1, i1, c2, i2)
                break
            }
        }
        return this
    }

    @PublishedApi
    internal inline fun forEachUnfiltered(block: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int) -> Unit): Query2<T1, L1, T2, L2> {
        val indices = __indices
        val c1 = c1
        val c2 = c2
        val size = indices?.size ?: __size
        for (idx in 0 until size) {
            val i = indices?.get(idx) ?: (size - 1 - idx)
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            if (i1 != ComponentNull && i2 != ComponentNull) {
                block(entity, c1, i1, c2, i2)
            }
        }
        return this
    }

    inline fun forEach(block: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int) -> Unit): Query2<T1, L1, T2, L2> {
        refreshIfNeeded()
        return forEachUnfiltered(block)
    }


    /**
     * Iterates matching entries whose inline [predicate] returns true.
     * The predicate is inlined into the traversal and does not materialize or mutate the query.
     */
    inline fun forEachWhere(
        predicate: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int) -> Boolean,
        block: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int) -> Unit,
    ): Query2<T1, L1, T2, L2> {
        forEach { entity, c1, i1, c2, i2 ->
            if (predicate(entity, c1, i1, c2, i2)) {
                block(entity, c1, i1, c2, i2)
            }
        }
        return this
    }

    /** Returns true when [predicate] is true for every matching entry. */
    inline fun all(predicate: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int) -> Boolean): Boolean {
        forEach { entity, c1, i1, c2, i2 ->
            if (!predicate(entity, c1, i1, c2, i2)) return false
        }
        return true
    }

    /** Returns the last entity in query iteration order, or [EntityNull] when empty. */
    inline fun last(): Int {
        var result = EntityNull
        forEach { entity, _, _, _, _ -> result = entity }
        return result
    }

    /** Executes [block] for each matching entity in parallel. */
    suspend fun forEachParallel(
        chunkSize: Int = 1024,
        block: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int) -> Unit
    ): Query2<T1, L1, T2, L2> {
        refreshIfNeeded()
        val indices = __indices
        val c1 = c1
        val c2 = c2
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
                        if (i1 != ComponentNull && i2 != ComponentNull) {
                            block(entity, c1, i1, c2, i2)
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
        val size = indices?.size ?: __size
        for (idx in 0 until size) {
            val i = indices?.get(idx) ?: (size - 1 - idx)
            val entity = __entities[i]
            val i1 = componentIndex(p1, __e1, entity, i)
            val i2 = componentIndex(p2, __e2, entity, i)
            if (i1 != ComponentNull && i2 != ComponentNull) return true
        }
        return false
    }

    /** Returns true if no entities match the query. */
    inline fun isEmpty(): Boolean = !any()

    /** Returns the number of entities matching the query. */
    inline fun count(): Int {
        var count = 0
        forEach { _, _, _, _, _ -> count++ }
        return count
    }

    /** Finds the entity with the minimum value selected by [selector]. Returns -1 if no matches. */
    inline fun <R : Comparable<R>> minEntity(crossinline selector: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int) -> R): Int {
        var minEntity = -1
        var minValue: R? = null
        forEach { entity, c1, i1, c2, i2 ->
            val value = selector(entity, c1, i1, c2, i2)
            val currentMin = minValue
            if (currentMin == null || value < currentMin) {
                minValue = value
                minEntity = entity
            }
        }
        return minEntity
    }

    /** Finds the entity with the maximum value selected by [selector]. Returns -1 if no matches. */
    inline fun <R : Comparable<R>> maxEntity(crossinline selector: (entity: Int, c1: L1, i1: Int, c2: L2, i2: Int) -> R): Int {
        var maxEntity = -1
        var maxValue: R? = null
        forEach { entity, c1, i1, c2, i2 ->
            val value = selector(entity, c1, i1, c2, i2)
            val currentMax = maxValue
            if (currentMax == null || value > currentMax) {
                maxValue = value
                maxEntity = entity
            }
        }
        return maxEntity
    }

    /** Shuffles the internal iteration order. */
    fun shuffle(): Query2<T1, L1, T2, L2> {
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
        forEach { entity, _, _, _, _ -> destination.add(entity) }
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
        forEach { _, _, i1, _, i2 ->
            destination.add(if (dp === p1) i1 else i2)
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
        forEach { entity, _, _, _, _ ->
            seen++
            if (kotlin.random.Random.nextInt(seen) == 0) selected = entity
        }
        return selected
    }

    /** Returns a new [IntList] containing all matching entity IDs. */
    fun toEntities(): IntList {
        val result = IntList()
        forEach { entity, _, _, _, _ -> result.add(entity) }
        return result
    }

}
