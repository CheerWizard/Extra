package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun SpirvTarget?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun SpirvTarget?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun SpirvTarget?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun SpirvTarget?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun SpirvTarget?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun ByteArray.decodeSpirvTarget(): SpirvTarget = NativeBuffer(this).decodeSpirvTarget()

public fun NativeBuffer.decodeSpirvTarget(): SpirvTarget {
  val ordinal = nextInt()
  return SpirvTarget.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of SpirvTarget")
}

public fun NativeBuffer.decodeGpuSpirvTarget(): SpirvTarget {
  val ordinal = nextInt()
  return SpirvTarget.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of SpirvTarget")
}

public val SpirvTarget.`value`: Int
  get() = ordinal
