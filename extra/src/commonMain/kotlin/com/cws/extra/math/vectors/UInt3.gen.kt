package com.cws.extra.math.vectors

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun UInt3?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else UInt.SIZE_BYTES + UInt.SIZE_BYTES + UInt.SIZE_BYTES

public fun UInt3?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else UInt.SIZE_BYTES + UInt.SIZE_BYTES + UInt.SIZE_BYTES

public fun UInt3?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun UInt3?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun UInt3?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun UInt3?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushUInt(x)
  buffer.pushUInt(y)
  buffer.pushUInt(z)
}

public fun UInt3?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushUInt(x)
  buffer.pushUInt(y)
  buffer.pushUInt(z)
}

public fun UInt3?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushUInt(x)
  buffer.pushUInt(y)
  buffer.pushUInt(z)
}

public fun NativeBuffer.decodeUInt3(): UInt3 = UInt3(
  nextUInt(),
  nextUInt(),
  nextUInt(),
)

public fun NativeBuffer.decodeGpuUInt3(): UInt3 = UInt3(
  nextUInt(),
  nextUInt(),
  nextUInt(),
)

public fun ByteArray.decodeUInt3(): UInt3 = NativeBuffer(this).decodeUInt3()
