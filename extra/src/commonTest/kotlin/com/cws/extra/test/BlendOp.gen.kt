package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun BlendOp?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun BlendOp?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun BlendOp?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun BlendOp?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun BlendOp?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeBlendOp(): BlendOp = NativeBuffer(this).decodeBlendOp()

public fun NativeBuffer.decodeBlendOp(): BlendOp {
  val rawValue = nextInt()
  return BlendOp.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of BlendOp")
}

public fun NativeBuffer.decodeGpuBlendOp(): BlendOp {
  val rawValue = nextInt()
  return BlendOp.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of BlendOp")
}

public val BlendOp.`value`: Int
  get() = rawValue
