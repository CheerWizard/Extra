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
import com.cws.extra.test.decodeCompareOp
import com.cws.extra.test.decodeGpuCompareOp
import com.cws.extra.test.decodeGpuStencilOp
import com.cws.extra.test.decodeStencilOp
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun StencilState?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Boolean.SIZE_BYTES + compareOp.sizeBytes(memoryLayout) + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + stencilFailOp.sizeBytes(memoryLayout) + depthFailOp.sizeBytes(memoryLayout) + passOp.sizeBytes(memoryLayout)

public fun StencilState?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Boolean.SIZE_BYTES + compareOp.sizeBytesPacked(memoryLayout) + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + stencilFailOp.sizeBytesPacked(memoryLayout) + depthFailOp.sizeBytesPacked(memoryLayout) + passOp.sizeBytesPacked(memoryLayout)

public fun StencilState?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun StencilState?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun StencilState?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun StencilState?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushBoolean(enabled)
  compareOp.encode(buffer)
  buffer.pushInt(reference)
  buffer.pushInt(compareMask)
  buffer.pushInt(writeMask)
  stencilFailOp.encode(buffer)
  depthFailOp.encode(buffer)
  passOp.encode(buffer)
}

public fun StencilState?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushBoolean(enabled)
  compareOp.encodeGpu(buffer)
  buffer.pushInt(reference)
  buffer.pushInt(compareMask)
  buffer.pushInt(writeMask)
  stencilFailOp.encodeGpu(buffer)
  depthFailOp.encodeGpu(buffer)
  passOp.encodeGpu(buffer)
}

public fun StencilState?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushBoolean(enabled)
  compareOp.encodePacked(buffer)
  buffer.pushInt(reference)
  buffer.pushInt(compareMask)
  buffer.pushInt(writeMask)
  stencilFailOp.encodePacked(buffer)
  depthFailOp.encodePacked(buffer)
  passOp.encodePacked(buffer)
}

public fun NativeBuffer.decodeStencilState(): StencilState = StencilState(
  nextBoolean(),
  decodeCompareOp(),
  nextInt(),
  nextInt(),
  nextInt(),
  decodeStencilOp(),
  decodeStencilOp(),
  decodeStencilOp(),
)

public fun NativeBuffer.decodeGpuStencilState(): StencilState = StencilState(
  nextBoolean(),
  decodeGpuCompareOp(),
  nextInt(),
  nextInt(),
  nextInt(),
  decodeGpuStencilOp(),
  decodeGpuStencilOp(),
  decodeGpuStencilOp(),
)

public fun ByteArray.decodeStencilState(): StencilState = NativeBuffer(this).decodeStencilState()
