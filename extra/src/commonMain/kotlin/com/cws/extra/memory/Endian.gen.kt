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

public fun Endian?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun Endian?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun Endian?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun Endian?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun Endian?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(ordinal)
}

public fun ByteArray.decodeEndian(): Endian = NativeBuffer(this).decodeEndian()

public fun NativeBuffer.decodeEndian(): Endian {
  val ordinal = nextInt()
  return Endian.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of Endian")
}

public fun NativeBuffer.decodeGpuEndian(): Endian {
  val ordinal = nextInt()
  return Endian.entries.getOrNull(ordinal) ?: error("Can't find ordinal inside of Endian")
}

public val Endian.`value`: Int
  get() = ordinal
