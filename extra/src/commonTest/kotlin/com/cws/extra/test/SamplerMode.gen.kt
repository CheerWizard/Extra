package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun SamplerMode?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun SamplerMode?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun SamplerMode?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun SamplerMode?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun SamplerMode?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeSamplerMode(): SamplerMode = NativeBuffer(this).decodeSamplerMode()

public fun NativeBuffer.decodeSamplerMode(): SamplerMode {
  val rawValue = nextInt()
  return SamplerMode.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of SamplerMode")
}

public fun NativeBuffer.decodeGpuSamplerMode(): SamplerMode {
  val rawValue = nextInt()
  return SamplerMode.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of SamplerMode")
}

public val SamplerMode.`value`: Int
  get() = rawValue
