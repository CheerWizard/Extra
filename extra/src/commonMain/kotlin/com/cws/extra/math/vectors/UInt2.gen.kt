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
package com.cws.extra.math.vectors

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun UInt2?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else UInt.SIZE_BYTES + UInt.SIZE_BYTES

public fun UInt2?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else UInt.SIZE_BYTES + UInt.SIZE_BYTES

public fun UInt2?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun UInt2?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun UInt2?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun UInt2?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushUInt(x)
  buffer.pushUInt(y)
}

public fun UInt2?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushUInt(x)
  buffer.pushUInt(y)
}

public fun UInt2?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushUInt(x)
  buffer.pushUInt(y)
}

public fun NativeBuffer.decodeUInt2(): UInt2 = UInt2(
  nextUInt(),
  nextUInt(),
)

public fun NativeBuffer.decodeGpuUInt2(): UInt2 = UInt2(
  nextUInt(),
  nextUInt(),
)

public fun ByteArray.decodeUInt2(): UInt2 = NativeBuffer(this).decodeUInt2()
