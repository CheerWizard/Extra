package com.cws.extra.memory

import com.cws.extra.memory.*

import kotlin.ByteArray
import kotlin.Int

public fun Endian?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun Endian?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun Endian?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun Endian?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun Endian?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun ByteArray.decodeEndian(): Endian = NativeBuffer(this).decodeEndian()

public fun NativeBuffer.decodeEndian(): Endian {
  val ordinal = nextInt()
  return Endian.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of Endian")
}

public fun NativeBuffer.decodeGpuEndian(): Endian {
  val ordinal = nextInt()
  return Endian.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of Endian")
}

public val Endian.`value`: Int
  get() = ordinal
