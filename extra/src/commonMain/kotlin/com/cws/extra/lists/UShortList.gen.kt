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
package com.cws.extra.lists

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun UShortList?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES + Int.SIZE_BYTES + array.sizeBytes(memoryLayout)

public fun UShortList?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES + array.sizeBytes(memoryLayout)

public fun UShortList?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun UShortList?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun UShortList?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun UShortList?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  buffer.pushUShortArray(array)
}

public fun UShortList?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  buffer.pushUShortArray(array)
}

public fun UShortList?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  buffer.pushPackedUShortArray(array)
}

public fun NativeBuffer.decodeUShortList(): UShortList = UShortList(
  nextInt(),
  nextUShortArray(),
)

public fun NativeBuffer.decodeGpuUShortList(): UShortList = UShortList(
  nextInt(),
  nextUShortArray(),
)

public fun ByteArray.decodeUShortList(): UShortList = NativeBuffer(this).decodeUShortList()
