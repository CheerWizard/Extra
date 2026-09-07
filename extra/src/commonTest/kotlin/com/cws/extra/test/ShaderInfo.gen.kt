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
import com.cws.extra.test.decodeGpuShaderStage
import com.cws.extra.test.decodeGpuSpirvTarget
import com.cws.extra.test.decodeShaderStage
import com.cws.extra.test.decodeSpirvTarget
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun ShaderInfo?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES + name.orEmpty().sizeBytesUtf8(memoryLayout) + Int.SIZE_BYTES + entryPoint.orEmpty().sizeBytesUtf8(memoryLayout) + stage.sizeBytes(memoryLayout) + spirvTarget.sizeBytes(memoryLayout) + Int.SIZE_BYTES + spirvCode.sizeBytes(memoryLayout) + Int.SIZE_BYTES + textCode.orEmpty().sizeBytesUtf8(memoryLayout)

public fun ShaderInfo?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else name.orEmpty().sizeBytesUtf8(memoryLayout) + entryPoint.orEmpty().sizeBytesUtf8(memoryLayout) + stage.sizeBytesPacked(memoryLayout) + spirvTarget.sizeBytesPacked(memoryLayout) + spirvCode.sizeBytes(memoryLayout) + textCode.orEmpty().sizeBytesUtf8(memoryLayout)

public fun ShaderInfo?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun ShaderInfo?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun ShaderInfo?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun ShaderInfo?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  buffer.pushStringUtf8(entryPoint)
  stage.encode(buffer)
  spirvTarget.encode(buffer)
  buffer.pushByteArray(spirvCode)
  buffer.pushStringUtf8(textCode)
}

public fun ShaderInfo?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  buffer.pushStringUtf8(entryPoint)
  stage.encodeGpu(buffer)
  spirvTarget.encodeGpu(buffer)
  buffer.pushByteArray(spirvCode)
  buffer.pushStringUtf8(textCode)
}

public fun ShaderInfo?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushPackedStringUtf8(name)
  buffer.pushPackedStringUtf8(entryPoint)
  stage.encodePacked(buffer)
  spirvTarget.encodePacked(buffer)
  buffer.pushPackedByteArray(spirvCode)
  buffer.pushPackedStringUtf8(textCode)
}

public fun NativeBuffer.decodeShaderInfo(): ShaderInfo = ShaderInfo(
  nextStringUtf8(),
  nextStringUtf8(),
  decodeShaderStage(),
  decodeSpirvTarget(),
  nextByteArray(),
  nextStringUtf8(),
)

public fun NativeBuffer.decodeGpuShaderInfo(): ShaderInfo = ShaderInfo(
  nextStringUtf8(),
  nextStringUtf8(),
  decodeGpuShaderStage(),
  decodeGpuSpirvTarget(),
  nextByteArray(),
  nextStringUtf8(),
)

public fun ByteArray.decodeShaderInfo(): ShaderInfo = NativeBuffer(this).decodeShaderInfo()
