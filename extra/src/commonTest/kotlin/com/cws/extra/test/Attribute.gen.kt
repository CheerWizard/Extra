package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import com.cws.extra.test.decodeAttributeFormat
import com.cws.extra.test.decodeAttributeType
import com.cws.extra.test.decodeGpuAttributeFormat
import com.cws.extra.test.decodeGpuAttributeType
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun Attribute?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES + type.sizeBytes(memoryLayout) + format.sizeBytes(memoryLayout)

public fun Attribute?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES + type.sizeBytesPacked(memoryLayout) + format.sizeBytesPacked(memoryLayout)

public fun Attribute?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun Attribute?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun Attribute?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun Attribute?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(location)
  type.encode(buffer)
  format.encode(buffer)
}

public fun Attribute?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(location)
  type.encodeGpu(buffer)
  format.encodeGpu(buffer)
}

public fun Attribute?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(location)
  type.encodePacked(buffer)
  format.encodePacked(buffer)
}

public fun NativeBuffer.decodeAttribute(): Attribute = Attribute(
  nextInt(),
  decodeAttributeType(),
  decodeAttributeFormat(),
)

public fun NativeBuffer.decodeGpuAttribute(): Attribute = Attribute(
  nextInt(),
  decodeGpuAttributeType(),
  decodeGpuAttributeFormat(),
)

public fun ByteArray.decodeAttribute(): Attribute = NativeBuffer(this).decodeAttribute()
