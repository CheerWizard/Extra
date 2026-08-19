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
import com.cws.extra.memory.ExtraData
import com.cws.extra.memory.IExtraList

const val ComponentNull = -1
const val EntityNull = -1

fun ComponentPool(entityCount: Int) = ComponentPool(
    IntList(entityCount) { ComponentNull },
    IntList(entityCount) { EntityNull },
)

@ExtraData
class ComponentPool(
    // store component indices by entity index
    val entityToComponent: IntList,
    // store entity indices by component index
    val componentToEntity: IntList,
) {

    fun has(entity: Int): Boolean {
        if (entity >= entityToComponent.size || entity == ComponentNull) return false
        val componentIndex = entityToComponent[entity]
        return componentIndex != ComponentNull && componentIndex < componentToEntity.size && componentToEntity[componentIndex] == entity
    }

    fun getComponentIndex(entity: Int) = entityToComponent[entity]

    fun add(entity: Int): Int {
        if (has(entity)) return getComponentIndex(entity)

        componentToEntity.add(entity)
        val componentIndex = componentToEntity.lastIndex

        while (entity >= entityToComponent.size) {
            entityToComponent.add(ComponentNull)
        }

        entityToComponent[entity] = componentIndex

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

        return componentIndex
    }

    fun clear() {
        entityToComponent.clear()
        componentToEntity.clear()
    }

}

fun ComponentBitmasks(capacity: Int) = ComponentBitmasks(LongArray(capacity))

@ExtraData
data class ComponentBitmasks(
    var signatures: LongArray,
) {

    fun add(entity: Int, componentId: Int) {
        signatures[entity] = signatures[entity] or (1L shl componentId)
    }

    fun remove(entity: Int, componentId: Int) {
        signatures[entity] = signatures[entity] and (1L shl componentId).inv()
    }

    fun hasAll(entity: Int, mask: Long) = (signatures[entity] and mask) == mask

    fun clear() {
        signatures.fill(0)
    }

}

interface ComponentStorage {
    val list: IExtraList
    fun <T> add(entity: Int, component: T)
    fun remove(entity: Int)
    fun clear()
    fun index(entity: Int): Int
    fun has(entity: Int): Boolean
}

fun Scene(capacity: Int) = Scene(
    IntList(capacity) { EntityNull },
    ComponentBitmasks(capacity),
    IntList(capacity) { EntityNull },
    0,
    ComponentRegistry(capacity),
)

@ExtraData
data class Scene(
    val entities: IntList,
    val bitmasks: ComponentBitmasks,
    val removedEntities: IntList,
    var entityIdCounter: Int,
    val registry: ComponentRegistry,
) {

    fun createEntity(): Int {
        val newEntity = if (removedEntities.isNotEmpty) {
            removedEntities.pop()
        } else {
            entityIdCounter++
        }
        return addEntity(newEntity)
    }

    fun addEntity(entity: Int): Int {
        if (entities.array.contains(entity)) return entity
        entities.add(entity)
        return entity
    }

    fun removeEntity(entity: Int) {
        if (!entities.array.contains(entity)) return

        entities.forEachIndexed { i, e ->
            if (entity == e) {
                removedEntities.add(entities.removeAtSwap(i))
                return@forEachIndexed
            }
        }

        for (i in 0 until registry.size) {
            registry[i].remove(entity)
        }

        bitmasks.signatures[entity] = 0L
    }

    fun clear() {
        entities.clear()
        for (i in 0 until registry.size) {
            registry[i].clear()
        }
        registry.clear()
        entityIdCounter = 0
        removedEntities.clear()
    }

    inline fun <reified T> add(entity: Int, component: T) {
        val id = getComponentID<T>()
        val c = registry[id]
        c.add(entity, component)
        bitmasks.add(entity, id)
    }

    inline fun <reified T> has(entity: Int): Boolean {
        val id = getComponentID<T>()
        return registry[id].has(entity)
    }

    inline fun <reified T> remove(entity: Int) {
        val id = getComponentID<T>()
        val c = registry[id]
        c.remove(entity)
        bitmasks.remove(entity, id)
    }

    inline fun <reified T1> forEach(
        block: (entity: Int, c1: Int) -> Unit
    ) {
        val id1 = getComponentID<T1>()
        val c1 = registry[id1]
        val mask = (1L shl id1)
        for (i in entities.lastIndex downTo 0) {
            val entityId = entities[i]
            if (bitmasks.hasAll(entityId, mask)) {
                val i1 = c1.index(entityId)
                if (i1 != ComponentNull) {
                    block(entityId, i1)
                }
            }
        }
    }

    inline fun <reified T1, reified T2> forEach(
        block: (entity: Int, c1: Int, c2: Int) -> Unit
    ) {
        val id1 = getComponentID<T1>()
        val id2 = getComponentID<T2>()
        val c1 = registry[id1]
        val c2 = registry[id2]
        val mask = (1L shl id1) or (1L shl id2)
        for (i in entities.lastIndex downTo 0) {
            val entityId = entities[i]
            if (bitmasks.hasAll(entityId, mask)) {
                val i1 = c1.index(entityId)
                val i2 = c2.index(entityId)
                if (i1 != ComponentNull && i2 != ComponentNull) {
                    block(entityId, i1, i2)
                }
            }
        }
    }

    inline fun <reified T1, reified T2, reified T3> forEach(
        block: (entity: Int, c1: Int, c2: Int, c3: Int) -> Unit
    ) {
        val id1 = getComponentID<T1>()
        val id2 = getComponentID<T2>()
        val id3 = getComponentID<T3>()
        val c1 = registry[id1]
        val c2 = registry[id2]
        val c3 = registry[id3]
        val mask = (1L shl id1) or (1L shl id2) or (1L shl id3)
        for (i in entities.lastIndex downTo 0) {
            val entityId = entities[i]
            if (bitmasks.hasAll(entityId, mask)) {
                val i1 = c1.index(entityId)
                val i2 = c2.index(entityId)
                val i3 = c3.index(entityId)
                if (i1 != ComponentNull && i2 != ComponentNull && i3 != ComponentNull) {
                    block(entityId, i1, i2, i3)
                }
            }
        }
    }

    inline fun <reified T1, reified T2, reified T3, reified T4> forEach(
        block: (entity: Int, c1: Int, c2: Int, c3: Int, c4: Int) -> Unit
    ) {
        val id1 = getComponentID<T1>()
        val id2 = getComponentID<T2>()
        val id3 = getComponentID<T3>()
        val id4 = getComponentID<T4>()
        val c1 = registry[id1]
        val c2 = registry[id2]
        val c3 = registry[id3]
        val c4 = registry[id3]
        val mask = (1L shl id1) or (1L shl id2) or (1L shl id3) or (1L shl id4)
        for (i in entities.lastIndex downTo 0) {
            val entityId = entities[i]
            if (bitmasks.hasAll(entityId, mask)) {
                val i1 = c1.index(entityId)
                val i2 = c2.index(entityId)
                val i3 = c3.index(entityId)
                val i4 = c4.index(entityId)
                if (i1 != ComponentNull &&
                    i2 != ComponentNull &&
                    i3 != ComponentNull &&
                    i4 != ComponentNull
                ) {
                    block(entityId, i1, i2, i3, i4)
                }
            }
        }
    }

    inline fun <reified T1, reified T2, reified T3, reified T4, reified T5> forEach(
        block: (entity: Int, c1: Int, c2: Int, c3: Int, c4: Int, c5: Int) -> Unit
    ) {
        val id1 = getComponentID<T1>()
        val id2 = getComponentID<T2>()
        val id3 = getComponentID<T3>()
        val id4 = getComponentID<T4>()
        val id5 = getComponentID<T5>()
        val c1 = registry[id1]
        val c2 = registry[id2]
        val c3 = registry[id3]
        val c4 = registry[id4]
        val c5 = registry[id5]
        val mask = (1L shl id1) or (1L shl id2) or (1L shl id3) or (1L shl id4) or (1L shl id5)
        for (i in entities.lastIndex downTo 0) {
            val entityId = entities[i]
            if (bitmasks.hasAll(entityId, mask)) {
                val i1 = c1.index(entityId)
                val i2 = c2.index(entityId)
                val i3 = c3.index(entityId)
                val i4 = c4.index(entityId)
                val i5 = c5.index(entityId)
                if (i1 != ComponentNull &&
                    i2 != ComponentNull &&
                    i3 != ComponentNull &&
                    i4 != ComponentNull &&
                    i5 != ComponentNull
                ) {
                    block(entityId, i1, i2, i3, i4, i5)
                }
            }
        }
    }

}