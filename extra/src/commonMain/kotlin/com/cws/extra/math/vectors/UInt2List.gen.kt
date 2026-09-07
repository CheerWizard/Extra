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

public fun UInt2List?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else x.sizeBytes(memoryLayout) + y.sizeBytes(memoryLayout)

public fun UInt2List?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else x.sizeBytesPacked(memoryLayout) + y.sizeBytesPacked(memoryLayout)

public fun UInt2List?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun UInt2List?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun UInt2List?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun UInt2List?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encode(i, buffer)
       encode(i, buffer)
  }
}

public fun UInt2List?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
  }
}

public fun UInt2List?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodePacked(i, buffer)
       encodePacked(i, buffer)
  }
}

public fun UInt2List?.encode(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushUInt(x[i])
  buffer.pushUInt(y[i])
}

public fun UInt2List?.encodeGpu(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushUInt(x[i])
  buffer.pushUInt(y[i])
}

public fun UInt2List.encodePacked(i: Int, buffer: NativeBuffer) {
  buffer.pushUInt(x[i])
  buffer.pushUInt(y[i])
}

public fun NativeBuffer.decodeUInt2List(): UInt2List {
  val decodedSize = nextInt()
  val buffer = this
  return UInt2List(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun NativeBuffer.decodeGpuUInt2List(): UInt2List {
  val decodedSize = nextInt()
  val buffer = this
  return UInt2List(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun UInt2List.decode(i: Int, buffer: NativeBuffer) {
    x.decode(i, buffer)
    y.decode(i, buffer)
}

public fun UInt2List.decodeGpu(i: Int, buffer: NativeBuffer) {
    x.decodeGpu(i, buffer)
    y.decodeGpu(i, buffer)
}

public fun ByteArray.decodeUInt2List(): UInt2List = NativeBuffer(this).decodeUInt2List()
