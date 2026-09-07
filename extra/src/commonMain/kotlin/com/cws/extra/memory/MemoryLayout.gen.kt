package com.cws.extra.memory

import com.cws.extra.memory.*

import kotlin.ByteArray
import kotlin.Int

public fun MemoryLayout?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun MemoryLayout?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun MemoryLayout?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun MemoryLayout?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun MemoryLayout?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun ByteArray.decodeMemoryLayout(): MemoryLayout = NativeBuffer(this).decodeMemoryLayout()

public fun NativeBuffer.decodeMemoryLayout(): MemoryLayout {
  val ordinal = nextInt()
  return MemoryLayout.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of MemoryLayout")
}

public fun NativeBuffer.decodeGpuMemoryLayout(): MemoryLayout {
  val ordinal = nextInt()
  return MemoryLayout.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of MemoryLayout")
}

public val MemoryLayout.`value`: Int
  get() = ordinal
