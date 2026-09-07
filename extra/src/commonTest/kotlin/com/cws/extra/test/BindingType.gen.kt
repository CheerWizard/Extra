package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun BindingType?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun BindingType?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun BindingType?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun BindingType?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun BindingType?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeBindingType(): BindingType = NativeBuffer(this).decodeBindingType()

public fun NativeBuffer.decodeBindingType(): BindingType {
  val rawValue = nextInt()
  return BindingType.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of BindingType")
}

public fun NativeBuffer.decodeGpuBindingType(): BindingType {
  val rawValue = nextInt()
  return BindingType.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of BindingType")
}

public val BindingType.`value`: Int
  get() = rawValue
