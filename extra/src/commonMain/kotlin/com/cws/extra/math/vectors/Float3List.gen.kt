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
package com.cws.extra.math.vectors

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

public fun Float3List?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else x.sizeBytes(memoryLayout) + y.sizeBytes(memoryLayout) + z.sizeBytes(memoryLayout)

public fun Float3List?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else x.sizeBytesPacked(memoryLayout) + y.sizeBytesPacked(memoryLayout) + z.sizeBytesPacked(memoryLayout)

public fun Float3List?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun Float3List?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun Float3List?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun Float3List?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
  }
}

public fun Float3List?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
  }
}

public fun Float3List?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
  }
}

public fun Float3List?.encode(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(x[i])
  buffer.pushFloat(y[i])
  buffer.pushFloat(z[i])
}

public fun Float3List?.encodeGpu(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushFloat(x[i])
  buffer.pushFloat(y[i])
  buffer.pushFloat(z[i])
}

public fun Float3List.encodePacked(i: Int, buffer: NativeBuffer) {
  buffer.pushFloat(x[i])
  buffer.pushFloat(y[i])
  buffer.pushFloat(z[i])
}

public fun NativeBuffer.decodeFloat3List(): Float3List {
  val decodedSize = nextInt()
  val buffer = this
  return Float3List(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun NativeBuffer.decodeGpuFloat3List(): Float3List {
  val decodedSize = nextInt()
  val buffer = this
  return Float3List(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun Float3List.decode(i: Int, buffer: NativeBuffer) {
    x.decode(i, buffer)
    y.decode(i, buffer)
    z.decode(i, buffer)
}

public fun Float3List.decodeGpu(i: Int, buffer: NativeBuffer) {
    x.decodeGpu(i, buffer)
    y.decodeGpu(i, buffer)
    z.decodeGpu(i, buffer)
}

public fun ByteArray.decodeFloat3List(): Float3List = NativeBuffer(this).decodeFloat3List()
