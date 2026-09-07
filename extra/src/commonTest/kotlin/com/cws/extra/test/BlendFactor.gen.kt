package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun BlendFactor?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun BlendFactor?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun BlendFactor?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun BlendFactor?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun BlendFactor?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeBlendFactor(): BlendFactor = NativeBuffer(this).decodeBlendFactor()

public fun NativeBuffer.decodeBlendFactor(): BlendFactor {
  val rawValue = nextInt()
  return BlendFactor.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of BlendFactor")
}

public fun NativeBuffer.decodeGpuBlendFactor(): BlendFactor {
  val rawValue = nextInt()
  return BlendFactor.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of BlendFactor")
}

public val BlendFactor.`value`: Int
  get() = rawValue
