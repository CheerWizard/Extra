package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.math.matrices.sizeBytes
import com.cws.extra.math.matrices.sizeBytesPacked
import com.cws.extra.math.vectors.decodeFloat2
import com.cws.extra.math.vectors.decodeFloat3
import com.cws.extra.math.vectors.decodeFloat4
import com.cws.extra.math.vectors.decodeGpuFloat2
import com.cws.extra.math.vectors.decodeGpuFloat3
import com.cws.extra.math.vectors.decodeGpuFloat4
import com.cws.extra.math.vectors.decodeGpuInt2
import com.cws.extra.math.vectors.decodeGpuInt3
import com.cws.extra.math.vectors.decodeGpuInt4
import com.cws.extra.math.vectors.decodeGpuQuaternion
import com.cws.extra.math.vectors.decodeGpuUInt2
import com.cws.extra.math.vectors.decodeGpuUInt3
import com.cws.extra.math.vectors.decodeGpuUInt4
import com.cws.extra.math.vectors.decodeInt2
import com.cws.extra.math.vectors.decodeInt3
import com.cws.extra.math.vectors.decodeInt4
import com.cws.extra.math.vectors.decodeQuaternion
import com.cws.extra.math.vectors.decodeUInt2
import com.cws.extra.math.vectors.decodeUInt3
import com.cws.extra.math.vectors.decodeUInt4
import com.cws.extra.math.vectors.encode
import com.cws.extra.math.vectors.encodeGpu
import com.cws.extra.math.vectors.encodePacked
import com.cws.extra.math.vectors.sizeBytes
import com.cws.extra.math.vectors.sizeBytesPacked
import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun TestData.NestedData?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Long.SIZE_BYTES + float2.sizeBytes(memoryLayout) + float3.sizeBytes(memoryLayout) + float4.sizeBytes(memoryLayout) + int2.sizeBytes(memoryLayout) + int3.sizeBytes(memoryLayout) + int4.sizeBytes(memoryLayout) + uint2.sizeBytes(memoryLayout) + uInt3.sizeBytes(memoryLayout) + uInt4.sizeBytes(memoryLayout) + mat2.sizeBytes(memoryLayout) + mat3.sizeBytes(memoryLayout) + mat4.sizeBytes(memoryLayout) + quaternion.sizeBytes(memoryLayout) + Int.SIZE_BYTES + data.entries.sumOf { Int.SIZE_BYTES + it.key.orEmpty().sizeBytesUtf8(memoryLayout) + Int.SIZE_BYTES + it.value.orEmpty().sizeBytesUtf8(memoryLayout) } + Int.SIZE_BYTES + subscribers.sumOf { Int.SIZE_BYTES + it.orEmpty().sizeBytesUtf8(memoryLayout) }

public fun TestData.NestedData?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Long.SIZE_BYTES + float2.sizeBytesPacked(memoryLayout) + float3.sizeBytesPacked(memoryLayout) + float4.sizeBytesPacked(memoryLayout) + int2.sizeBytesPacked(memoryLayout) + int3.sizeBytesPacked(memoryLayout) + int4.sizeBytesPacked(memoryLayout) + uint2.sizeBytesPacked(memoryLayout) + uInt3.sizeBytesPacked(memoryLayout) + uInt4.sizeBytesPacked(memoryLayout) + mat2.sizeBytesPacked(memoryLayout) + mat3.sizeBytesPacked(memoryLayout) + mat4.sizeBytesPacked(memoryLayout) + quaternion.sizeBytesPacked(memoryLayout) + data.entries.sumOf { Int.SIZE_BYTES + it.key.orEmpty().sizeBytesUtf8(memoryLayout) + Int.SIZE_BYTES + it.value.orEmpty().sizeBytesUtf8(memoryLayout) } + subscribers.sumOf { Int.SIZE_BYTES + it.orEmpty().sizeBytesUtf8(memoryLayout) }

public fun TestData.NestedData?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun TestData.NestedData?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun TestData.NestedData?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun TestData.NestedData?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushLong(id)
  float2.encode(buffer)
  float3.encode(buffer)
  float4.encode(buffer)
  int2.encode(buffer)
  int3.encode(buffer)
  int4.encode(buffer)
  uint2.encode(buffer)
  uInt3.encode(buffer)
  uInt4.encode(buffer)
  buffer.pushMat2RowMajor(mat2)
  buffer.pushMat3RowMajor(mat3)
  buffer.pushMat4RowMajor(mat4)
  quaternion.encode(buffer)
  buffer.pushMap(data, { buffer.pushStringUtf8(it) }, { buffer.pushStringUtf8(it) })
  buffer.pushCollection(subscribers) { buffer.pushStringUtf8(it) }
}

public fun TestData.NestedData?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushLong(id)
  float2.encodeGpu(buffer)
  float3.encodeGpu(buffer)
  float4.encodeGpu(buffer)
  int2.encodeGpu(buffer)
  int3.encodeGpu(buffer)
  int4.encodeGpu(buffer)
  uint2.encodeGpu(buffer)
  uInt3.encodeGpu(buffer)
  uInt4.encodeGpu(buffer)
  buffer.pushMat2ColumnMajor(mat2)
  buffer.pushMat3ColumnMajor(mat3)
  buffer.pushMat4ColumnMajor(mat4)
  quaternion.encodeGpu(buffer)
  buffer.pushMap(data, { buffer.pushStringUtf8(it) }, { buffer.pushStringUtf8(it) })
  buffer.pushCollection(subscribers) { buffer.pushStringUtf8(it) }
}

public fun TestData.NestedData?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushLong(id)
  float2.encodePacked(buffer)
  float3.encodePacked(buffer)
  float4.encodePacked(buffer)
  int2.encodePacked(buffer)
  int3.encodePacked(buffer)
  int4.encodePacked(buffer)
  uint2.encodePacked(buffer)
  uInt3.encodePacked(buffer)
  uInt4.encodePacked(buffer)
  buffer.pushMat2ColumnMajor(mat2)
  buffer.pushMat3ColumnMajor(mat3)
  buffer.pushMat4ColumnMajor(mat4)
  quaternion.encodePacked(buffer)
  buffer.pushPackedMap(data, { buffer.pushStringUtf8(it) }, { buffer.pushStringUtf8(it) })
  buffer.pushPackedCollection(subscribers) { buffer.pushStringUtf8(it) }
}

public fun NativeBuffer.decodeNestedData(): TestData.NestedData = TestData.NestedData(
  nextLong(),
  decodeFloat2(),
  decodeFloat3(),
  decodeFloat4(),
  decodeInt2(),
  decodeInt3(),
  decodeInt4(),
  decodeUInt2(),
  decodeUInt3(),
  decodeUInt4(),
  nextMat2RowMajor(),
  nextMat3RowMajor(),
  nextMat4RowMajor(),
  decodeQuaternion(),
  nextMap({ this.nextStringUtf8() }, { this.nextStringUtf8() }),
  nextSet { this.nextStringUtf8() },
)

public fun NativeBuffer.decodeGpuNestedData(): TestData.NestedData = TestData.NestedData(
  nextLong(),
  decodeGpuFloat2(),
  decodeGpuFloat3(),
  decodeGpuFloat4(),
  decodeGpuInt2(),
  decodeGpuInt3(),
  decodeGpuInt4(),
  decodeGpuUInt2(),
  decodeGpuUInt3(),
  decodeGpuUInt4(),
  nextMat2ColumnMajor(),
  nextMat3ColumnMajor(),
  nextMat4ColumnMajor(),
  decodeGpuQuaternion(),
  nextMap({ this.nextStringUtf8() }, { this.nextStringUtf8() }),
  nextSet { this.nextStringUtf8() },
)

public fun ByteArray.decodeNestedData(): TestData.NestedData = NativeBuffer(this).decodeNestedData()
