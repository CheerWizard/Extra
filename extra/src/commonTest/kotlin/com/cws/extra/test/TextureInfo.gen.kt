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
import com.cws.extra.test.decodeGpuMemoryType
import com.cws.extra.test.decodeGpuTextureFormat
import com.cws.extra.test.decodeGpuTextureType
import com.cws.extra.test.decodeMemoryType
import com.cws.extra.test.decodeTextureFormat
import com.cws.extra.test.decodeTextureType
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun TextureInfo?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES + name.orEmpty().sizeBytesUtf8(memoryLayout) + type.sizeBytes(memoryLayout) + memoryType.sizeBytes(memoryLayout) + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + format.sizeBytes(memoryLayout) + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Boolean.SIZE_BYTES

public fun TextureInfo?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else name.orEmpty().sizeBytesUtf8(memoryLayout) + type.sizeBytesPacked(memoryLayout) + memoryType.sizeBytesPacked(memoryLayout) + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + format.sizeBytesPacked(memoryLayout) + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Boolean.SIZE_BYTES

public fun TextureInfo?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun TextureInfo?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun TextureInfo?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun TextureInfo?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  type.encode(buffer)
  memoryType.encode(buffer)
  buffer.pushInt(usages)
  buffer.pushInt(width)
  buffer.pushInt(height)
  buffer.pushInt(depth)
  format.encode(buffer)
  buffer.pushInt(mips)
  buffer.pushInt(baseMip)
  buffer.pushInt(samples)
  buffer.pushBoolean(isStatic)
}

public fun TextureInfo?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  type.encodeGpu(buffer)
  memoryType.encodeGpu(buffer)
  buffer.pushInt(usages)
  buffer.pushInt(width)
  buffer.pushInt(height)
  buffer.pushInt(depth)
  format.encodeGpu(buffer)
  buffer.pushInt(mips)
  buffer.pushInt(baseMip)
  buffer.pushInt(samples)
  buffer.pushBoolean(isStatic)
}

public fun TextureInfo?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushPackedStringUtf8(name)
  type.encodePacked(buffer)
  memoryType.encodePacked(buffer)
  buffer.pushInt(usages)
  buffer.pushInt(width)
  buffer.pushInt(height)
  buffer.pushInt(depth)
  format.encodePacked(buffer)
  buffer.pushInt(mips)
  buffer.pushInt(baseMip)
  buffer.pushInt(samples)
  buffer.pushBoolean(isStatic)
}

public fun NativeBuffer.decodeTextureInfo(): TextureInfo = TextureInfo(
  nextStringUtf8(),
  decodeTextureType(),
  decodeMemoryType(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextInt(),
  decodeTextureFormat(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextBoolean(),
)

public fun NativeBuffer.decodeGpuTextureInfo(): TextureInfo = TextureInfo(
  nextStringUtf8(),
  decodeGpuTextureType(),
  decodeGpuMemoryType(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextInt(),
  decodeGpuTextureFormat(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextBoolean(),
)

public fun ByteArray.decodeTextureInfo(): TextureInfo = NativeBuffer(this).decodeTextureInfo()
