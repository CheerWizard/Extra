package com.cws.extra.ecs

import com.cws.extra.memory.*

import com.cws.extra.lists.decodeBooleanList
import com.cws.extra.lists.decodeGpuBooleanList
import com.cws.extra.lists.decodeGpuIntList
import com.cws.extra.lists.decodeIntList
import com.cws.extra.lists.encode
import com.cws.extra.lists.encodeGpu
import com.cws.extra.lists.encodePacked
import com.cws.extra.lists.sizeBytes
import com.cws.extra.lists.sizeBytesPacked
import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun EntityPool?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else alive.sizeBytes(memoryLayout) + removed.sizeBytes(memoryLayout) + bulk.sizeBytes(memoryLayout) + Int.SIZE_BYTES

public fun EntityPool?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else alive.sizeBytesPacked(memoryLayout) + removed.sizeBytesPacked(memoryLayout) + bulk.sizeBytesPacked(memoryLayout) + Int.SIZE_BYTES

public fun EntityPool?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun EntityPool?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun EntityPool?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun EntityPool?.encode(buffer: NativeBuffer) {
  if (this == null) return
  alive.encode(buffer)
  removed.encode(buffer)
  bulk.encode(buffer)
  buffer.pushInt(nextId)
}

public fun EntityPool?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  alive.encodeGpu(buffer)
  removed.encodeGpu(buffer)
  bulk.encodeGpu(buffer)
  buffer.pushInt(nextId)
}

public fun EntityPool?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  alive.encodePacked(buffer)
  removed.encodePacked(buffer)
  bulk.encodePacked(buffer)
  buffer.pushInt(nextId)
}

public fun NativeBuffer.decodeEntityPool(): EntityPool = EntityPool(
  decodeBooleanList(),
  decodeIntList(),
  decodeIntList(),
  nextInt(),
)

public fun NativeBuffer.decodeGpuEntityPool(): EntityPool = EntityPool(
  decodeGpuBooleanList(),
  decodeGpuIntList(),
  decodeGpuIntList(),
  nextInt(),
)

public fun ByteArray.decodeEntityPool(): EntityPool = NativeBuffer(this).decodeEntityPool()
