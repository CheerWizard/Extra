package com.cws.extra.math.matrices

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun Mat2?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES

public fun Mat2?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES

public fun Mat2?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun Mat2?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun Mat2?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun Mat2?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(m00)
  buffer.pushFloat(m01)
  buffer.pushFloat(m10)
  buffer.pushFloat(m11)
}

public fun Mat2?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(m00)
  buffer.pushFloat(m01)
  buffer.pushFloat(m10)
  buffer.pushFloat(m11)
}

public fun Mat2?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(m00)
  buffer.pushFloat(m01)
  buffer.pushFloat(m10)
  buffer.pushFloat(m11)
}

public fun NativeBuffer.decodeMat2(): Mat2 = Mat2(
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
)

public fun NativeBuffer.decodeGpuMat2(): Mat2 = Mat2(
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
)

public fun ByteArray.decodeMat2(): Mat2 = NativeBuffer(this).decodeMat2()
