package com.cws.extra.ecs

import com.cws.extra.memory.IExtraList
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer

interface ComponentStorage {
    val list: IExtraList
    fun <T> add(componentIndex: Int, component: T)
    fun <T> has(component: T): Boolean
    fun remove(componentIndex: Int)

    fun sizeBytes(memoryLayout: MemoryLayout): Int
    fun sizeBytesPacked(memoryLayout: MemoryLayout): Int

    fun encode(buffer: NativeBuffer)
    fun encodeGpu(buffer: NativeBuffer)
    fun encodePacked(buffer: NativeBuffer)

    fun decode(buffer: NativeBuffer)
    fun decodeGpu(buffer: NativeBuffer)
    fun decodePacked(buffer: NativeBuffer)
}