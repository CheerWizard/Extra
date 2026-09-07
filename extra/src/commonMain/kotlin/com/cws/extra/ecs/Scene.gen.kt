package com.cws.extra.ecs

import com.cws.extra.memory.*

import com.cws.extra.ecs.decodeComponentsState
import com.cws.extra.ecs.decodeEntityPool
import com.cws.extra.ecs.decodeGpuComponentsState
import com.cws.extra.ecs.decodeGpuEntityPool
import com.cws.extra.ecs.encode
import com.cws.extra.ecs.encodeGpu
import com.cws.extra.ecs.encodePacked
import com.cws.extra.ecs.sizeBytes
import com.cws.extra.ecs.sizeBytesPacked
import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun Scene?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else entities.sizeBytes(memoryLayout) + components.sizeBytes(memoryLayout)

public fun Scene?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else entities.sizeBytesPacked(memoryLayout) + components.sizeBytesPacked(memoryLayout)

public fun Scene?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun Scene?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun Scene?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun Scene?.encode(buffer: NativeBuffer) {
  if (this == null) return
  entities.encode(buffer)
  components.encode(buffer)
}

public fun Scene?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  entities.encodeGpu(buffer)
  components.encodeGpu(buffer)
}

public fun Scene?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  entities.encodePacked(buffer)
  components.encodePacked(buffer)
}

public fun NativeBuffer.decodeScene(): Scene = Scene(
  decodeEntityPool(),
  decodeComponentsState(),
)

public fun NativeBuffer.decodeGpuScene(): Scene = Scene(
  decodeGpuEntityPool(),
  decodeGpuComponentsState(),
)

public fun ByteArray.decodeScene(): Scene = NativeBuffer(this).decodeScene()
