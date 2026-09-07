package com.cws.extra.math.matrices

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

public fun Mat2List?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else m00.sizeBytes(memoryLayout) + m01.sizeBytes(memoryLayout) + m10.sizeBytes(memoryLayout) + m11.sizeBytes(memoryLayout)

public fun Mat2List?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else m00.sizeBytesPacked(memoryLayout) + m01.sizeBytesPacked(memoryLayout) + m10.sizeBytesPacked(memoryLayout) + m11.sizeBytesPacked(memoryLayout)

public fun Mat2List?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun Mat2List?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun Mat2List?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun Mat2List?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
  }
}

public fun Mat2List?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
  }
}

public fun Mat2List?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
  }
}

public fun Mat2List?.encode(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(m00[i])
  buffer.pushFloat(m01[i])
  buffer.pushFloat(m10[i])
  buffer.pushFloat(m11[i])
}

public fun Mat2List?.encodeGpu(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(m00[i])
  buffer.pushFloat(m01[i])
  buffer.pushFloat(m10[i])
  buffer.pushFloat(m11[i])
}

public fun Mat2List.encodePacked(i: Int, buffer: NativeBuffer) {
  buffer.pushFloat(m00[i])
  buffer.pushFloat(m01[i])
  buffer.pushFloat(m10[i])
  buffer.pushFloat(m11[i])
}

public fun NativeBuffer.decodeMat2List(): Mat2List {
  val decodedSize = nextInt()
  val buffer = this
  return Mat2List(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun NativeBuffer.decodeGpuMat2List(): Mat2List {
  val decodedSize = nextInt()
  val buffer = this
  return Mat2List(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun Mat2List.decode(i: Int, buffer: NativeBuffer) {
    m00.decode(i, buffer)
    m01.decode(i, buffer)
    m10.decode(i, buffer)
    m11.decode(i, buffer)
}

public fun Mat2List.decodeGpu(i: Int, buffer: NativeBuffer) {
    m00.decodeGpu(i, buffer)
    m01.decodeGpu(i, buffer)
    m10.decodeGpu(i, buffer)
    m11.decodeGpu(i, buffer)
}

public fun ByteArray.decodeMat2List(): Mat2List = NativeBuffer(this).decodeMat2List()
