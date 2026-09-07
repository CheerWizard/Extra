package com.cws.extra.math.matrices

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun Mat4?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES

public fun Mat4?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES

public fun Mat4?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun Mat4?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun Mat4?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun Mat4?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(m00)
  buffer.pushFloat(m01)
  buffer.pushFloat(m02)
  buffer.pushFloat(m03)
  buffer.pushFloat(m10)
  buffer.pushFloat(m11)
  buffer.pushFloat(m12)
  buffer.pushFloat(m13)
  buffer.pushFloat(m20)
  buffer.pushFloat(m21)
  buffer.pushFloat(m22)
  buffer.pushFloat(m23)
  buffer.pushFloat(m30)
  buffer.pushFloat(m31)
  buffer.pushFloat(m32)
  buffer.pushFloat(m33)
}

public fun Mat4?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(m00)
  buffer.pushFloat(m01)
  buffer.pushFloat(m02)
  buffer.pushFloat(m03)
  buffer.pushFloat(m10)
  buffer.pushFloat(m11)
  buffer.pushFloat(m12)
  buffer.pushFloat(m13)
  buffer.pushFloat(m20)
  buffer.pushFloat(m21)
  buffer.pushFloat(m22)
  buffer.pushFloat(m23)
  buffer.pushFloat(m30)
  buffer.pushFloat(m31)
  buffer.pushFloat(m32)
  buffer.pushFloat(m33)
}

public fun Mat4?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(m00)
  buffer.pushFloat(m01)
  buffer.pushFloat(m02)
  buffer.pushFloat(m03)
  buffer.pushFloat(m10)
  buffer.pushFloat(m11)
  buffer.pushFloat(m12)
  buffer.pushFloat(m13)
  buffer.pushFloat(m20)
  buffer.pushFloat(m21)
  buffer.pushFloat(m22)
  buffer.pushFloat(m23)
  buffer.pushFloat(m30)
  buffer.pushFloat(m31)
  buffer.pushFloat(m32)
  buffer.pushFloat(m33)
}

public fun NativeBuffer.decodeMat4(): Mat4 = Mat4(
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
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

public fun NativeBuffer.decodeGpuMat4(): Mat4 = Mat4(
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
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

public fun ByteArray.decodeMat4(): Mat4 = NativeBuffer(this).decodeMat4()
