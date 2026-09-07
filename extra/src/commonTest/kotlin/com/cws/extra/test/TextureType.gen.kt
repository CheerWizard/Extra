package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun TextureType?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun TextureType?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun TextureType?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun TextureType?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun TextureType?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeTextureType(): TextureType = NativeBuffer(this).decodeTextureType()

public fun NativeBuffer.decodeTextureType(): TextureType {
  val rawValue = nextInt()
  return TextureType.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of TextureType")
}

public fun NativeBuffer.decodeGpuTextureType(): TextureType {
  val rawValue = nextInt()
  return TextureType.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of TextureType")
}

public val TextureType.`value`: Int
  get() = rawValue
