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
import kotlin.Float
import kotlin.Int

public fun TestEnumRaw?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Float.SIZE_BYTES

public fun TestEnumRaw?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Float.SIZE_BYTES

public fun TestEnumRaw?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(rawValue)
}

public fun TestEnumRaw?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(rawValue)
}

public fun TestEnumRaw?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(rawValue)
}

public fun ByteArray.decodeTestEnumRaw(): TestEnumRaw = NativeBuffer(this).decodeTestEnumRaw()

public fun NativeBuffer.decodeTestEnumRaw(): TestEnumRaw {
  val rawValue = nextFloat()
  return TestEnumRaw.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of TestEnumRaw")
}

public fun NativeBuffer.decodeGpuTestEnumRaw(): TestEnumRaw {
  val rawValue = nextFloat()
  return TestEnumRaw.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of TestEnumRaw")
}

public val TestEnumRaw.`value`: Float
  get() = rawValue
