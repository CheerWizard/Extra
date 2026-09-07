package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun CommandBufferHandle?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Long.SIZE_BYTES

public fun CommandBufferHandle?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Long.SIZE_BYTES

public fun CommandBufferHandle?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun CommandBufferHandle?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun CommandBufferHandle?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun CommandBufferHandle?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushLong(address)
}

public fun CommandBufferHandle?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushLong(address)
}

public fun CommandBufferHandle?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushLong(address)
}

public fun NativeBuffer.decodeCommandBufferHandle(): CommandBufferHandle = CommandBufferHandle(
  nextLong(),
)

public fun NativeBuffer.decodeGpuCommandBufferHandle(): CommandBufferHandle = CommandBufferHandle(
  nextLong(),
)

public fun ByteArray.decodeCommandBufferHandle(): CommandBufferHandle = NativeBuffer(this).decodeCommandBufferHandle()
