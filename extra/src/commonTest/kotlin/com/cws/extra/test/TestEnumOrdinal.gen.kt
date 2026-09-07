package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun TestEnumOrdinal?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun TestEnumOrdinal?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun TestEnumOrdinal?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun TestEnumOrdinal?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun TestEnumOrdinal?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun ByteArray.decodeTestEnumOrdinal(): TestEnumOrdinal = NativeBuffer(this).decodeTestEnumOrdinal()

public fun NativeBuffer.decodeTestEnumOrdinal(): TestEnumOrdinal {
  val ordinal = nextInt()
  return TestEnumOrdinal.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of TestEnumOrdinal")
}

public fun NativeBuffer.decodeGpuTestEnumOrdinal(): TestEnumOrdinal {
  val ordinal = nextInt()
  return TestEnumOrdinal.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of TestEnumOrdinal")
}

public val TestEnumOrdinal.`value`: Int
  get() = ordinal
