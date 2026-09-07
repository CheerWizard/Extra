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

public fun PrimitiveTopology?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun PrimitiveTopology?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun PrimitiveTopology?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun PrimitiveTopology?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun PrimitiveTopology?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodePrimitiveTopology(): PrimitiveTopology = NativeBuffer(this).decodePrimitiveTopology()

public fun NativeBuffer.decodePrimitiveTopology(): PrimitiveTopology {
  val rawValue = nextInt()
  return PrimitiveTopology.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of PrimitiveTopology")
}

public fun NativeBuffer.decodeGpuPrimitiveTopology(): PrimitiveTopology {
  val rawValue = nextInt()
  return PrimitiveTopology.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of PrimitiveTopology")
}

public val PrimitiveTopology.`value`: Int
  get() = rawValue
