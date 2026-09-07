package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.lists.decode
import com.cws.extra.lists.decodeGpu
import com.cws.extra.lists.sizeBytes
import com.cws.extra.lists.sizeBytesPacked
import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import com.cws.extra.test.decode
import com.cws.extra.test.decodeGpu
import com.cws.extra.test.decodeGpuHeroClass
import com.cws.extra.test.decodeHeroClass
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun HeroList?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else id.sizeBytes(memoryLayout) + experience.sizeBytes(memoryLayout) + speed.sizeBytes(memoryLayout) + weight.sizeBytes(memoryLayout) + level.sizeBytes(memoryLayout) + prestige.sizeBytes(memoryLayout) + enabled.sizeBytes(memoryLayout) + symbol.sizeBytes(memoryLayout) + Int.SIZE_BYTES + name.sumOf { Int.SIZE_BYTES + it.orEmpty().sizeBytesUtf8(memoryLayout) } + Int.SIZE_BYTES + tag.sumOf { Int.SIZE_BYTES + it.orEmpty().sizeBytesUtf8(memoryLayout) } + Int.SIZE_BYTES + heroClass.sumOf { it.sizeBytes(memoryLayout) } + transform.sizeBytes(memoryLayout) + stats.sizeBytes(memoryLayout) + Int.SIZE_BYTES + nickname.sumOf { Int.SIZE_BYTES + it.orEmpty().sizeBytesUtf8(memoryLayout) }

public fun HeroList?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else id.sizeBytesPacked(memoryLayout) + experience.sizeBytesPacked(memoryLayout) + speed.sizeBytesPacked(memoryLayout) + weight.sizeBytesPacked(memoryLayout) + level.sizeBytesPacked(memoryLayout) + prestige.sizeBytesPacked(memoryLayout) + enabled.sizeBytesPacked(memoryLayout) + symbol.sizeBytesPacked(memoryLayout) + name.sumOf { Int.SIZE_BYTES + it.orEmpty().sizeBytesUtf8(memoryLayout) } + tag.sumOf { Int.SIZE_BYTES + it.orEmpty().sizeBytesUtf8(memoryLayout) } + heroClass.sumOf { it.sizeBytesPacked(memoryLayout) } + transform.sizeBytesPacked(memoryLayout) + stats.sizeBytesPacked(memoryLayout) + nickname.sumOf { Int.SIZE_BYTES + it.orEmpty().sizeBytesUtf8(memoryLayout) }

public fun HeroList?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun HeroList?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun HeroList?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun HeroList?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
  }
}

public fun HeroList?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
  }
}

public fun HeroList?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
  }
}

public fun HeroList?.encode(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(id[i])
  buffer.pushLong(experience[i])
  buffer.pushFloat(speed[i])
  buffer.pushDouble(weight[i])
  buffer.pushShort(level[i])
  buffer.pushByte(prestige[i])
  buffer.pushBoolean(enabled[i])
  buffer.pushChar(symbol[i])
  buffer.pushGenericList(i, name) { buffer.pushStringUtf8(it) }
  buffer.pushGenericList(i, tag) { buffer.pushStringUtf8(it) }
  buffer.pushGenericList(i, heroClass) { it.encode(buffer) }
  transform.encode(i, buffer)
  stats.encode(i, buffer)
  buffer.pushGenericList(i, nickname) { buffer.pushStringUtf8(it) }
}

public fun HeroList?.encodeGpu(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(id[i])
  buffer.pushLong(experience[i])
  buffer.pushFloat(speed[i])
  buffer.pushDouble(weight[i])
  buffer.pushShort(level[i])
  buffer.pushByte(prestige[i])
  buffer.pushBoolean(enabled[i])
  buffer.pushChar(symbol[i])
  buffer.pushGenericList(i, name) { buffer.pushStringUtf8(it) }
  buffer.pushGenericList(i, tag) { buffer.pushStringUtf8(it) }
  buffer.pushGenericList(i, heroClass) { it.encodeGpu(buffer) }
  transform.encodeGpu(i, buffer)
  stats.encodeGpu(i, buffer)
  buffer.pushGenericList(i, nickname) { buffer.pushStringUtf8(it) }
}

public fun HeroList.encodePacked(i: Int, buffer: NativeBuffer) {
  buffer.pushInt(id[i])
  buffer.pushLong(experience[i])
  buffer.pushFloat(speed[i])
  buffer.pushDouble(weight[i])
  buffer.pushShort(level[i])
  buffer.pushByte(prestige[i])
  buffer.pushBoolean(enabled[i])
  buffer.pushChar(symbol[i])
  buffer.pushPackedGenericList(i, name) { buffer.pushStringUtf8(it) }
  buffer.pushPackedGenericList(i, tag) { buffer.pushStringUtf8(it) }
  buffer.pushPackedGenericList(i, heroClass) { it.encodeGpu(buffer) }
  transform.encodePacked(i, buffer)
  stats.encodePacked(i, buffer)
  buffer.pushPackedGenericList(i, nickname) { buffer.pushStringUtf8(it) }
}

public fun NativeBuffer.decodeHeroList(): HeroList {
  val decodedSize = nextInt()
  val buffer = this
  return HeroList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun NativeBuffer.decodeGpuHeroList(): HeroList {
  val decodedSize = nextInt()
  val buffer = this
  return HeroList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun HeroList.decode(i: Int, buffer: NativeBuffer) {
    id.decode(i, buffer)
    experience.decode(i, buffer)
    speed.decode(i, buffer)
    weight.decode(i, buffer)
    level.decode(i, buffer)
    prestige.decode(i, buffer)
    enabled.decode(i, buffer)
    symbol.decode(i, buffer)
    name[i].let { buffer.nextStringUtf8() }
    tag[i].let { buffer.nextStringUtf8() }
    heroClass[i].let { buffer.decodeHeroClass() }
    transform.decode(i, buffer)
    stats.decode(i, buffer)
    nickname[i].let { buffer.nextStringUtf8() }
}

public fun HeroList.decodeGpu(i: Int, buffer: NativeBuffer) {
    id.decodeGpu(i, buffer)
    experience.decodeGpu(i, buffer)
    speed.decodeGpu(i, buffer)
    weight.decodeGpu(i, buffer)
    level.decodeGpu(i, buffer)
    prestige.decodeGpu(i, buffer)
    enabled.decodeGpu(i, buffer)
    symbol.decodeGpu(i, buffer)
    name[i].let { buffer.nextStringUtf8() }
    tag[i].let { buffer.nextStringUtf8() }
    heroClass[i].let { buffer.decodeGpuHeroClass() }
    transform.decodeGpu(i, buffer)
    stats.decodeGpu(i, buffer)
    nickname[i].let { buffer.nextStringUtf8() }
}

public fun ByteArray.decodeHeroList(): HeroList = NativeBuffer(this).decodeHeroList()
