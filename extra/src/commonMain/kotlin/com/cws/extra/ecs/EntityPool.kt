package com.cws.extra.ecs

import com.cws.extra.lists.BooleanList
import com.cws.extra.lists.IntList
import com.cws.extra.memory.ExtraData

fun EntityPool(
    entityCount: Int = EntityPool.DEFAULT_ENTITY_COUNT,
    removedEntityCount: Int = EntityPool.DEFAULT_REMOVED_ENTITY_COUNT,
    bulkEntityCount: Int = EntityPool.DEFAULT_BULK_ENTITY_COUNT,
) = EntityPool(
    alive = BooleanList(entityCount),
    removed = IntList(removedEntityCount),
    bulk = IntList(bulkEntityCount),
    nextId = 0,
)

/**
 * Manages a pool of entity IDs, including recycling of removed entities.
 */
@ExtraData
data class EntityPool(
    internal val alive: BooleanList,
    internal val removed: IntList,
    internal val bulk: IntList,
    internal var nextId: Int,
) {

    companion object {
        const val DEFAULT_ENTITY_COUNT = 16
        const val DEFAULT_REMOVED_ENTITY_COUNT = 16
        const val DEFAULT_BULK_ENTITY_COUNT = 16
    }

    val size: Int get() = alive.size

    fun create(): Int {
        val entity = if (removed.isNotEmpty) removed.pop() else nextId++
        add(entity)
        return entity
    }

    /** Creates [entityCount] entities at once. Returns a list of the new IDs. */
    fun create(entityCount: Int): IntList {
        if (entityCount < 0) return bulk

        bulk.clear()
        alive.ensureCapacity(entityCount)
        var remainCount = entityCount

        while (removed.isNotEmpty && remainCount > 0) {
            val entity = removed.pop()
            alive[entity] = true
            bulk.push(entity)
            remainCount--
        }

        while (remainCount > 0) {
            val entity = nextId++
            alive[entity] = true
            bulk.push(entity)
            remainCount--
        }

        alive.size += entityCount
        return bulk
    }

    fun add(entity: Int): Boolean {
        if (entity < 0 || has(entity)) return false
        alive.ensureCapacity(entity + 1)
        alive[entity] = true
        alive.size += 1
        return true
    }

    fun has(entity: Int) = entity >= 0 && entity <= alive.lastIndex && alive[entity]

    fun remove(entity: Int) {
        alive[entity] = false
        alive.size -= 1
        removed.push(entity)
    }

    fun clear() {
        alive.clear()
        removed.clear()
        bulk.clear()
        nextId = 0
    }

}