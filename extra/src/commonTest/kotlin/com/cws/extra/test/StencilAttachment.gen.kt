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
import com.cws.extra.test.decodeGpuTextureHandle
import com.cws.extra.test.decodeTextureHandle
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun StencilAttachment?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else texture.sizeBytes(memoryLayout) + Boolean.SIZE_BYTES + Int.SIZE_BYTES

public fun StencilAttachment?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else texture.sizeBytesPacked(memoryLayout) + Boolean.SIZE_BYTES + Int.SIZE_BYTES

public fun StencilAttachment?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun StencilAttachment?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun StencilAttachment?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun StencilAttachment?.encode(buffer: NativeBuffer) {
  if (this == null) return
  texture.encode(buffer)
  buffer.pushBoolean(enabled)
  buffer.pushInt(stencilClearValue)
}

public fun StencilAttachment?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  texture.encodeGpu(buffer)
  buffer.pushBoolean(enabled)
  buffer.pushInt(stencilClearValue)
}

public fun StencilAttachment?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  texture.encodePacked(buffer)
  buffer.pushBoolean(enabled)
  buffer.pushInt(stencilClearValue)
}

public fun NativeBuffer.decodeStencilAttachment(): StencilAttachment = StencilAttachment(
  decodeTextureHandle(),
  nextBoolean(),
  nextInt(),
)

public fun NativeBuffer.decodeGpuStencilAttachment(): StencilAttachment = StencilAttachment(
  decodeGpuTextureHandle(),
  nextBoolean(),
  nextInt(),
)

public fun ByteArray.decodeStencilAttachment(): StencilAttachment = NativeBuffer(this).decodeStencilAttachment()
