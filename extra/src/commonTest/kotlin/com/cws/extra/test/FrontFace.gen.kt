package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun FrontFace?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun FrontFace?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun FrontFace?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun FrontFace?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun FrontFace?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeFrontFace(): FrontFace = NativeBuffer(this).decodeFrontFace()

public fun NativeBuffer.decodeFrontFace(): FrontFace {
  val rawValue = nextInt()
  return FrontFace.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of FrontFace")
}

public fun NativeBuffer.decodeGpuFrontFace(): FrontFace {
  val rawValue = nextInt()
  return FrontFace.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of FrontFace")
}

public val FrontFace.`value`: Int
  get() = rawValue
