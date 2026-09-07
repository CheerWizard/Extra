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
import com.cws.extra.test.decodeBindingType
import com.cws.extra.test.decodeGpuBindingType
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun Binding?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else type.sizeBytes(memoryLayout) + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES

public fun Binding?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else type.sizeBytesPacked(memoryLayout) + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES + Int.SIZE_BYTES

public fun Binding?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun Binding?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun Binding?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun Binding?.encode(buffer: NativeBuffer) {
  if (this == null) return
  type.encode(buffer)
  buffer.pushInt(shaderStages)
  buffer.pushInt(set)
  buffer.pushInt(binding)
  buffer.pushInt(count)
}

public fun Binding?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  type.encodeGpu(buffer)
  buffer.pushInt(shaderStages)
  buffer.pushInt(set)
  buffer.pushInt(binding)
  buffer.pushInt(count)
}

public fun Binding?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  type.encodePacked(buffer)
  buffer.pushInt(shaderStages)
  buffer.pushInt(set)
  buffer.pushInt(binding)
  buffer.pushInt(count)
}

public fun NativeBuffer.decodeBinding(): Binding = Binding(
  decodeBindingType(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextInt(),
)

public fun NativeBuffer.decodeGpuBinding(): Binding = Binding(
  decodeGpuBindingType(),
  nextInt(),
  nextInt(),
  nextInt(),
  nextInt(),
)

public fun ByteArray.decodeBinding(): Binding = NativeBuffer(this).decodeBinding()
