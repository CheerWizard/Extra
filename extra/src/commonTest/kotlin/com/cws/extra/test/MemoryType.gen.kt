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

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun MemoryType?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun MemoryType?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun MemoryType?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun MemoryType?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun MemoryType?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodeMemoryType(): MemoryType = NativeBuffer(this).decodeMemoryType()

public fun NativeBuffer.decodeMemoryType(): MemoryType {
  val rawValue = nextInt()
  return MemoryType.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of MemoryType")
}

public fun NativeBuffer.decodeGpuMemoryType(): MemoryType {
  val rawValue = nextInt()
  return MemoryType.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of MemoryType")
}

public val MemoryType.`value`: Int
  get() = rawValue
