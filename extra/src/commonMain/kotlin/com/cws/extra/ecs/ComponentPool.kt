package com.cws.extra.ecs

import com.cws.extra.lists.IntList
import com.cws.extra.memory.ExtraData

fun ComponentPool(
    entityCount: Int,
    componentCount: Int,
) = ComponentPool(
    IntList(entityCount) { ComponentNull },
    IntList(componentCount) { EntityNull },
)

/**
 * Maps entities to component indices and vice versa for a specific component type.
 * Uses a dense array for components to improve cache locality.
 */
@ExtraData
class ComponentPool(
    // store component indices by entity index
    @PublishedApi
    internal val entityToComponent: IntList,
    // store entity indices by component index
    @PublishedApi
    internal val componentToEntity: IntList,
) {

    /** Incremented whenever the dense/sparse entity-component mapping changes. */
    @PublishedApi
    internal var structuralVersion: Int = 0
        private set

    init {
        entityToComponent.size = entityToComponent.capacity
    }

    inline val size: Int get() = componentToEntity.size

    inline fun has(entity: Int): Boolean {
        return entity >= 0 && entity < entityToComponent.size && entityToComponent[entity] != ComponentNull
    }

    inline fun getComponentIndex(entity: Int) = entityToComponent[entity]

    fun add(entity: Int): Int {
        if (has(entity)) return getComponentIndex(entity)

        componentToEntity.add(entity)
        val componentIndex = componentToEntity.lastIndex

        val newSize = entity + 1
        entityToComponent.ensureCapacity(newSize)

        if (newSize > entityToComponent.size) {
            val oldSize = entityToComponent.size
            entityToComponent.size = newSize
            entityToComponent.array.fill(ComponentNull, oldSize, entity)
        }

        entityToComponent[entity] = componentIndex
        structuralVersion++

        return componentIndex
    }

    fun remove(entity: Int): Int {
        if (!has(entity)) return ComponentNull

        val componentIndex = entityToComponent[entity]
        val lastComponentIndex = componentToEntity.lastIndex
        val lastEntity = componentToEntity[lastComponentIndex]

        componentToEntity.removeAtSwap(componentIndex)

        if (componentIndex != lastComponentIndex) {
            entityToComponent[lastEntity] = componentIndex
        }

        entityToComponent[entity] = ComponentNull
        structuralVersion++

        return componentIndex
    }

    fun clear() {
        val changed = entityToComponent.size != 0 || componentToEntity.size != 0
        entityToComponent.clear()
        componentToEntity.clear()
        if (changed) structuralVersion++
    }

}
