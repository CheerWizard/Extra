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
package com.cws.extra.math.matrices

import com.cws.extra.memory.*

import com.cws.extra.lists.decode
import com.cws.extra.lists.decodeGpu
import com.cws.extra.lists.sizeBytes
import com.cws.extra.lists.sizeBytesPacked
import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun Mat3List?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else m00.sizeBytes(memoryLayout) + m01.sizeBytes(memoryLayout) + m02.sizeBytes(memoryLayout) + m10.sizeBytes(memoryLayout) + m11.sizeBytes(memoryLayout) + m12.sizeBytes(memoryLayout) + m20.sizeBytes(memoryLayout) + m21.sizeBytes(memoryLayout) + m22.sizeBytes(memoryLayout)

public fun Mat3List?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else m00.sizeBytesPacked(memoryLayout) + m01.sizeBytesPacked(memoryLayout) + m02.sizeBytesPacked(memoryLayout) + m10.sizeBytesPacked(memoryLayout) + m11.sizeBytesPacked(memoryLayout) + m12.sizeBytesPacked(memoryLayout) + m20.sizeBytesPacked(memoryLayout) + m21.sizeBytesPacked(memoryLayout) + m22.sizeBytesPacked(memoryLayout)

public fun Mat3List?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun Mat3List?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun Mat3List?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun Mat3List?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
  }
}

public fun Mat3List?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
  }
}

public fun Mat3List?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
  }
}

public fun Mat3List?.encode(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(m00[i])
  buffer.pushFloat(m01[i])
  buffer.pushFloat(m02[i])
  buffer.pushFloat(m10[i])
  buffer.pushFloat(m11[i])
  buffer.pushFloat(m12[i])
  buffer.pushFloat(m20[i])
  buffer.pushFloat(m21[i])
  buffer.pushFloat(m22[i])
}

public fun Mat3List?.encodeGpu(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(m00[i])
  buffer.pushFloat(m01[i])
  buffer.pushFloat(m02[i])
  buffer.pushFloat(m10[i])
  buffer.pushFloat(m11[i])
  buffer.pushFloat(m12[i])
  buffer.pushFloat(m20[i])
  buffer.pushFloat(m21[i])
  buffer.pushFloat(m22[i])
}

public fun Mat3List.encodePacked(i: Int, buffer: NativeBuffer) {
  buffer.pushFloat(m00[i])
  buffer.pushFloat(m01[i])
  buffer.pushFloat(m02[i])
  buffer.pushFloat(m10[i])
  buffer.pushFloat(m11[i])
  buffer.pushFloat(m12[i])
  buffer.pushFloat(m20[i])
  buffer.pushFloat(m21[i])
  buffer.pushFloat(m22[i])
}

public fun NativeBuffer.decodeMat3List(): Mat3List {
  val decodedSize = nextInt()
  val buffer = this
  return Mat3List(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun NativeBuffer.decodeGpuMat3List(): Mat3List {
  val decodedSize = nextInt()
  val buffer = this
  return Mat3List(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun Mat3List.decode(i: Int, buffer: NativeBuffer) {
    m00.decode(i, buffer)
    m01.decode(i, buffer)
    m02.decode(i, buffer)
    m10.decode(i, buffer)
    m11.decode(i, buffer)
    m12.decode(i, buffer)
    m20.decode(i, buffer)
    m21.decode(i, buffer)
    m22.decode(i, buffer)
}

public fun Mat3List.decodeGpu(i: Int, buffer: NativeBuffer) {
    m00.decodeGpu(i, buffer)
    m01.decodeGpu(i, buffer)
    m02.decodeGpu(i, buffer)
    m10.decodeGpu(i, buffer)
    m11.decodeGpu(i, buffer)
    m12.decodeGpu(i, buffer)
    m20.decodeGpu(i, buffer)
    m21.decodeGpu(i, buffer)
    m22.decodeGpu(i, buffer)
}

public fun ByteArray.decodeMat3List(): Mat3List = NativeBuffer(this).decodeMat3List()
