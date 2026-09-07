package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import com.cws.extra.test.decodeGpuMemoryType
import com.cws.extra.test.decodeMemoryType
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun BufferInfo?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES + name.orEmpty().sizeBytesUtf8(memoryLayout) + Int.SIZE_BYTES + memoryType.sizeBytes(memoryLayout) + Int.SIZE_BYTES + Long.SIZE_BYTES + Boolean.SIZE_BYTES

public fun BufferInfo?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else name.orEmpty().sizeBytesUtf8(memoryLayout) + Int.SIZE_BYTES + memoryType.sizeBytesPacked(memoryLayout) + Int.SIZE_BYTES + Long.SIZE_BYTES + Boolean.SIZE_BYTES

public fun BufferInfo?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun BufferInfo?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun BufferInfo?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun BufferInfo?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  buffer.pushInt(slot)
  memoryType.encode(buffer)
  buffer.pushInt(usages)
  buffer.pushLong(size)
  buffer.pushBoolean(isStatic)
}

public fun BufferInfo?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  buffer.pushInt(slot)
  memoryType.encodeGpu(buffer)
  buffer.pushInt(usages)
  buffer.pushLong(size)
  buffer.pushBoolean(isStatic)
}

public fun BufferInfo?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushPackedStringUtf8(name)
  buffer.pushInt(slot)
  memoryType.encodePacked(buffer)
  buffer.pushInt(usages)
  buffer.pushLong(size)
  buffer.pushBoolean(isStatic)
}

public fun NativeBuffer.decodeBufferInfo(): BufferInfo = BufferInfo(
  nextStringUtf8(),
  nextInt(),
  decodeMemoryType(),
  nextInt(),
  nextLong(),
  nextBoolean(),
)

public fun NativeBuffer.decodeGpuBufferInfo(): BufferInfo = BufferInfo(
  nextStringUtf8(),
  nextInt(),
  decodeGpuMemoryType(),
  nextInt(),
  nextLong(),
  nextBoolean(),
)

public fun ByteArray.decodeBufferInfo(): BufferInfo = NativeBuffer(this).decodeBufferInfo()
