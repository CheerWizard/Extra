/*
 * Copyright 2026 CheerWizard
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import com.cws.extra.test.decodeBindingLayoutHandle
import com.cws.extra.test.decodeBufferHandle
import com.cws.extra.test.decodeCullMode
import com.cws.extra.test.decodeFrontFace
import com.cws.extra.test.decodeGpuBindingLayoutHandle
import com.cws.extra.test.decodeGpuBufferHandle
import com.cws.extra.test.decodeGpuCullMode
import com.cws.extra.test.decodeGpuFrontFace
import com.cws.extra.test.decodeGpuPolygonMode
import com.cws.extra.test.decodeGpuPrimitiveTopology
import com.cws.extra.test.decodeGpuRenderTargetHandle
import com.cws.extra.test.decodeGpuShaderHandle
import com.cws.extra.test.decodeGpuStencilState
import com.cws.extra.test.decodePolygonMode
import com.cws.extra.test.decodePrimitiveTopology
import com.cws.extra.test.decodeRenderTargetHandle
import com.cws.extra.test.decodeShaderHandle
import com.cws.extra.test.decodeStencilState
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun RenderPipelineInfo?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES + name.orEmpty().sizeBytesUtf8(memoryLayout) + Boolean.SIZE_BYTES + primitiveTopology.sizeBytes(memoryLayout) + vertexBuffer.sizeBytes(memoryLayout) + indexBuffer.sizeBytes(memoryLayout) + vertexShader.sizeBytes(memoryLayout) + fragmentShader.sizeBytes(memoryLayout) + geometryShader.sizeBytes(memoryLayout) + Int.SIZE_BYTES + bindingLayouts.sumOf { it.sizeBytes(memoryLayout) } + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + polygonMode.sizeBytes(memoryLayout) + Float.SIZE_BYTES + cullMode.sizeBytes(memoryLayout) + frontFace.sizeBytes(memoryLayout) + Int.SIZE_BYTES + renderTarget.sizeBytes(memoryLayout) + stencilState.sizeBytes(memoryLayout)

public fun RenderPipelineInfo?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else name.orEmpty().sizeBytesUtf8(memoryLayout) + Boolean.SIZE_BYTES + primitiveTopology.sizeBytesPacked(memoryLayout) + vertexBuffer.sizeBytesPacked(memoryLayout) + indexBuffer.sizeBytesPacked(memoryLayout) + vertexShader.sizeBytesPacked(memoryLayout) + fragmentShader.sizeBytesPacked(memoryLayout) + geometryShader.sizeBytesPacked(memoryLayout) + bindingLayouts.sumOf { it.sizeBytesPacked(memoryLayout) } + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + polygonMode.sizeBytesPacked(memoryLayout) + Float.SIZE_BYTES + cullMode.sizeBytesPacked(memoryLayout) + frontFace.sizeBytesPacked(memoryLayout) + Int.SIZE_BYTES + renderTarget.sizeBytesPacked(memoryLayout) + stencilState.sizeBytesPacked(memoryLayout)

public fun RenderPipelineInfo?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun RenderPipelineInfo?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun RenderPipelineInfo?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun RenderPipelineInfo?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  buffer.pushBoolean(instanced)
  primitiveTopology.encode(buffer)
  vertexBuffer.encode(buffer)
  indexBuffer.encode(buffer)
  vertexShader.encode(buffer)
  fragmentShader.encode(buffer)
  geometryShader.encode(buffer)
  buffer.pushCollection(bindingLayouts) { it.encode(buffer) }
  buffer.pushFloat(viewportX)
  buffer.pushFloat(viewportY)
  buffer.pushFloat(viewportWidth)
  buffer.pushFloat(viewportHeight)
  buffer.pushFloat(viewportMinDepth)
  buffer.pushFloat(viewportMaxDepth)
  buffer.pushInt(scissorX)
  buffer.pushInt(scissorY)
  buffer.pushInt(scissorWidth)
  buffer.pushInt(scissorHeight)
  polygonMode.encode(buffer)
  buffer.pushFloat(lineWidth)
  cullMode.encode(buffer)
  frontFace.encode(buffer)
  buffer.pushInt(sampleCount)
  renderTarget.encode(buffer)
  stencilState.encode(buffer)
}

public fun RenderPipelineInfo?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  buffer.pushBoolean(instanced)
  primitiveTopology.encodeGpu(buffer)
  vertexBuffer.encodeGpu(buffer)
  indexBuffer.encodeGpu(buffer)
  vertexShader.encodeGpu(buffer)
  fragmentShader.encodeGpu(buffer)
  geometryShader.encodeGpu(buffer)
  buffer.pushCollection(bindingLayouts) { it.encodeGpu(buffer) }
  buffer.pushFloat(viewportX)
  buffer.pushFloat(viewportY)
  buffer.pushFloat(viewportWidth)
  buffer.pushFloat(viewportHeight)
  buffer.pushFloat(viewportMinDepth)
  buffer.pushFloat(viewportMaxDepth)
  buffer.pushInt(scissorX)
  buffer.pushInt(scissorY)
  buffer.pushInt(scissorWidth)
  buffer.pushInt(scissorHeight)
  polygonMode.encodeGpu(buffer)
  buffer.pushFloat(lineWidth)
  cullMode.encodeGpu(buffer)
  frontFace.encodeGpu(buffer)
  buffer.pushInt(sampleCount)
  renderTarget.encodeGpu(buffer)
  stencilState.encodeGpu(buffer)
}

public fun RenderPipelineInfo?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushPackedStringUtf8(name)
  buffer.pushBoolean(instanced)
  primitiveTopology.encodePacked(buffer)
  vertexBuffer.encodePacked(buffer)
  indexBuffer.encodePacked(buffer)
  vertexShader.encodePacked(buffer)
  fragmentShader.encodePacked(buffer)
  geometryShader.encodePacked(buffer)
  buffer.pushPackedCollection(bindingLayouts) { it.encodeGpu(buffer) }
  buffer.pushFloat(viewportX)
  buffer.pushFloat(viewportY)
  buffer.pushFloat(viewportWidth)
  buffer.pushFloat(viewportHeight)
  buffer.pushFloat(viewportMinDepth)
  buffer.pushFloat(viewportMaxDepth)
  buffer.pushInt(scissorX)
  buffer.pushInt(scissorY)
  buffer.pushInt(scissorWidth)
  buffer.pushInt(scissorHeight)
  polygonMode.encodePacked(buffer)
  buffer.pushFloat(lineWidth)
  cullMode.encodePacked(buffer)
  frontFace.encodePacked(buffer)
  buffer.pushInt(sampleCount)
  renderTarget.encodePacked(buffer)
  stencilState.encodePacked(buffer)
}

public fun NativeBuffer.decodeRenderPipelineInfo(): RenderPipelineInfo = RenderPipelineInfo(
  nextStringUtf8(),
  nextBoolean(),
  decodePrimitiveTopology(),
  decodeBufferHandle(),
  decodeBufferHandle(),
  decodeShaderHandle(),
  decodeShaderHandle(),
  decodeShaderHandle(),
  nextList { this.decodeBindingLayoutHandle() },
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextInt(),
  decodePolygonMode(),
  nextFloat(),
  decodeCullMode(),
  decodeFrontFace(),
  nextInt(),
  decodeRenderTargetHandle(),
  decodeStencilState(),
)

public fun NativeBuffer.decodeGpuRenderPipelineInfo(): RenderPipelineInfo = RenderPipelineInfo(
  nextStringUtf8(),
  nextBoolean(),
  decodeGpuPrimitiveTopology(),
  decodeGpuBufferHandle(),
  decodeGpuBufferHandle(),
  decodeGpuShaderHandle(),
  decodeGpuShaderHandle(),
  decodeGpuShaderHandle(),
  nextList { this.decodeGpuBindingLayoutHandle() },
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextInt(),
  decodeGpuPolygonMode(),
  nextFloat(),
  decodeGpuCullMode(),
  decodeGpuFrontFace(),
  nextInt(),
  decodeGpuRenderTargetHandle(),
  decodeGpuStencilState(),
)

public fun ByteArray.decodeRenderPipelineInfo(): RenderPipelineInfo = NativeBuffer(this).decodeRenderPipelineInfo()
