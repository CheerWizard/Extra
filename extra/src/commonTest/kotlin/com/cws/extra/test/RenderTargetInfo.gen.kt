package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import com.cws.extra.test.decodeColorAttachment
import com.cws.extra.test.decodeDepthAttachment
import com.cws.extra.test.decodeGpuColorAttachment
import com.cws.extra.test.decodeGpuDepthAttachment
import com.cws.extra.test.decodeGpuStencilAttachment
import com.cws.extra.test.decodeStencilAttachment
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun RenderTargetInfo?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES + name.orEmpty().sizeBytesUtf8(memoryLayout) + Boolean.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + colorAttachments.sumOf { it.sizeBytes(memoryLayout) } + depthAttachment.sizeBytes(memoryLayout) + stencilAttachment.sizeBytes(memoryLayout)

public fun RenderTargetInfo?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else name.orEmpty().sizeBytesUtf8(memoryLayout) + Boolean.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + colorAttachments.sumOf { it.sizeBytesPacked(memoryLayout) } + depthAttachment.sizeBytesPacked(memoryLayout) + stencilAttachment.sizeBytesPacked(memoryLayout)

public fun RenderTargetInfo?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun RenderTargetInfo?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun RenderTargetInfo?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun RenderTargetInfo?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  buffer.pushBoolean(isSwapchain)
  buffer.pushInt(x)
  buffer.pushInt(y)
  buffer.pushInt(width)
  buffer.pushInt(height)
  buffer.pushInt(depth)
  buffer.pushCollection(colorAttachments) { it.encode(buffer) }
  depthAttachment.encode(buffer)
  stencilAttachment.encode(buffer)
}

public fun RenderTargetInfo?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  buffer.pushBoolean(isSwapchain)
  buffer.pushInt(x)
  buffer.pushInt(y)
  buffer.pushInt(width)
  buffer.pushInt(height)
  buffer.pushInt(depth)
  buffer.pushCollection(colorAttachments) { it.encodeGpu(buffer) }
  depthAttachment.encodeGpu(buffer)
  stencilAttachment.encodeGpu(buffer)
}

public fun RenderTargetInfo?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushPackedStringUtf8(name)
  buffer.pushBoolean(isSwapchain)
  buffer.pushInt(x)
  buffer.pushInt(y)
  buffer.pushInt(width)
  buffer.pushInt(height)
  buffer.pushInt(depth)
  buffer.pushPackedCollection(colorAttachments) { it.encodeGpu(buffer) }
  depthAttachment.encodePacked(buffer)
  stencilAttachment.encodePacked(buffer)
}

public fun NativeBuffer.decodeRenderTargetInfo(): RenderTargetInfo = RenderTargetInfo(
  nextStringUtf8(),
  nextBoolean(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextList { this.decodeColorAttachment() },
  decodeDepthAttachment(),
  decodeStencilAttachment(),
)

public fun NativeBuffer.decodeGpuRenderTargetInfo(): RenderTargetInfo = RenderTargetInfo(
  nextStringUtf8(),
  nextBoolean(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextList { this.decodeGpuColorAttachment() },
  decodeGpuDepthAttachment(),
  decodeGpuStencilAttachment(),
)

public fun ByteArray.decodeRenderTargetInfo(): RenderTargetInfo = NativeBuffer(this).decodeRenderTargetInfo()
