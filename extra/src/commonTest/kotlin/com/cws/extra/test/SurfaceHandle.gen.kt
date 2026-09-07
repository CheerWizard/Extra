package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun SurfaceHandle?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Long.SIZE_BYTES

public fun SurfaceHandle?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Long.SIZE_BYTES

public fun SurfaceHandle?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun SurfaceHandle?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun SurfaceHandle?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun SurfaceHandle?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushLong(address)
}

public fun SurfaceHandle?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushLong(address)
}

public fun SurfaceHandle?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushLong(address)
}

public fun NativeBuffer.decodeSurfaceHandle(): SurfaceHandle = SurfaceHandle(
  nextLong(),
)

public fun NativeBuffer.decodeGpuSurfaceHandle(): SurfaceHandle = SurfaceHandle(
  nextLong(),
)

public fun ByteArray.decodeSurfaceHandle(): SurfaceHandle = NativeBuffer(this).decodeSurfaceHandle()
