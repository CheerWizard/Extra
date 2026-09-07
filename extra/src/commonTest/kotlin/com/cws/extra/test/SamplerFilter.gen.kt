package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun SamplerFilter?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun SamplerFilter?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun SamplerFilter?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun SamplerFilter?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun SamplerFilter?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeSamplerFilter(): SamplerFilter = NativeBuffer(this).decodeSamplerFilter()

public fun NativeBuffer.decodeSamplerFilter(): SamplerFilter {
  val rawValue = nextInt()
  return SamplerFilter.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of SamplerFilter")
}

public fun NativeBuffer.decodeGpuSamplerFilter(): SamplerFilter {
  val rawValue = nextInt()
  return SamplerFilter.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of SamplerFilter")
}

public val SamplerFilter.`value`: Int
  get() = rawValue
