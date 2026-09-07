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
package com.cws.extra.memory

import com.cws.extra.memory.*

import kotlin.ByteArray
import kotlin.Int

public fun MemoryBoundary?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun MemoryBoundary?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun MemoryBoundary?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun MemoryBoundary?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun MemoryBoundary?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun ByteArray.decodeMemoryBoundary(): MemoryBoundary = NativeBuffer(this).decodeMemoryBoundary()

public fun NativeBuffer.decodeMemoryBoundary(): MemoryBoundary {
  val ordinal = nextInt()
  return MemoryBoundary.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of MemoryBoundary")
}

public fun NativeBuffer.decodeGpuMemoryBoundary(): MemoryBoundary {
  val ordinal = nextInt()
  return MemoryBoundary.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of MemoryBoundary")
}

public val MemoryBoundary.`value`: Int
  get() = ordinal
