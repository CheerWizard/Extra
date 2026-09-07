package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun CompareOp?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun CompareOp?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun CompareOp?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun CompareOp?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun CompareOp?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeCompareOp(): CompareOp = NativeBuffer(this).decodeCompareOp()

public fun NativeBuffer.decodeCompareOp(): CompareOp {
  val rawValue = nextInt()
  return CompareOp.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of CompareOp")
}

public fun NativeBuffer.decodeGpuCompareOp(): CompareOp {
  val rawValue = nextInt()
  return CompareOp.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of CompareOp")
}

public val CompareOp.`value`: Int
  get() = rawValue
