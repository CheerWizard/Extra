package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun SamplerMipMapMode?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun SamplerMipMapMode?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun SamplerMipMapMode?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun SamplerMipMapMode?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun SamplerMipMapMode?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeSamplerMipMapMode(): SamplerMipMapMode = NativeBuffer(this).decodeSamplerMipMapMode()

public fun NativeBuffer.decodeSamplerMipMapMode(): SamplerMipMapMode {
  val rawValue = nextInt()
  return SamplerMipMapMode.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of SamplerMipMapMode")
}

public fun NativeBuffer.decodeGpuSamplerMipMapMode(): SamplerMipMapMode {
  val rawValue = nextInt()
  return SamplerMipMapMode.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of SamplerMipMapMode")
}

public val SamplerMipMapMode.`value`: Int
  get() = rawValue
