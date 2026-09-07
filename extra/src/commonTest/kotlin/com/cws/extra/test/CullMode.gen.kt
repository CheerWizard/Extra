package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun CullMode?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun CullMode?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun CullMode?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun CullMode?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun CullMode?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeCullMode(): CullMode = NativeBuffer(this).decodeCullMode()

public fun NativeBuffer.decodeCullMode(): CullMode {
  val rawValue = nextInt()
  return CullMode.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of CullMode")
}

public fun NativeBuffer.decodeGpuCullMode(): CullMode {
  val rawValue = nextInt()
  return CullMode.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of CullMode")
}

public val CullMode.`value`: Int
  get() = rawValue
