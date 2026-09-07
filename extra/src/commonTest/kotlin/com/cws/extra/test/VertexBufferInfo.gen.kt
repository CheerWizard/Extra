package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import com.cws.extra.test.decodeAttribute
import com.cws.extra.test.decodeGpuAttribute
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun VertexBufferInfo?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES + name.orEmpty().sizeBytesUtf8(memoryLayout) + Int.SIZE_BYTES + attributes.sumOf { it.sizeBytes(memoryLayout) } + Int.SIZE_BYTES + Int.SIZE_BYTES

public fun VertexBufferInfo?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else name.orEmpty().sizeBytesUtf8(memoryLayout) + attributes.sumOf { it.sizeBytesPacked(memoryLayout) } + Int.SIZE_BYTES + Int.SIZE_BYTES

public fun VertexBufferInfo?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun VertexBufferInfo?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun VertexBufferInfo?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun VertexBufferInfo?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  buffer.pushCollection(attributes) { it.encode(buffer) }
  buffer.pushInt(vertexCount)
  buffer.pushInt(slot)
}

public fun VertexBufferInfo?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  buffer.pushCollection(attributes) { it.encodeGpu(buffer) }
  buffer.pushInt(vertexCount)
  buffer.pushInt(slot)
}

public fun VertexBufferInfo?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushPackedStringUtf8(name)
  buffer.pushPackedCollection(attributes) { it.encodeGpu(buffer) }
  buffer.pushInt(vertexCount)
  buffer.pushInt(slot)
}

public fun NativeBuffer.decodeVertexBufferInfo(): VertexBufferInfo = VertexBufferInfo(
  nextStringUtf8(),
  nextList { this.decodeAttribute() },
  nextInt(),
  nextInt(),
)

public fun NativeBuffer.decodeGpuVertexBufferInfo(): VertexBufferInfo = VertexBufferInfo(
  nextStringUtf8(),
  nextList { this.decodeGpuAttribute() },
  nextInt(),
  nextInt(),
)

public fun ByteArray.decodeVertexBufferInfo(): VertexBufferInfo = NativeBuffer(this).decodeVertexBufferInfo()
