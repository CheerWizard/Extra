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
package com.cws.extra.ecs

import com.cws.extra.memory.*

import com.cws.extra.lists.decodeGpuIntList
import com.cws.extra.lists.decodeIntList
import com.cws.extra.lists.encode
import com.cws.extra.lists.encodeGpu
import com.cws.extra.lists.encodePacked
import com.cws.extra.lists.sizeBytes
import com.cws.extra.lists.sizeBytesPacked
import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun ComponentPool?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else entityToComponent.sizeBytes(memoryLayout) + componentToEntity.sizeBytes(memoryLayout)

public fun ComponentPool?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else entityToComponent.sizeBytesPacked(memoryLayout) + componentToEntity.sizeBytesPacked(memoryLayout)

public fun ComponentPool?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun ComponentPool?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun ComponentPool?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun ComponentPool?.encode(buffer: NativeBuffer) {
  if (this == null) return
  entityToComponent.encode(buffer)
  componentToEntity.encode(buffer)
}

public fun ComponentPool?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  entityToComponent.encodeGpu(buffer)
  componentToEntity.encodeGpu(buffer)
}

public fun ComponentPool?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  entityToComponent.encodePacked(buffer)
  componentToEntity.encodePacked(buffer)
}

public fun NativeBuffer.decodeComponentPool(): ComponentPool = ComponentPool(
  decodeIntList(),
  decodeIntList(),
)

public fun NativeBuffer.decodeGpuComponentPool(): ComponentPool = ComponentPool(
  decodeGpuIntList(),
  decodeGpuIntList(),
)

public fun ByteArray.decodeComponentPool(): ComponentPool = NativeBuffer(this).decodeComponentPool()
