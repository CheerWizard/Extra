package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun AccessFlag?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun AccessFlag?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun AccessFlag?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun AccessFlag?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun AccessFlag?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeAccessFlag(): AccessFlag = NativeBuffer(this).decodeAccessFlag()

public fun NativeBuffer.decodeAccessFlag(): AccessFlag {
  val rawValue = nextInt()
  return AccessFlag.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of AccessFlag")
}

public fun NativeBuffer.decodeGpuAccessFlag(): AccessFlag {
  val rawValue = nextInt()
  return AccessFlag.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of AccessFlag")
}

public val AccessFlag.`value`: Int
  get() = rawValue
