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
import com.cws.extra.test.decodeBlendState
import com.cws.extra.test.decodeGpuBlendState
import com.cws.extra.test.decodeGpuTextureHandle
import com.cws.extra.test.decodeTextureHandle
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun ColorAttachment?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else texture.sizeBytes(memoryLayout) + clearColor.sizeBytes(memoryLayout) + blendState.sizeBytes(memoryLayout)

public fun ColorAttachment?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else texture.sizeBytesPacked(memoryLayout) + clearColor.sizeBytesPacked(memoryLayout) + blendState.sizeBytesPacked(memoryLayout)

public fun ColorAttachment?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun ColorAttachment?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun ColorAttachment?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun ColorAttachment?.encode(buffer: NativeBuffer) {
  if (this == null) return
  texture.encode(buffer)
  clearColor.encode(buffer)
  blendState.encode(buffer)
}

public fun ColorAttachment?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  texture.encodeGpu(buffer)
  clearColor.encodeGpu(buffer)
  blendState.encodeGpu(buffer)
}

public fun ColorAttachment?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  texture.encodePacked(buffer)
  clearColor.encodePacked(buffer)
  blendState.encodePacked(buffer)
}

public fun NativeBuffer.decodeColorAttachment(): ColorAttachment = ColorAttachment(
  decodeTextureHandle(),
  decodeFloat4(),
  decodeBlendState(),
)

public fun NativeBuffer.decodeGpuColorAttachment(): ColorAttachment = ColorAttachment(
  decodeGpuTextureHandle(),
  decodeGpuFloat4(),
  decodeGpuBlendState(),
)

public fun ByteArray.decodeColorAttachment(): ColorAttachment = NativeBuffer(this).decodeColorAttachment()
