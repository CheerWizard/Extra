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
import kotlin.ByteArray
import kotlin.Int

public fun CollisionList?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else impulse.sizeBytes(memoryLayout) + damageScale.sizeBytes(memoryLayout)

public fun CollisionList?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else impulse.sizeBytesPacked(memoryLayout) + damageScale.sizeBytesPacked(memoryLayout)

public fun CollisionList?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun CollisionList?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun CollisionList?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun CollisionList?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encode(i, buffer)
       encode(i, buffer)
  }
}

public fun CollisionList?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
  }
}

public fun CollisionList?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodePacked(i, buffer)
       encodePacked(i, buffer)
  }
}

public fun CollisionList?.encode(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(impulse[i])
  buffer.pushFloat(damageScale[i])
}

public fun CollisionList?.encodeGpu(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(impulse[i])
  buffer.pushFloat(damageScale[i])
}

public fun CollisionList.encodePacked(i: Int, buffer: NativeBuffer) {
  buffer.pushFloat(impulse[i])
  buffer.pushFloat(damageScale[i])
}

public fun NativeBuffer.decodeCollisionList(): CollisionList {
  val decodedSize = nextInt()
  val buffer = this
  return CollisionList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun NativeBuffer.decodeGpuCollisionList(): CollisionList {
  val decodedSize = nextInt()
  val buffer = this
  return CollisionList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun CollisionList.decode(i: Int, buffer: NativeBuffer) {
    impulse.decode(i, buffer)
    damageScale.decode(i, buffer)
}

public fun CollisionList.decodeGpu(i: Int, buffer: NativeBuffer) {
    impulse.decodeGpu(i, buffer)
    damageScale.decodeGpu(i, buffer)
}

public fun ByteArray.decodeCollisionList(): CollisionList = NativeBuffer(this).decodeCollisionList()
