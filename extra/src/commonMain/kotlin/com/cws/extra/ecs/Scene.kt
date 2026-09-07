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
import kotlin.jvm.JvmName

fun Scene(
    entityCount: Int = EntityPool.DEFAULT_ENTITY_COUNT,
) = Scene(
    EntityPool(entityCount),
    ComponentRegistry.createComponentsState(entityCount),
)

/**
 * The main entry point for ECS operations. A Scene contains entities and their components.
 */
@ExtraData
data class Scene(
    @PublishedApi
    internal val entities: EntityPool,
    val components: ComponentsState,
) {

    /** Creates a new entity. */
    fun createEntity(): Int = entities.create()

    fun createEntities(entityCount: Int): IntList = entities.create(entityCount)

    fun addEntity(entity: Int): Boolean = entities.add(entity)

    /** Removes an entity and all its components from the scene. */
    fun removeEntity(entity: Int) {
        if (!entities.has(entity)) return
        entities.remove(entity)
        components.removeEntity(entity)
    }

    fun hasEntity(entity: Int) = entities.has(entity)

    fun clear() {
        entities.clear()
        components.clear()
    }

    inline fun <reified T> create(component: T): Int {
        val entity = createEntity()
        val id = ComponentId<T>()
        components.add(id, entity, component)
        return entity
    }

    inline fun <reified T1, reified T2> create(
        component1: T1,
        component2: T2,
    ): Int {
        val entity = createEntity()
        val id1 = ComponentId<T1>()
        val id2 = ComponentId<T2>()
        components.add(id1, entity, component1)
        components.add(id2, entity, component2)
        return entity
    }

    inline fun <reified T1, reified T2, reified T3> create(
        component1: T1,
        component2: T2,
        component3: T3,
    ): Int {
        val entity = createEntity()
        val id1 = ComponentId<T1>()
        val id2 = ComponentId<T2>()
        val id3 = ComponentId<T3>()
        components.add(id1, entity, component1)
        components.add(id2, entity, component2)
        components.add(id3, entity, component3)
        return entity
    }

    inline fun <reified T1, reified T2, reified T3, reified T4> create(
        component1: T1,
        component2: T2,
        component3: T3,
        component4: T4,
    ): Int {
        val entity = createEntity()
        val id1 = ComponentId<T1>()
        val id2 = ComponentId<T2>()
        val id3 = ComponentId<T3>()
        val id4 = ComponentId<T4>()
        components.add(id1, entity, component1)
        components.add(id2, entity, component2)
        components.add(id3, entity, component3)
        components.add(id4, entity, component4)
        return entity
    }

    inline fun <reified T> create(
        entityCount: Int,
        component: T
    ) {
        val entities = createEntities(entityCount)
        val id = ComponentId<T>()
        while (entities.isNotEmpty) {
            val entity = entities.pop()
            components.add(id, entity, component)
        }
    }

    inline fun <reified T1, reified T2> create(
        entityCount: Int,
        component1: T1,
        component2: T2,
    ) {
        val entities = createEntities(entityCount)
        val id1 = ComponentId<T1>()
        val id2 = ComponentId<T2>()
        while (entities.isNotEmpty) {
            val entity = entities.pop()
            components.add(id1, entity, component1)
            components.add(id2, entity, component2)
        }
    }

    inline fun <reified T1, reified T2, reified T3> create(
        entityCount: Int,
        component1: T1,
        component2: T2,
        component3: T3,
    ) {
        val entities = createEntities(entityCount)
        val id1 = ComponentId<T1>()
        val id2 = ComponentId<T2>()
        val id3 = ComponentId<T3>()
        while (entities.isNotEmpty) {
            val entity = entities.pop()
            components.add(id1, entity, component1)
            components.add(id2, entity, component2)
            components.add(id3, entity, component3)
        }
    }

    inline fun <reified T> add(
        entity: Int,
        component: T
    ) {
        val id = ComponentId<T>()
        components.add(id, entity, component)
    }

    inline fun <reified T1, reified T2> add(
        entity: Int,
        component1: T1,
        component2: T2,
    ) {
        val id1 = ComponentId<T1>()
        val id2 = ComponentId<T2>()
        components.add(id1, entity, component1)
        components.add(id2, entity, component2)
    }

    inline fun <reified T1, reified T2, reified T3> add(
        entity: Int,
        component1: T1,
        component2: T2,
        component3: T3,
    ) {
        val id1 = ComponentId<T1>()
        val id2 = ComponentId<T2>()
        val id3 = ComponentId<T3>()
        components.add(id1, entity, component1)
        components.add(id2, entity, component2)
        components.add(id3, entity, component3)
    }

    inline fun <reified T1, reified T2, reified T3, reified T4> add(
        entity: Int,
        component1: T1,
        component2: T2,
        component3: T3,
        component4: T4,
    ) {
        val id1 = ComponentId<T1>()
        val id2 = ComponentId<T2>()
        val id3 = ComponentId<T3>()
        val id4 = ComponentId<T4>()
        components.add(id1, entity, component1)
        components.add(id2, entity, component2)
        components.add(id3, entity, component3)
        components.add(id4, entity, component4)
    }

    @JvmName("has")
    inline fun <reified T> has(entity: Int): Boolean = components.has<T>(entity)

    @JvmName("has2")
    inline fun <reified T1, reified T2> has(entity: Int): Boolean {
        return components.has<T1>(entity) && components.has<T2>(entity)
    }

    @JvmName("has3")
    inline fun <reified T1, reified T2, reified T3> has(entity: Int): Boolean {
        return components.has<T1>(entity) && components.has<T2>(entity) && components.has<T3>(entity)
    }

    @JvmName("has4")
    inline fun <reified T1, reified T2, reified T3, reified T4> has(entity: Int): Boolean {
        return components.has<T1>(entity) && components.has<T2>(entity) &&
                components.has<T3>(entity) && components.has<T4>(entity)
    }

    @JvmName("remove")
    inline fun <reified T> remove(entity: Int) {
        val id = ComponentId<T>()
        components.remove(id, entity)
    }

    @JvmName("remove2")
    inline fun <reified T1, reified T2> remove(entity: Int) {
        val id1 = ComponentId<T1>()
        val id2 = ComponentId<T2>()
        components.remove(id1, entity)
        components.remove(id2, entity)
    }

    @JvmName("remove3")
    inline fun <reified T1, reified T2, reified T3> remove(entity: Int) {
        val id1 = ComponentId<T1>()
        val id2 = ComponentId<T2>()
        val id3 = ComponentId<T3>()
        components.remove(id1, entity)
        components.remove(id2, entity)
        components.remove(id3, entity)
    }

    @JvmName("remove4")
    inline fun <reified T1, reified T2, reified T3, reified T4> remove(entity: Int) {
        val id1 = ComponentId<T1>()
        val id2 = ComponentId<T2>()
        val id3 = ComponentId<T3>()
        val id4 = ComponentId<T4>()
        components.remove(id1, entity)
        components.remove(id2, entity)
        components.remove(id3, entity)
        components.remove(id4, entity)
    }

    inline fun <reified T> get(entity: Int): Int {
        return components.getPoolUnsafe(ComponentRegistry.getRegistrationIndex<T>()).getComponentIndex(entity)
    }

    inline fun <reified T1, reified L1 : IExtraList> update(
        entity: Int,
        updateBlock: L1.(componentIndex: Int) -> Unit,
    ) {
        val id = ComponentId<T1>()
        val storageIndex = ComponentRegistry.getRegistrationIndex(id)
        val storage = components.storages[storageIndex]
        val pool = components.getPoolUnsafe(storageIndex)
        val componentIndex = pool.entityToComponent[entity]
        if (storage != null && componentIndex != ComponentNull) {
            (storage.list as L1).updateBlock(componentIndex)
        }
    }

    /** Creates a query for entities matching specified component types. */
    @JvmName("query")
    inline fun <reified T1, reified L1: IExtraList> query() =
        Query1<T1, L1>(this, ComponentId<T1>())

    @JvmName("query2")
    inline fun <reified T1, reified L1: IExtraList, reified T2, reified L2: IExtraList> query() =
        Query2<T1, L1, T2, L2>(this, ComponentId<T1>(), ComponentId<T2>())

    @JvmName("query3")
    inline fun <reified T1, reified L1: IExtraList, reified T2, reified L2: IExtraList, reified T3, reified L3 : IExtraList> query() =
        Query3<T1, L1, T2, L2, T3, L3>(this, ComponentId<T1>(), ComponentId<T2>(), ComponentId<T3>())

    @JvmName("query4")
    inline fun <reified T1, reified L1: IExtraList, reified T2, reified L2: IExtraList, reified T3, reified L3 : IExtraList, reified T4, reified L4 : IExtraList> query() =
        Query4<T1, L1, T2, L2, T3, L3, T4, L4>(this, ComponentId<T1>(), ComponentId<T2>(), ComponentId<T3>(), ComponentId<T4>())

    @JvmName("query5")
    inline fun <reified T1, reified L1: IExtraList, reified T2, reified L2: IExtraList, reified T3, reified L3 : IExtraList, reified T4, reified L4 : IExtraList, reified T5, reified L5 : IExtraList> query() =
        Query5<T1, L1, T2, L2, T3, L3, T4, L4, T5, L5>(this, ComponentId<T1>(), ComponentId<T2>(), ComponentId<T3>(), ComponentId<T4>(), ComponentId<T5>())
}
