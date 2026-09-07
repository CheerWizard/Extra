package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun HeroClass?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun HeroClass?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun HeroClass?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun HeroClass?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun HeroClass?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun ByteArray.decodeHeroClass(): HeroClass = NativeBuffer(this).decodeHeroClass()

public fun NativeBuffer.decodeHeroClass(): HeroClass {
  val ordinal = nextInt()
  return HeroClass.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of HeroClass")
}

public fun NativeBuffer.decodeGpuHeroClass(): HeroClass {
  val ordinal = nextInt()
  return HeroClass.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of HeroClass")
}

public val HeroClass.`value`: Int
  get() = ordinal
