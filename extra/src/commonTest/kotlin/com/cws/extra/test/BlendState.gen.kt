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
import com.cws.extra.test.decodeBlendFactor
import com.cws.extra.test.decodeBlendOp
import com.cws.extra.test.decodeGpuBlendFactor
import com.cws.extra.test.decodeGpuBlendOp
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun BlendState?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Boolean.SIZE_BYTES + srcFactorColor.sizeBytes(memoryLayout) + dstFactorColor.sizeBytes(memoryLayout) + blendOpColor.sizeBytes(memoryLayout) + srcFactorAlpha.sizeBytes(memoryLayout) + dstFactorAlpha.sizeBytes(memoryLayout) + blendOpAlpha.sizeBytes(memoryLayout)

public fun BlendState?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Boolean.SIZE_BYTES + srcFactorColor.sizeBytesPacked(memoryLayout) + dstFactorColor.sizeBytesPacked(memoryLayout) + blendOpColor.sizeBytesPacked(memoryLayout) + srcFactorAlpha.sizeBytesPacked(memoryLayout) + dstFactorAlpha.sizeBytesPacked(memoryLayout) + blendOpAlpha.sizeBytesPacked(memoryLayout)

public fun BlendState?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun BlendState?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun BlendState?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun BlendState?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushBoolean(enable)
  srcFactorColor.encode(buffer)
  dstFactorColor.encode(buffer)
  blendOpColor.encode(buffer)
  srcFactorAlpha.encode(buffer)
  dstFactorAlpha.encode(buffer)
  blendOpAlpha.encode(buffer)
}

public fun BlendState?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushBoolean(enable)
  srcFactorColor.encodeGpu(buffer)
  dstFactorColor.encodeGpu(buffer)
  blendOpColor.encodeGpu(buffer)
  srcFactorAlpha.encodeGpu(buffer)
  dstFactorAlpha.encodeGpu(buffer)
  blendOpAlpha.encodeGpu(buffer)
}

public fun BlendState?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushBoolean(enable)
  srcFactorColor.encodePacked(buffer)
  dstFactorColor.encodePacked(buffer)
  blendOpColor.encodePacked(buffer)
  srcFactorAlpha.encodePacked(buffer)
  dstFactorAlpha.encodePacked(buffer)
  blendOpAlpha.encodePacked(buffer)
}

public fun NativeBuffer.decodeBlendState(): BlendState = BlendState(
  nextBoolean(),
  decodeBlendFactor(),
  decodeBlendFactor(),
  decodeBlendOp(),
  decodeBlendFactor(),
  decodeBlendFactor(),
  decodeBlendOp(),
)

public fun NativeBuffer.decodeGpuBlendState(): BlendState = BlendState(
  nextBoolean(),
  decodeGpuBlendFactor(),
  decodeGpuBlendFactor(),
  decodeGpuBlendOp(),
  decodeGpuBlendFactor(),
  decodeGpuBlendFactor(),
  decodeGpuBlendOp(),
)

public fun ByteArray.decodeBlendState(): BlendState = NativeBuffer(this).decodeBlendState()
