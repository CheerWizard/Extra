package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun AttributeType?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun AttributeType?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun AttributeType?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun AttributeType?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun AttributeType?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeAttributeType(): AttributeType = NativeBuffer(this).decodeAttributeType()

public fun NativeBuffer.decodeAttributeType(): AttributeType {
  val rawValue = nextInt()
  return AttributeType.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of AttributeType")
}

public fun NativeBuffer.decodeGpuAttributeType(): AttributeType {
  val rawValue = nextInt()
  return AttributeType.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of AttributeType")
}

public val AttributeType.`value`: Int
  get() = rawValue
