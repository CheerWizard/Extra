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
import kotlin.ByteArray
import kotlin.Int

public fun Velocity?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES

public fun Velocity?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES

public fun Velocity?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun Velocity?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun Velocity?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun Velocity?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(x)
  buffer.pushFloat(y)
  buffer.pushFloat(z)
}

public fun Velocity?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(x)
  buffer.pushFloat(y)
  buffer.pushFloat(z)
}

public fun Velocity?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(x)
  buffer.pushFloat(y)
  buffer.pushFloat(z)
}

public fun NativeBuffer.decodeVelocity(): Velocity = Velocity(
  nextFloat(),
  nextFloat(),
  nextFloat(),
)

public fun NativeBuffer.decodeGpuVelocity(): Velocity = Velocity(
  nextFloat(),
  nextFloat(),
  nextFloat(),
)

public fun ByteArray.decodeVelocity(): Velocity = NativeBuffer(this).decodeVelocity()
