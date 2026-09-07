package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun MemoryType?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun MemoryType?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun MemoryType?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun MemoryType?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun MemoryType?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeMemoryType(): MemoryType = NativeBuffer(this).decodeMemoryType()

public fun NativeBuffer.decodeMemoryType(): MemoryType {
  val rawValue = nextInt()
  return MemoryType.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of MemoryType")
}

public fun NativeBuffer.decodeGpuMemoryType(): MemoryType {
  val rawValue = nextInt()
  return MemoryType.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of MemoryType")
}

public val MemoryType.`value`: Int
  get() = rawValue
