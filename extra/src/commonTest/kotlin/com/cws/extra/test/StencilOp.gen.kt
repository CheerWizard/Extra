package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun StencilOp?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun StencilOp?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun StencilOp?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun StencilOp?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun StencilOp?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeStencilOp(): StencilOp = NativeBuffer(this).decodeStencilOp()

public fun NativeBuffer.decodeStencilOp(): StencilOp {
  val rawValue = nextInt()
  return StencilOp.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of StencilOp")
}

public fun NativeBuffer.decodeGpuStencilOp(): StencilOp {
  val rawValue = nextInt()
  return StencilOp.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of StencilOp")
}

public val StencilOp.`value`: Int
  get() = rawValue
