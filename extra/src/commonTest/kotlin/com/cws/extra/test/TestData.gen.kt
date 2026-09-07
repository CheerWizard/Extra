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
import com.cws.extra.memory.sizeBytes
import com.cws.extra.memory.sizeBytesPacked
import com.cws.extra.test.decodeGpuNestedData
import com.cws.extra.test.decodeGpuTestEnumOrdinal
import com.cws.extra.test.decodeGpuTestEnumRaw
import com.cws.extra.test.decodeNestedData
import com.cws.extra.test.decodeTestEnumOrdinal
import com.cws.extra.test.decodeTestEnumRaw
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun TestData?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Long.SIZE_BYTES + Long.SIZE_BYTES + Int.SIZE_BYTES + name.orEmpty().sizeBytesUtf8(memoryLayout) + Int.SIZE_BYTES + Int.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Boolean.SIZE_BYTES + Short.SIZE_BYTES + ordinalEnum.sizeBytes(memoryLayout) + rawEnum.sizeBytes(memoryLayout) + 12 * Byte.SIZE_BYTES + Int.SIZE_BYTES + stringUtf8.orEmpty().sizeBytesUtf8(memoryLayout) + 18 * Char.SIZE_BYTES + Int.SIZE_BYTES + stringUtf16.orEmpty().sizeBytesUtf16(memoryLayout) + 24 * Byte.SIZE_BYTES + Int.SIZE_BYTES + bytes.sizeBytes(memoryLayout) + 48 * Short.SIZE_BYTES + Int.SIZE_BYTES + shorts.sizeBytes(memoryLayout) + 64 * Int.SIZE_BYTES + Int.SIZE_BYTES + ints.sizeBytes(memoryLayout) + 36 * Long.SIZE_BYTES + Int.SIZE_BYTES + longs.sizeBytes(memoryLayout) + 36 * Float.SIZE_BYTES + Int.SIZE_BYTES + floats.sizeBytes(memoryLayout) + 36 * Double.SIZE_BYTES + Int.SIZE_BYTES + doubles.sizeBytes(memoryLayout) + nestedDataBuffer.sizeBytes(memoryLayout) + Int.SIZE_BYTES + data.sumOf { it.sizeBytes(memoryLayout) }

public fun TestData?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Long.SIZE_BYTES + Long.SIZE_BYTES + name.orEmpty().sizeBytesUtf8(memoryLayout) + Int.SIZE_BYTES + Int.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES + Boolean.SIZE_BYTES + Short.SIZE_BYTES + ordinalEnum.sizeBytesPacked(memoryLayout) + rawEnum.sizeBytesPacked(memoryLayout) + fixedStringUtf8.orEmpty().sizeBytesUtf8(memoryLayout) + stringUtf8.orEmpty().sizeBytesUtf8(memoryLayout) + fixedStringUtf16.orEmpty().sizeBytesUtf16(memoryLayout) + stringUtf16.orEmpty().sizeBytesUtf16(memoryLayout) + fixedBytes.sizeBytes(memoryLayout) + bytes.sizeBytes(memoryLayout) + fixedShorts.sizeBytes(memoryLayout) + shorts.sizeBytes(memoryLayout) + fixedInts.sizeBytes(memoryLayout) + ints.sizeBytes(memoryLayout) + fixedLongs.sizeBytes(memoryLayout) + longs.sizeBytes(memoryLayout) + fixedFloats.sizeBytes(memoryLayout) + floats.sizeBytes(memoryLayout) + fixedDoubles.sizeBytes(memoryLayout) + doubles.sizeBytes(memoryLayout) + nestedDataBuffer.sizeBytesPacked(memoryLayout) + data.sumOf { it.sizeBytesPacked(memoryLayout) }

public fun TestData?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun TestData?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun TestData?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun TestData?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushLong(id)
  buffer.pushLong(timestamp)
  buffer.pushStringUtf8(name)
  buffer.pushInt(width)
  buffer.pushInt(height)
  buffer.pushFloat(x)
  buffer.pushFloat(y)
  buffer.pushBoolean(flag)
  buffer.pushShort(age)
  ordinalEnum.encode(buffer)
  rawEnum.encode(buffer)
  buffer.pushFixedStringUtf8(fixedStringUtf8, 12)
  buffer.pushStringUtf8(stringUtf8)
  buffer.pushFixedStringUtf16(fixedStringUtf16, 18)
  buffer.pushStringUtf16(stringUtf16)
  buffer.pushFixedByteArray(fixedBytes, 24)
  buffer.pushByteArray(bytes)
  buffer.pushFixedShortArray(fixedShorts, 48)
  buffer.pushShortArray(shorts)
  buffer.pushFixedIntArray(fixedInts, 64)
  buffer.pushIntArray(ints)
  buffer.pushFixedLongArray(fixedLongs, 36)
  buffer.pushLongArray(longs)
  buffer.pushFixedFloatArray(fixedFloats, 36)
  buffer.pushFloatArray(floats)
  buffer.pushFixedDoubleArray(fixedDoubles, 36)
  buffer.pushDoubleArray(doubles)
  buffer.pushNativeBuffer(nestedDataBuffer)
  buffer.pushCollection(data) { it.encode(buffer) }
}

public fun TestData?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushLong(id)
  buffer.pushLong(timestamp)
  buffer.pushStringUtf8(name)
  buffer.pushInt(width)
  buffer.pushInt(height)
  buffer.pushFloat(x)
  buffer.pushFloat(y)
  buffer.pushBoolean(flag)
  buffer.pushShort(age)
  ordinalEnum.encodeGpu(buffer)
  rawEnum.encodeGpu(buffer)
  buffer.pushFixedStringUtf8(fixedStringUtf8, 12)
  buffer.pushStringUtf8(stringUtf8)
  buffer.pushFixedStringUtf16(fixedStringUtf16, 18)
  buffer.pushStringUtf16(stringUtf16)
  buffer.pushFixedByteArray(fixedBytes, 24)
  buffer.pushByteArray(bytes)
  buffer.pushFixedShortArray(fixedShorts, 48)
  buffer.pushShortArray(shorts)
  buffer.pushFixedIntArray(fixedInts, 64)
  buffer.pushIntArray(ints)
  buffer.pushFixedLongArray(fixedLongs, 36)
  buffer.pushLongArray(longs)
  buffer.pushFixedFloatArray(fixedFloats, 36)
  buffer.pushFloatArray(floats)
  buffer.pushFixedDoubleArray(fixedDoubles, 36)
  buffer.pushDoubleArray(doubles)
  buffer.pushNativeBuffer(nestedDataBuffer)
  buffer.pushCollection(data) { it.encodeGpu(buffer) }
}

public fun TestData?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushLong(id)
  buffer.pushLong(timestamp)
  buffer.pushPackedStringUtf8(name)
  buffer.pushInt(width)
  buffer.pushInt(height)
  buffer.pushFloat(x)
  buffer.pushFloat(y)
  buffer.pushBoolean(flag)
  buffer.pushShort(age)
  ordinalEnum.encodePacked(buffer)
  rawEnum.encodePacked(buffer)
  buffer.pushPackedStringUtf8(fixedStringUtf8)
  buffer.pushPackedStringUtf8(stringUtf8)
  buffer.pushPackedStringUtf16(fixedStringUtf16)
  buffer.pushPackedStringUtf16(stringUtf16)
  buffer.pushPackedByteArray(fixedBytes)
  buffer.pushPackedByteArray(bytes)
  buffer.pushPackedShortArray(fixedShorts)
  buffer.pushPackedShortArray(shorts)
  buffer.pushPackedIntArray(fixedInts)
  buffer.pushPackedIntArray(ints)
  buffer.pushPackedLongArray(fixedLongs)
  buffer.pushPackedLongArray(longs)
  buffer.pushPackedFloatArray(fixedFloats)
  buffer.pushPackedFloatArray(floats)
  buffer.pushPackedDoubleArray(fixedDoubles)
  buffer.pushPackedDoubleArray(doubles)
  buffer.pushNativeBuffer(nestedDataBuffer)
  buffer.pushPackedCollection(data) { it.encodeGpu(buffer) }
}

public fun NativeBuffer.decodeTestData(): TestData = TestData(
  nextLong(),
  nextLong(),
  nextStringUtf8(),
  nextInt(),
  nextInt(),
  nextFloat(),
  nextFloat(),
  nextBoolean(),
  nextShort(),
  decodeTestEnumOrdinal(),
  decodeTestEnumRaw(),
  nextStringUtf8(12),
  nextStringUtf8(),
  nextStringUtf16(18),
  nextStringUtf16(),
  nextByteArray(24),
  nextByteArray(),
  nextShortArray(48),
  nextShortArray(),
  nextIntArray(64),
  nextIntArray(),
  nextLongArray(36),
  nextLongArray(),
  nextFloatArray(36),
  nextFloatArray(),
  nextDoubleArray(36),
  nextDoubleArray(),
  nextNativeBuffer(),
  nextList { this.decodeNestedData() },
)

public fun NativeBuffer.decodeGpuTestData(): TestData = TestData(
  nextLong(),
  nextLong(),
  nextStringUtf8(),
  nextInt(),
  nextInt(),
  nextFloat(),
  nextFloat(),
  nextBoolean(),
  nextShort(),
  decodeGpuTestEnumOrdinal(),
  decodeGpuTestEnumRaw(),
  nextStringUtf8(12),
  nextStringUtf8(),
  nextStringUtf16(18),
  nextStringUtf16(),
  nextByteArray(24),
  nextByteArray(),
  nextShortArray(48),
  nextShortArray(),
  nextIntArray(64),
  nextIntArray(),
  nextLongArray(36),
  nextLongArray(),
  nextFloatArray(36),
  nextFloatArray(),
  nextDoubleArray(36),
  nextDoubleArray(),
  nextNativeBuffer(),
  nextList { this.decodeGpuNestedData() },
)

public fun ByteArray.decodeTestData(): TestData = NativeBuffer(this).decodeTestData()
