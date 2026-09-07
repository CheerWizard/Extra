package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun PolygonMode?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun PolygonMode?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun PolygonMode?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun PolygonMode?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun PolygonMode?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodePolygonMode(): PolygonMode = NativeBuffer(this).decodePolygonMode()

public fun NativeBuffer.decodePolygonMode(): PolygonMode {
  val rawValue = nextInt()
  return PolygonMode.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of PolygonMode")
}

public fun NativeBuffer.decodeGpuPolygonMode(): PolygonMode {
  val rawValue = nextInt()
  return PolygonMode.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of PolygonMode")
}

public val PolygonMode.`value`: Int
  get() = rawValue
