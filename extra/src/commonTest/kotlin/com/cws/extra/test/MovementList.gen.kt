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

public fun MovementList?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else speed.sizeBytes(memoryLayout)

public fun MovementList?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else speed.sizeBytesPacked(memoryLayout)

public fun MovementList?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun MovementList?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun MovementList?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun MovementList?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encode(i, buffer)
  }
}

public fun MovementList?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodeGpu(i, buffer)
  }
}

public fun MovementList?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodePacked(i, buffer)
  }
}

public fun MovementList?.encode(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(speed[i])
}

public fun MovementList?.encodeGpu(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(speed[i])
}

public fun MovementList.encodePacked(i: Int, buffer: NativeBuffer) {
  buffer.pushFloat(speed[i])
}

public fun NativeBuffer.decodeMovementList(): MovementList {
  val decodedSize = nextInt()
  val buffer = this
  return MovementList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
    }
  }
}

public fun NativeBuffer.decodeGpuMovementList(): MovementList {
  val decodedSize = nextInt()
  val buffer = this
  return MovementList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
    }
  }
}

public fun MovementList.decode(i: Int, buffer: NativeBuffer) {
    speed.decode(i, buffer)
}

public fun MovementList.decodeGpu(i: Int, buffer: NativeBuffer) {
    speed.decodeGpu(i, buffer)
}

public fun ByteArray.decodeMovementList(): MovementList = NativeBuffer(this).decodeMovementList()
