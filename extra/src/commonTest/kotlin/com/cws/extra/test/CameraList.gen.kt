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

public fun CameraList?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else fov.sizeBytes(memoryLayout)

public fun CameraList?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else fov.sizeBytesPacked(memoryLayout)

public fun CameraList?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun CameraList?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun CameraList?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun CameraList?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encode(i, buffer)
  }
}

public fun CameraList?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodeGpu(i, buffer)
  }
}

public fun CameraList?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodePacked(i, buffer)
  }
}

public fun CameraList?.encode(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(fov[i])
}

public fun CameraList?.encodeGpu(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(fov[i])
}

public fun CameraList.encodePacked(i: Int, buffer: NativeBuffer) {
  buffer.pushFloat(fov[i])
}

public fun NativeBuffer.decodeCameraList(): CameraList {
  val decodedSize = nextInt()
  val buffer = this
  return CameraList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
    }
  }
}

public fun NativeBuffer.decodeGpuCameraList(): CameraList {
  val decodedSize = nextInt()
  val buffer = this
  return CameraList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
    }
  }
}

public fun CameraList.decode(i: Int, buffer: NativeBuffer) {
    fov.decode(i, buffer)
}

public fun CameraList.decodeGpu(i: Int, buffer: NativeBuffer) {
    fov.decodeGpu(i, buffer)
}

public fun ByteArray.decodeCameraList(): CameraList = NativeBuffer(this).decodeCameraList()
