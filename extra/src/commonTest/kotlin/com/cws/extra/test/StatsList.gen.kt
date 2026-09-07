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

public fun StatsList?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else health.sizeBytes(memoryLayout) + mana.sizeBytes(memoryLayout) + stamina.sizeBytes(memoryLayout) + level.sizeBytes(memoryLayout) + alive.sizeBytes(memoryLayout)

public fun StatsList?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else health.sizeBytesPacked(memoryLayout) + mana.sizeBytesPacked(memoryLayout) + stamina.sizeBytesPacked(memoryLayout) + level.sizeBytesPacked(memoryLayout) + alive.sizeBytesPacked(memoryLayout)

public fun StatsList?.encode(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encode(buffer)
  return buffer
}

public fun StatsList?.encodeGpu(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytes(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodeGpu(buffer)
  return buffer
}

public fun StatsList?.encodePacked(
  memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
  endian: Endian = Endian.LITTLE,
  memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
): NativeBuffer {
  if (this == null) return NativeBuffer(0)
  val buffer = NativeBuffer(capacity = sizeBytesPacked(memoryLayout), memoryLayout = memoryLayout, endian = endian, memoryBoundary = memoryBoundary)
  encodePacked(buffer)
  return buffer
}

public fun StatsList?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
       encode(i, buffer)
  }
}

public fun StatsList?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
       encodeGpu(i, buffer)
  }
}

public fun StatsList?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(size)
  for (i in 0 until size) {
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
       encodePacked(i, buffer)
  }
}

public fun StatsList?.encode(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(health[i])
  buffer.pushFloat(mana[i])
  buffer.pushDouble(stamina[i])
  buffer.pushShort(level[i])
  buffer.pushBoolean(alive[i])
}

public fun StatsList?.encodeGpu(i: Int, buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(health[i])
  buffer.pushFloat(mana[i])
  buffer.pushDouble(stamina[i])
  buffer.pushShort(level[i])
  buffer.pushBoolean(alive[i])
}

public fun StatsList.encodePacked(i: Int, buffer: NativeBuffer) {
  buffer.pushInt(health[i])
  buffer.pushFloat(mana[i])
  buffer.pushDouble(stamina[i])
  buffer.pushShort(level[i])
  buffer.pushBoolean(alive[i])
}

public fun NativeBuffer.decodeStatsList(): StatsList {
  val decodedSize = nextInt()
  val buffer = this
  return StatsList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun NativeBuffer.decodeGpuStatsList(): StatsList {
  val decodedSize = nextInt()
  val buffer = this
  return StatsList(decodedSize).apply {  
      for (i in 0 until decodedSize) {
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
        decode(i, buffer)
    }
  }
}

public fun StatsList.decode(i: Int, buffer: NativeBuffer) {
    health.decode(i, buffer)
    mana.decode(i, buffer)
    stamina.decode(i, buffer)
    level.decode(i, buffer)
    alive.decode(i, buffer)
}

public fun StatsList.decodeGpu(i: Int, buffer: NativeBuffer) {
    health.decodeGpu(i, buffer)
    mana.decodeGpu(i, buffer)
    stamina.decodeGpu(i, buffer)
    level.decodeGpu(i, buffer)
    alive.decodeGpu(i, buffer)
}

public fun ByteArray.decodeStatsList(): StatsList = NativeBuffer(this).decodeStatsList()
