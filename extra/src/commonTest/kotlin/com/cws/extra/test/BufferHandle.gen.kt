package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun BufferHandle?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Long.SIZE_BYTES

public fun BufferHandle?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Long.SIZE_BYTES

public fun BufferHandle?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun BufferHandle?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun BufferHandle?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun BufferHandle?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushLong(address)
}

public fun BufferHandle?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushLong(address)
}

public fun BufferHandle?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushLong(address)
}

public fun NativeBuffer.decodeBufferHandle(): BufferHandle = BufferHandle(
  nextLong(),
)

public fun NativeBuffer.decodeGpuBufferHandle(): BufferHandle = BufferHandle(
  nextLong(),
)

public fun ByteArray.decodeBufferHandle(): BufferHandle = NativeBuffer(this).decodeBufferHandle()
