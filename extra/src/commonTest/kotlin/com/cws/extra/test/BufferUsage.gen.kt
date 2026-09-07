package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun BufferUsage?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun BufferUsage?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun BufferUsage?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun BufferUsage?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun BufferUsage?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeBufferUsage(): BufferUsage = NativeBuffer(this).decodeBufferUsage()

public fun NativeBuffer.decodeBufferUsage(): BufferUsage {
  val rawValue = nextInt()
  return BufferUsage.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of BufferUsage")
}

public fun NativeBuffer.decodeGpuBufferUsage(): BufferUsage {
  val rawValue = nextInt()
  return BufferUsage.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of BufferUsage")
}

public val BufferUsage.`value`: Int
  get() = rawValue
