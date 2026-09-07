package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import com.cws.extra.test.decodeBindingLayoutHandle
import com.cws.extra.test.decodeGpuBindingLayoutHandle
import com.cws.extra.test.decodeGpuShaderHandle
import com.cws.extra.test.decodeShaderHandle
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun ComputePipelineInfo?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES + name.orEmpty().sizeBytesUtf8(memoryLayout) + computeShader.sizeBytes(memoryLayout) + Int.SIZE_BYTES + bindingLayouts.sumOf { it.sizeBytes(memoryLayout) }

public fun ComputePipelineInfo?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else name.orEmpty().sizeBytesUtf8(memoryLayout) + computeShader.sizeBytesPacked(memoryLayout) + bindingLayouts.sumOf { it.sizeBytesPacked(memoryLayout) }

public fun ComputePipelineInfo?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun ComputePipelineInfo?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun ComputePipelineInfo?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun ComputePipelineInfo?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  computeShader.encode(buffer)
  buffer.pushCollection(bindingLayouts) { it.encode(buffer) }
}

public fun ComputePipelineInfo?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  computeShader.encodeGpu(buffer)
  buffer.pushCollection(bindingLayouts) { it.encodeGpu(buffer) }
}

public fun ComputePipelineInfo?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushPackedStringUtf8(name)
  computeShader.encodePacked(buffer)
  buffer.pushPackedCollection(bindingLayouts) { it.encodeGpu(buffer) }
}

public fun NativeBuffer.decodeComputePipelineInfo(): ComputePipelineInfo = ComputePipelineInfo(
  nextStringUtf8(),
  decodeShaderHandle(),
  nextList { this.decodeBindingLayoutHandle() },
)

public fun NativeBuffer.decodeGpuComputePipelineInfo(): ComputePipelineInfo = ComputePipelineInfo(
  nextStringUtf8(),
  decodeGpuShaderHandle(),
  nextList { this.decodeGpuBindingLayoutHandle() },
)

public fun ByteArray.decodeComputePipelineInfo(): ComputePipelineInfo = NativeBuffer(this).decodeComputePipelineInfo()
