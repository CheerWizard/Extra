package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun TextureFormat?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun TextureFormat?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun TextureFormat?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun TextureFormat?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun TextureFormat?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeTextureFormat(): TextureFormat = NativeBuffer(this).decodeTextureFormat()

public fun NativeBuffer.decodeTextureFormat(): TextureFormat {
  val rawValue = nextInt()
  return TextureFormat.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of TextureFormat")
}

public fun NativeBuffer.decodeGpuTextureFormat(): TextureFormat {
  val rawValue = nextInt()
  return TextureFormat.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of TextureFormat")
}

public val TextureFormat.`value`: Int
  get() = rawValue
