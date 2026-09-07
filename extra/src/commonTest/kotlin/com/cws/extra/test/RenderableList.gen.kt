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

public fun RenderableList?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else textureId.sizeBytes(memoryLayout)

public fun RenderableList?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else textureId.sizeBytesPacked(memoryLayout)

public fun RenderableList?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun RenderableList?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun RenderableList?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun RenderableList?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encode(i, buffer)
  }
}

public fun RenderableList?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodeGpu(i, buffer)
  }
}

public fun RenderableList?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodePacked(i, buffer)
  }
}

public fun RenderableList?.encode(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(textureId[i])
}

public fun RenderableList?.encodeGpu(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(textureId[i])
}

public fun RenderableList.encodePacked(i: Int, buffer: NativeBuffer) {
  buffer.pushInt(textureId[i])
}

public fun NativeBuffer.decodeRenderableList(): RenderableList {
  val decodedSize = nextInt()
  val buffer = this
  return RenderableList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
    }
  }
}

public fun NativeBuffer.decodeGpuRenderableList(): RenderableList {
  val decodedSize = nextInt()
  val buffer = this
  return RenderableList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
    }
  }
}

public fun RenderableList.decode(i: Int, buffer: NativeBuffer) {
    textureId.decode(i, buffer)
}

public fun RenderableList.decodeGpu(i: Int, buffer: NativeBuffer) {
    textureId.decodeGpu(i, buffer)
}

public fun ByteArray.decodeRenderableList(): RenderableList = NativeBuffer(this).decodeRenderableList()
