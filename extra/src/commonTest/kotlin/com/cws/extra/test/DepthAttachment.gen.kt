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
import com.cws.extra.test.decodeGpuTextureHandle
import com.cws.extra.test.decodeTextureHandle
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun DepthAttachment?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else texture.sizeBytes(memoryLayout) + Boolean.SIZE_BYTES + Float.SIZE_BYTES + depthCompareOp.sizeBytes(memoryLayout) + Boolean.SIZE_BYTES + Boolean.SIZE_BYTES

public fun DepthAttachment?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else texture.sizeBytesPacked(memoryLayout) + Boolean.SIZE_BYTES + Float.SIZE_BYTES + depthCompareOp.sizeBytesPacked(memoryLayout) + Boolean.SIZE_BYTES + Boolean.SIZE_BYTES

public fun DepthAttachment?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun DepthAttachment?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun DepthAttachment?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun DepthAttachment?.encode(buffer: NativeBuffer) {
  if (this == null) return
  texture.encode(buffer)
  buffer.pushBoolean(enabled)
  buffer.pushFloat(depthClearValue)
  depthCompareOp.encode(buffer)
  buffer.pushBoolean(depthReadOnly)
  buffer.pushBoolean(depthWriteEnabled)
}

public fun DepthAttachment?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  texture.encodeGpu(buffer)
  buffer.pushBoolean(enabled)
  buffer.pushFloat(depthClearValue)
  depthCompareOp.encodeGpu(buffer)
  buffer.pushBoolean(depthReadOnly)
  buffer.pushBoolean(depthWriteEnabled)
}

public fun DepthAttachment?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  texture.encodePacked(buffer)
  buffer.pushBoolean(enabled)
  buffer.pushFloat(depthClearValue)
  depthCompareOp.encodePacked(buffer)
  buffer.pushBoolean(depthReadOnly)
  buffer.pushBoolean(depthWriteEnabled)
}

public fun NativeBuffer.decodeDepthAttachment(): DepthAttachment = DepthAttachment(
  decodeTextureHandle(),
  nextBoolean(),
  nextFloat(),
  decodeCompareOp(),
  nextBoolean(),
  nextBoolean(),
)

public fun NativeBuffer.decodeGpuDepthAttachment(): DepthAttachment = DepthAttachment(
  decodeGpuTextureHandle(),
  nextBoolean(),
  nextFloat(),
  decodeGpuCompareOp(),
  nextBoolean(),
  nextBoolean(),
)

public fun ByteArray.decodeDepthAttachment(): DepthAttachment = NativeBuffer(this).decodeDepthAttachment()
