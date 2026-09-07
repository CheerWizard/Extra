package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import com.cws.extra.test.decodeGpuIndexSize
import com.cws.extra.test.decodeIndexSize
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun IndexBufferInfo?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES + name.orEmpty().sizeBytesUtf8(memoryLayout) + Int.SIZE_BYTES + indexSize.sizeBytes(memoryLayout)

public fun IndexBufferInfo?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else name.orEmpty().sizeBytesUtf8(memoryLayout) + Int.SIZE_BYTES + indexSize.sizeBytesPacked(memoryLayout)

public fun IndexBufferInfo?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun IndexBufferInfo?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun IndexBufferInfo?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun IndexBufferInfo?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  buffer.pushInt(indexCount)
  indexSize.encode(buffer)
}

public fun IndexBufferInfo?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  buffer.pushInt(indexCount)
  indexSize.encodeGpu(buffer)
}

public fun IndexBufferInfo?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushPackedStringUtf8(name)
  buffer.pushInt(indexCount)
  indexSize.encodePacked(buffer)
}

public fun NativeBuffer.decodeIndexBufferInfo(): IndexBufferInfo = IndexBufferInfo(
  nextStringUtf8(),
  nextInt(),
  decodeIndexSize(),
)

public fun NativeBuffer.decodeGpuIndexBufferInfo(): IndexBufferInfo = IndexBufferInfo(
  nextStringUtf8(),
  nextInt(),
  decodeGpuIndexSize(),
)

public fun ByteArray.decodeIndexBufferInfo(): IndexBufferInfo = NativeBuffer(this).decodeIndexBufferInfo()
