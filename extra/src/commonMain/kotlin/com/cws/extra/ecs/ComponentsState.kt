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

import com.cws.extra.memory.Endian
import com.cws.extra.memory.IExtraList
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import com.cws.extra.memory.nextArray
import com.cws.extra.memory.nextInt
import com.cws.extra.memory.nextStringUtf16
import com.cws.extra.memory.pushArray
import com.cws.extra.memory.pushInt
import com.cws.extra.memory.pushPackedArray
import com.cws.extra.memory.pushStringUtf16
import com.cws.extra.memory.sizeBytesUtf16
import com.cws.print.Print

/**
 * Holds the state of all components in a [Scene], organized by pools and storages.
 */
data class ComponentsState(
    @PublishedApi
    internal val entityCount: Int,
    @PublishedApi
    internal val keys: Array<String>,
    @PublishedApi
    internal val pools: Array<ComponentPool?>,
    @PublishedApi
    internal val storages: Array<ComponentStorage?>,
) {

    companion object {
        const val TAG = "ComponentsState"
    }

    inline fun <reified T> add(entity: Int, component: T) {
        add(ComponentId<T>(), entity, component)
    }

    inline fun <reified T> add(componentId: Int, entity: Int, component: T) {
        val index = ComponentRegistry.getRegistrationIndex(componentId)
        val storage = storages[index] ?: run {
            Print.e(TAG) { "Failed to add component $componentId to components state, component storage not found" }
            return
        }
        val pool = pools[index] ?: run {
            Print.e(TAG) { "Failed to add component $componentId to components state, component pool not found" }
            return
        }
        if (!storage.has(component)) return
        val componentIndex = pool.add(entity)
        storage.add(componentIndex, component)
    }

    inline fun <reified T> remove(entity: Int) {
        remove(ComponentId<T>(), entity)
    }

    inline fun remove(componentId: Int, entity: Int) {
        val index = ComponentRegistry.getRegistrationIndex(componentId)
        val storage = storages[index] ?: run {
            Print.e(TAG) { "Failed to remove $componentId component from components state, component storage not found" }
            return
        }
        val pool = pools[index] ?: run {
            Print.e(TAG) { "Failed to remove $componentId component from components state, component pool not found" }
            return
        }
        if (pool.has(entity)) {
            val index = pool.remove(entity)
            if (index != ComponentNull) {
                storage.remove(index)
            }
        }
    }

    inline fun <reified T> has(entity: Int) = has(ComponentId<T>(), entity)

    inline fun has(componentId: Int, entity: Int): Boolean {
        val index = ComponentRegistry.getRegistrationIndex(componentId)
        val pool = pools[index]
        return pool?.has(entity) == true
    }

    inline fun <reified T> getPool(): ComponentPool? {
        return pools[ComponentRegistry.getRegistrationIndex<T>()]
    }

    @PublishedApi
    internal fun getPoolUnsafe(index: Int): ComponentPool = pools[index]
        ?: error("Component pool not found at registered storage index $index")

    internal inline fun <reified T> getPoolUnsafe(): ComponentPool =
        getPoolUnsafe(ComponentRegistry.getRegistrationIndex<T>())

    inline fun <reified T> getStorage(): ComponentStorage? {
        return storages[ComponentRegistry.getRegistrationIndex<T>()]
    }

    inline fun <reified T> getStorageUnsafe(): ComponentStorage = getStorage<T>()!!

    inline fun <reified T, reified S> getStorage(): S? {
        return storages[ComponentRegistry.getRegistrationIndex<T>()] as S
    }

    inline fun <reified T, reified S> getStorageUnsafe(): S = getStorage<T, S>()!!

    inline fun <reified Component, reified ComponentList : IExtraList> getComponentList(): ComponentList {
        val index = ComponentRegistry.getRegistrationIndex<Component>()
        val storage = storages[index] ?: run {
            Print.e(TAG) {
                "Failed to get component list at registry index $index, component storage not found"
            }
            throw IllegalArgumentException()
        }
        return storage.list as ComponentList
    }

    fun clear() {
        pools.forEach { it?.clear() }
    }

    /** Removes every component attached to [entity]. Entity destruction is intentionally cold-path. */
    internal fun removeEntity(entity: Int) {
        var registrationIndex = 0
        while (registrationIndex < pools.size) {
            val pool = pools[registrationIndex]
            if (pool != null && pool.has(entity)) {
                val componentIndex = pool.remove(entity)
                if (componentIndex != ComponentNull) {
                    storages[registrationIndex]?.remove(componentIndex)
                }
            }
            registrationIndex++
        }
    }

}

public fun ComponentsState?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else {
    Int.SIZE_BYTES * 3 + keys.sumOf { key ->
        val index = requireRegisteredKey(key)
        key.sizeBytesUtf16(memoryLayout) +
                pools[index].sizeBytes(memoryLayout) +
                (storages[index]?.sizeBytes(memoryLayout) ?: 0)
    }
}

public fun ComponentsState?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else {
    Int.SIZE_BYTES + keys.sumOf { key ->
        val index = requireRegisteredKey(key)
        key.sizeBytesUtf16(memoryLayout) +
                pools[index].sizeBytesPacked(memoryLayout) +
                (storages[index]?.sizeBytesPacked(memoryLayout) ?: 0)
    }
}

private fun ComponentsState.requireRegisteredKey(key: String): Int {
    val index = ComponentRegistry.getRegistrationIndexByKey(key)
    require(index != RegistrationIndexNull) { "Component key '$key' is not registered" }
    return index
}

public fun ComponentsState?.encode(
    memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
    endian: Endian = Endian.LITTLE,
    memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
    if (this == null) return NativeBuffer(0)
    val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
    encode(buffer)
    return buffer
}

public fun ComponentsState?.encodeGpu(
    memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
    endian: Endian = Endian.LITTLE,
    memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
    if (this == null) return NativeBuffer(0)
    val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
    encodeGpu(buffer)
    return buffer
}

public fun ComponentsState?.encodePacked(
    memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
    endian: Endian = Endian.LITTLE,
    memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
    if (this == null) return NativeBuffer(0)
    val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
    encodePacked(buffer)
    return buffer
}

public fun ComponentsState?.encode(buffer: NativeBuffer) {
    if (this == null) return
    buffer.pushInt(entityCount)
    buffer.pushArray(keys) { buffer.pushStringUtf16(it) }
    buffer.pushArray(keys) { key -> pools[requireRegisteredKey(key)].encode(buffer) }
    // Storage count and order are defined by keys.
    buffer.pushPackedArray(keys) { key -> storages[requireRegisteredKey(key)]?.encode(buffer) }
}

public fun ComponentsState?.encodeGpu(buffer: NativeBuffer) {
    if (this == null) return
    buffer.pushInt(entityCount)
    buffer.pushArray(keys) { buffer.pushStringUtf16(it) }
    buffer.pushArray(keys) { key -> pools[requireRegisteredKey(key)].encodeGpu(buffer) }
    buffer.pushPackedArray(keys) { key -> storages[requireRegisteredKey(key)]?.encodeGpu(buffer) }
}

public fun ComponentsState?.encodePacked(buffer: NativeBuffer) {
    if (this == null) return
    buffer.pushInt(entityCount)
    buffer.pushPackedArray(keys) { buffer.pushStringUtf16(it) }
    buffer.pushPackedArray(keys) { key -> pools[requireRegisteredKey(key)].encodePacked(buffer) }
    buffer.pushPackedArray(keys) { key -> storages[requireRegisteredKey(key)]?.encodePacked(buffer) }
}

public fun NativeBuffer.decodeComponentsState(): ComponentsState {
    val entityCount = nextInt()
    val keys = nextArray { nextStringUtf16() }
    val poolCount = nextInt()
    require(poolCount == keys.size) { "Component pool count $poolCount does not match key count ${keys.size}" }
    val indices = keys.map { key ->
        ComponentRegistry.getRegistrationIndexByKey(key).also { index ->
            require(index != RegistrationIndexNull) { "Component key '$key' is not registered" }
        }
    }
    val pools = arrayOfNulls<ComponentPool>(ComponentRegistry.capacity)
    val storages = arrayOfNulls<ComponentStorage>(ComponentRegistry.capacity)

    indices.forEach { index ->
        pools[index] = decodeComponentPool()
    }

    indices.forEach { index ->
        storages[index] = ComponentRegistry.createStorage(index, entityCount) {
            it?.decode(this)
        }
    }

    return ComponentsState(
        entityCount = entityCount,
        keys = keys,
        pools = pools,
        storages = storages,
    )
}

public fun NativeBuffer.decodeGpuComponentsState(): ComponentsState {
    val entityCount = nextInt()
    val keys = nextArray { nextStringUtf16() }
    val poolCount = nextInt()
    require(poolCount == keys.size) { "Component pool count $poolCount does not match key count ${keys.size}" }
    val indices = keys.map { key ->
        ComponentRegistry.getRegistrationIndexByKey(key).also { index ->
            require(index != RegistrationIndexNull) { "Component key '$key' is not registered" }
        }
    }
    val pools = arrayOfNulls<ComponentPool>(ComponentRegistry.capacity)
    val storages = arrayOfNulls<ComponentStorage>(ComponentRegistry.capacity)

    indices.forEach { index ->
        pools[index] = decodeGpuComponentPool()
    }

    indices.forEach { index ->
        storages[index] = ComponentRegistry.createStorage(index, entityCount) {
            it?.decodeGpu(this)
        }
    }

    return ComponentsState(
        entityCount = entityCount,
        keys = keys,
        pools = pools,
        storages = storages,
    )
}

public fun ByteArray.decodeComponentsState(): ComponentsState = NativeBuffer(this).decodeComponentsState()
