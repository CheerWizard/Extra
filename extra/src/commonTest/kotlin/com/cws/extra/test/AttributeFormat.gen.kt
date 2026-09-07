package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun AttributeFormat?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun AttributeFormat?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun AttributeFormat?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun AttributeFormat?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun AttributeFormat?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeAttributeFormat(): AttributeFormat = NativeBuffer(this).decodeAttributeFormat()

public fun NativeBuffer.decodeAttributeFormat(): AttributeFormat {
  val rawValue = nextInt()
  return AttributeFormat.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of AttributeFormat")
}

public fun NativeBuffer.decodeGpuAttributeFormat(): AttributeFormat {
  val rawValue = nextInt()
  return AttributeFormat.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of AttributeFormat")
}

public val AttributeFormat.`value`: Int
  get() = rawValue
