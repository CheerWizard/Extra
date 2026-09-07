package com.cws.extra.test

import com.cws.extra.memory.*

import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import kotlin.ByteArray
import kotlin.Int

public fun PipelineStage?.sizeBytes(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun PipelineStage?.sizeBytesPacked(memoryLayout: MemoryLayout): Int = if (this == null) 0 else Int.SIZE_BYTES

public fun PipelineStage?.encode(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun PipelineStage?.encodeGpu(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun PipelineStage?.encodePacked(buffer: NativeBuffer) {
  if (this == null) return
  buffer.pushInt(rawValue)
}

public fun ByteArray.decodePipelineStage(): PipelineStage = NativeBuffer(this).decodePipelineStage()

public fun NativeBuffer.decodePipelineStage(): PipelineStage {
  val rawValue = nextInt()
  return PipelineStage.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of PipelineStage")
}

public fun NativeBuffer.decodeGpuPipelineStage(): PipelineStage {
  val rawValue = nextInt()
  return PipelineStage.entries.find { it.rawValue == rawValue } ?: error("Can't find rawValue inside of PipelineStage")
}

public val PipelineStage.`value`: Int
  get() = rawValue
