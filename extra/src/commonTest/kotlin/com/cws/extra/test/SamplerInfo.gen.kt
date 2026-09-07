package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import com.cws.extra.test.decodeBorderColor
import com.cws.extra.test.decodeCompareOp
import com.cws.extra.test.decodeGpuBorderColor
import com.cws.extra.test.decodeGpuCompareOp
import com.cws.extra.test.decodeGpuSamplerFilter
import com.cws.extra.test.decodeGpuSamplerMipMapMode
import com.cws.extra.test.decodeGpuSamplerMode
import com.cws.extra.test.decodeSamplerFilter
import com.cws.extra.test.decodeSamplerMipMapMode
import com.cws.extra.test.decodeSamplerMode
import com.cws.extra.test.encode
import com.cws.extra.test.encodeGpu
import com.cws.extra.test.encodePacked
import com.cws.extra.test.sizeBytes
import com.cws.extra.test.sizeBytesPacked
import kotlin.ByteArray
import kotlin.Int

public fun SamplerInfo?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES + name.orEmpty().sizeBytesUtf8(memoryLayout) + magFilter.sizeBytes(memoryLayout) + minFilter.sizeBytes(memoryLayout) + addressModeU.sizeBytes(memoryLayout) + addressModeV.sizeBytes(memoryLayout) + addressModeW.sizeBytes(memoryLayout) + mipmapMode.sizeBytes(memoryLayout) + Boolean.SIZE_BYTES + Float.SIZE_BYTES + Boolean.SIZE_BYTES + Boolean.SIZE_BYTES + compareOp.sizeBytes(memoryLayout) + borderColor.sizeBytes(memoryLayout) + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES

public fun SamplerInfo?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else name.orEmpty().sizeBytesUtf8(memoryLayout) + magFilter.sizeBytesPacked(memoryLayout) + minFilter.sizeBytesPacked(memoryLayout) + addressModeU.sizeBytesPacked(memoryLayout) + addressModeV.sizeBytesPacked(memoryLayout) + addressModeW.sizeBytesPacked(memoryLayout) + mipmapMode.sizeBytesPacked(memoryLayout) + Boolean.SIZE_BYTES + Float.SIZE_BYTES + Boolean.SIZE_BYTES + Boolean.SIZE_BYTES + compareOp.sizeBytesPacked(memoryLayout) + borderColor.sizeBytesPacked(memoryLayout) + Float.SIZE_BYTES + Float.SIZE_BYTES + Float.SIZE_BYTES

public fun SamplerInfo?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun SamplerInfo?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun SamplerInfo?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun SamplerInfo?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  magFilter.encode(buffer)
  minFilter.encode(buffer)
  addressModeU.encode(buffer)
  addressModeV.encode(buffer)
  addressModeW.encode(buffer)
  mipmapMode.encode(buffer)
  buffer.pushBoolean(enableAnisotropy)
  buffer.pushFloat(maxAnisotropy)
  buffer.pushBoolean(unnormalizedCoordinates)
  buffer.pushBoolean(enableCompare)
  compareOp.encode(buffer)
  borderColor.encode(buffer)
  buffer.pushFloat(mipLodBias)
  buffer.pushFloat(minLod)
  buffer.pushFloat(maxLod)
}

public fun SamplerInfo?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushStringUtf8(name)
  magFilter.encodeGpu(buffer)
  minFilter.encodeGpu(buffer)
  addressModeU.encodeGpu(buffer)
  addressModeV.encodeGpu(buffer)
  addressModeW.encodeGpu(buffer)
  mipmapMode.encodeGpu(buffer)
  buffer.pushBoolean(enableAnisotropy)
  buffer.pushFloat(maxAnisotropy)
  buffer.pushBoolean(unnormalizedCoordinates)
  buffer.pushBoolean(enableCompare)
  compareOp.encodeGpu(buffer)
  borderColor.encodeGpu(buffer)
  buffer.pushFloat(mipLodBias)
  buffer.pushFloat(minLod)
  buffer.pushFloat(maxLod)
}

public fun SamplerInfo?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushPackedStringUtf8(name)
  magFilter.encodePacked(buffer)
  minFilter.encodePacked(buffer)
  addressModeU.encodePacked(buffer)
  addressModeV.encodePacked(buffer)
  addressModeW.encodePacked(buffer)
  mipmapMode.encodePacked(buffer)
  buffer.pushBoolean(enableAnisotropy)
  buffer.pushFloat(maxAnisotropy)
  buffer.pushBoolean(unnormalizedCoordinates)
  buffer.pushBoolean(enableCompare)
  compareOp.encodePacked(buffer)
  borderColor.encodePacked(buffer)
  buffer.pushFloat(mipLodBias)
  buffer.pushFloat(minLod)
  buffer.pushFloat(maxLod)
}

public fun NativeBuffer.decodeSamplerInfo(): SamplerInfo = SamplerInfo(
  nextStringUtf8(),
  decodeSamplerFilter(),
  decodeSamplerFilter(),
  decodeSamplerMode(),
  decodeSamplerMode(),
  decodeSamplerMode(),
  decodeSamplerMipMapMode(),
  nextBoolean(),
  nextFloat(),
  nextBoolean(),
  nextBoolean(),
  decodeCompareOp(),
  decodeBorderColor(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
)

public fun NativeBuffer.decodeGpuSamplerInfo(): SamplerInfo = SamplerInfo(
  nextStringUtf8(),
  decodeGpuSamplerFilter(),
  decodeGpuSamplerFilter(),
  decodeGpuSamplerMode(),
  decodeGpuSamplerMode(),
  decodeGpuSamplerMode(),
  decodeGpuSamplerMipMapMode(),
  nextBoolean(),
  nextFloat(),
  nextBoolean(),
  nextBoolean(),
  decodeGpuCompareOp(),
  decodeGpuBorderColor(),
  nextFloat(),
  nextFloat(),
  nextFloat(),
)

public fun ByteArray.decodeSamplerInfo(): SamplerInfo = NativeBuffer(this).decodeSamplerInfo()
