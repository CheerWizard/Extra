package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun IndexSize?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun IndexSize?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun IndexSize?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun IndexSize?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun IndexSize?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeIndexSize(): IndexSize = NativeBuffer(this).decodeIndexSize()

public fun NativeBuffer.decodeIndexSize(): IndexSize {
  val rawValue = nextInt()
  return IndexSize.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of IndexSize")
}

public fun NativeBuffer.decodeGpuIndexSize(): IndexSize {
  val rawValue = nextInt()
  return IndexSize.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of IndexSize")
}

public val IndexSize.`value`: Int
  get() = rawValue
