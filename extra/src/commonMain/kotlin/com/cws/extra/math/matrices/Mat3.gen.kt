package com.cws.extra.math.matrices

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun Mat3?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES

public fun Mat3?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES

public fun Mat3?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun Mat3?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun Mat3?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun Mat3?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(m00)
  buffer.pushFloat(m01)
  buffer.pushFloat(m02)
  buffer.pushFloat(m10)
  buffer.pushFloat(m11)
  buffer.pushFloat(m12)
  buffer.pushFloat(m20)
  buffer.pushFloat(m21)
  buffer.pushFloat(m22)
}

public fun Mat3?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(m00)
  buffer.pushFloat(m01)
  buffer.pushFloat(m02)
  buffer.pushFloat(m10)
  buffer.pushFloat(m11)
  buffer.pushFloat(m12)
  buffer.pushFloat(m20)
  buffer.pushFloat(m21)
  buffer.pushFloat(m22)
}

public fun Mat3?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(m00)
  buffer.pushFloat(m01)
  buffer.pushFloat(m02)
  buffer.pushFloat(m10)
  buffer.pushFloat(m11)
  buffer.pushFloat(m12)
  buffer.pushFloat(m20)
  buffer.pushFloat(m21)
  buffer.pushFloat(m22)
}

public fun NativeBuffer.decodeMat3(): Mat3 = Mat3(
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
)

public fun NativeBuffer.decodeGpuMat3(): Mat3 = Mat3(
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
)

public fun ByteArray.decodeMat3(): Mat3 = NativeBuffer(this).decodeMat3()
