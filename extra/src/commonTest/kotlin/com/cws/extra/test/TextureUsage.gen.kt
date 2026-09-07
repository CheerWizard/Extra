package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun TextureUsage?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun TextureUsage?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun TextureUsage?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun TextureUsage?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun TextureUsage?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeTextureUsage(): TextureUsage = NativeBuffer(this).decodeTextureUsage()

public fun NativeBuffer.decodeTextureUsage(): TextureUsage {
  val rawValue = nextInt()
  return TextureUsage.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of TextureUsage")
}

public fun NativeBuffer.decodeGpuTextureUsage(): TextureUsage {
  val rawValue = nextInt()
  return TextureUsage.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of TextureUsage")
}

public val TextureUsage.`value`: Int
  get() = rawValue
