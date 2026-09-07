package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.math.vectors.decodeFloat4
import com.cws.extra.math.vectors.decodeGpuFloat4
import com.cws.extra.math.vectors.encode
import com.cws.extra.math.vectors.encodeGpu
import com.cws.extra.math.vectors.encodePacked
import com.cws.extra.math.vectors.sizeBytes
import com.cws.extra.math.vectors.sizeBytesPacked
import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import com.cws.extra.test.decodeGpuSurfaceHandle
import com.cws.extra.test.decodeSurfaceHandle
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun RenderContextInfo?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES + applicationName.orEmpty().sizeBytesUtf8(memoryLayout) + Int.SIZE_BYTES + engineName.orEmpty().sizeBytesUtf8(memoryLayout) + Int.SIZE_BYTES + swapchainName.orEmpty().sizeBytesUtf8(memoryLayout) + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Boolean.SIZE_BYTES + surface.sizeBytes(memoryLayout) + clearColor.sizeBytes(memoryLayout) + Boolean.SIZE_BYTES + Boolean.SIZE_BYTES + Int.SIZE_BYTES

public fun RenderContextInfo?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else applicationName.orEmpty().sizeBytesUtf8(memoryLayout) + engineName.orEmpty().sizeBytesUtf8(memoryLayout) + swapchainName.orEmpty().sizeBytesUtf8(memoryLayout) + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Boolean.SIZE_BYTES + surface.sizeBytesPacked(memoryLayout) + clearColor.sizeBytesPacked(memoryLayout) + Boolean.SIZE_BYTES + Boolean.SIZE_BYTES + Int.SIZE_BYTES

public fun RenderContextInfo?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun RenderContextInfo?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun RenderContextInfo?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun RenderContextInfo?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(applicationName)
  buffer.pushStringUtf8(engineName)
  buffer.pushStringUtf8(swapchainName)
  buffer.pushInt(x)
  buffer.pushInt(y)
  buffer.pushInt(width)
  buffer.pushInt(height)
  buffer.pushInt(frameCount)
  buffer.pushBoolean(isDebug)
  surface.encode(buffer)
  clearColor.encode(buffer)
  buffer.pushBoolean(enableDepth)
  buffer.pushBoolean(enableStencil)
  buffer.pushInt(frameBudgetBytes)
}

public fun RenderContextInfo?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(applicationName)
  buffer.pushStringUtf8(engineName)
  buffer.pushStringUtf8(swapchainName)
  buffer.pushInt(x)
  buffer.pushInt(y)
  buffer.pushInt(width)
  buffer.pushInt(height)
  buffer.pushInt(frameCount)
  buffer.pushBoolean(isDebug)
  surface.encodeGpu(buffer)
  clearColor.encodeGpu(buffer)
  buffer.pushBoolean(enableDepth)
  buffer.pushBoolean(enableStencil)
  buffer.pushInt(frameBudgetBytes)
}

public fun RenderContextInfo?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushPackedStringUtf8(applicationName)
  buffer.pushPackedStringUtf8(engineName)
  buffer.pushPackedStringUtf8(swapchainName)
  buffer.pushInt(x)
  buffer.pushInt(y)
  buffer.pushInt(width)
  buffer.pushInt(height)
  buffer.pushInt(frameCount)
  buffer.pushBoolean(isDebug)
  surface.encodePacked(buffer)
  clearColor.encodePacked(buffer)
  buffer.pushBoolean(enableDepth)
  buffer.pushBoolean(enableStencil)
  buffer.pushInt(frameBudgetBytes)
}

public fun NativeBuffer.decodeRenderContextInfo(): RenderContextInfo = RenderContextInfo(
  nextStringUtf8(),
  nextStringUtf8(),
  nextStringUtf8(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextBoolean(),
  decodeSurfaceHandle(),
  decodeFloat4(),
  nextBoolean(),
  nextBoolean(),
  nextInt(),
)

public fun NativeBuffer.decodeGpuRenderContextInfo(): RenderContextInfo = RenderContextInfo(
  nextStringUtf8(),
  nextStringUtf8(),
  nextStringUtf8(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextBoolean(),
  decodeGpuSurfaceHandle(),
  decodeGpuFloat4(),
  nextBoolean(),
  nextBoolean(),
  nextInt(),
)

public fun ByteArray.decodeRenderContextInfo(): RenderContextInfo = NativeBuffer(this).decodeRenderContextInfo()
