package com.cws.extra.memory

import com.cws.extra.memory.*

import kotlin.ByteArray
import kotlin.Int

public fun MemoryBoundary?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun MemoryBoundary?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun MemoryBoundary?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun MemoryBoundary?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun MemoryBoundary?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun ByteArray.decodeMemoryBoundary(): MemoryBoundary = NativeBuffer(this).decodeMemoryBoundary()

public fun NativeBuffer.decodeMemoryBoundary(): MemoryBoundary {
  val ordinal = nextInt()
  return MemoryBoundary.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of MemoryBoundary")
}

public fun NativeBuffer.decodeGpuMemoryBoundary(): MemoryBoundary {
  val ordinal = nextInt()
  return MemoryBoundary.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of MemoryBoundary")
}

public val MemoryBoundary.`value`: Int
  get() = ordinal
