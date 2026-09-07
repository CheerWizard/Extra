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

public fun TransformList?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else x.sizeBytes(memoryLayout) + y.sizeBytes(memoryLayout) + z.sizeBytes(memoryLayout) + rotation.sizeBytes(memoryLayout) + scale.sizeBytes(memoryLayout)

public fun TransformList?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else x.sizeBytesPacked(memoryLayout) + y.sizeBytesPacked(memoryLayout) + z.sizeBytesPacked(memoryLayout) + rotation.sizeBytesPacked(memoryLayout) + scale.sizeBytesPacked(memoryLayout)

public fun TransformList?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun TransformList?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun TransformList?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun TransformList?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
  }
}

public fun TransformList?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
  }
}

public fun TransformList?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
  }
}

public fun TransformList?.encode(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(x[i])
  buffer.pushFloat(y[i])
  buffer.pushFloat(z[i])
  buffer.pushFloat(rotation[i])
  buffer.pushFloat(scale[i])
}

public fun TransformList?.encodeGpu(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(x[i])
  buffer.pushFloat(y[i])
  buffer.pushFloat(z[i])
  buffer.pushFloat(rotation[i])
  buffer.pushFloat(scale[i])
}

public fun TransformList.encodePacked(i: Int, buffer: NativeBuffer) {
  buffer.pushFloat(x[i])
  buffer.pushFloat(y[i])
  buffer.pushFloat(z[i])
  buffer.pushFloat(rotation[i])
  buffer.pushFloat(scale[i])
}

public fun NativeBuffer.decodeTransformList(): TransformList {
  val decodedSize = nextInt()
  val buffer = this
  return TransformList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun NativeBuffer.decodeGpuTransformList(): TransformList {
  val decodedSize = nextInt()
  val buffer = this
  return TransformList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun TransformList.decode(i: Int, buffer: NativeBuffer) {
    x.decode(i, buffer)
    y.decode(i, buffer)
    z.decode(i, buffer)
    rotation.decode(i, buffer)
    scale.decode(i, buffer)
}

public fun TransformList.decodeGpu(i: Int, buffer: NativeBuffer) {
    x.decodeGpu(i, buffer)
    y.decodeGpu(i, buffer)
    z.decodeGpu(i, buffer)
    rotation.decodeGpu(i, buffer)
    scale.decodeGpu(i, buffer)
}

public fun ByteArray.decodeTransformList(): TransformList = NativeBuffer(this).decodeTransformList()
