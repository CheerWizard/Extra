package com.cws.extra.math.vectors

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

public fun QuaternionList?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else x.sizeBytes(memoryLayout) + y.sizeBytes(memoryLayout) + z.sizeBytes(memoryLayout) + w.sizeBytes(memoryLayout)

public fun QuaternionList?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else x.sizeBytesPacked(memoryLayout) + y.sizeBytesPacked(memoryLayout) + z.sizeBytesPacked(memoryLayout) + w.sizeBytesPacked(memoryLayout)

public fun QuaternionList?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun QuaternionList?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun QuaternionList?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun QuaternionList?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
  }
}

public fun QuaternionList?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
  }
}

public fun QuaternionList?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
  }
}

public fun QuaternionList?.encode(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(x[i])
  buffer.pushFloat(y[i])
  buffer.pushFloat(z[i])
  buffer.pushFloat(w[i])
}

public fun QuaternionList?.encodeGpu(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(x[i])
  buffer.pushFloat(y[i])
  buffer.pushFloat(z[i])
  buffer.pushFloat(w[i])
}

public fun QuaternionList.encodePacked(i: Int, buffer: NativeBuffer) {
  buffer.pushFloat(x[i])
  buffer.pushFloat(y[i])
  buffer.pushFloat(z[i])
  buffer.pushFloat(w[i])
}

public fun NativeBuffer.decodeQuaternionList(): QuaternionList {
  val decodedSize = nextInt()
  val buffer = this
  return QuaternionList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun NativeBuffer.decodeGpuQuaternionList(): QuaternionList {
  val decodedSize = nextInt()
  val buffer = this
  return QuaternionList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun QuaternionList.decode(i: Int, buffer: NativeBuffer) {
    x.decode(i, buffer)
    y.decode(i, buffer)
    z.decode(i, buffer)
    w.decode(i, buffer)
}

public fun QuaternionList.decodeGpu(i: Int, buffer: NativeBuffer) {
    x.decodeGpu(i, buffer)
    y.decodeGpu(i, buffer)
    z.decodeGpu(i, buffer)
    w.decodeGpu(i, buffer)
}

public fun ByteArray.decodeQuaternionList(): QuaternionList = NativeBuffer(this).decodeQuaternionList()
