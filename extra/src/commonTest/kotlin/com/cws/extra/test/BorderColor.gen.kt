package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun BorderColor?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun BorderColor?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun BorderColor?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun BorderColor?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun BorderColor?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeBorderColor(): BorderColor = NativeBuffer(this).decodeBorderColor()

public fun NativeBuffer.decodeBorderColor(): BorderColor {
  val rawValue = nextInt()
  return BorderColor.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of BorderColor")
}

public fun NativeBuffer.decodeGpuBorderColor(): BorderColor {
  val rawValue = nextInt()
  return BorderColor.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of BorderColor")
}

public val BorderColor.`value`: Int
  get() = rawValue
