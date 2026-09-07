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
package com.cws.extra.http

import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.NativeBuffer
import io.ktor.utils.io.ByteReadChannel
import io.ktor.utils.io.readAvailable

suspend fun ByteReadChannel.readNativeBuffer(
    wireFormat: NativeBufferHttpFormat,
    contentLength: Long? = null,
    memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
    maxSize: Int = Int.MAX_VALUE,
    chunkSize: Int = DEFAULT_NATIVE_BUFFER_CHUNK_SIZE,
): NativeBuffer {
    require(maxSize >= 0) { "maxSize must be non-negative" }
    require(chunkSize > 0) { "chunkSize must be positive" }
    require(contentLength == null || contentLength >= 0L) { "contentLength must be non-negative" }
    require(contentLength == null || contentLength <= maxSize.toLong()) {
        "NativeBuffer body is $contentLength bytes, exceeding maxSize $maxSize"
    }
    require(contentLength == null || contentLength <= Int.MAX_VALUE.toLong()) {
        "NativeBuffer body is too large for a single NativeBuffer: $contentLength bytes"
    }

    val initialCapacity = when {
        contentLength != null -> contentLength.toInt()
        maxSize == 0 -> 0
        else -> minOf(chunkSize, maxSize)
    }
    val destination = NativeBuffer(
        capacity = initialCapacity,
        memoryLayout = wireFormat.memoryLayout,
        endian = wireFormat.endian,
        memoryBoundary = memoryBoundary,
    )

    try {
        val received = readInto(destination, contentLength, maxSize, chunkSize)
        if (received != initialCapacity) destination.resize(received)
        return destination
    } catch (cause: Throwable) {
        destination.release()
        throw cause
    }
}

/**
 * Consumes this channel using one reused [NativeBuffer]. The chunk is valid
 * only for the duration of [block] and must be copied if it needs to be kept.
 */
suspend fun ByteReadChannel.forEachNativeBufferChunk(
    wireFormat: NativeBufferHttpFormat,
    contentLength: Long? = null,
    memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
    maxSize: Long = Long.MAX_VALUE,
    chunkSize: Int = DEFAULT_NATIVE_BUFFER_CHUNK_SIZE,
    block: suspend (offset: Long, chunk: NativeBuffer) -> Unit,
) {
    require(chunkSize > 0) { "chunkSize must be positive" }
    require(maxSize >= 0L) { "maxSize must be non-negative" }
    require(contentLength == null || contentLength >= 0L) { "contentLength must be non-negative" }
    require(contentLength == null || contentLength <= maxSize) {
        "NativeBuffer body is $contentLength bytes, exceeding maxSize $maxSize"
    }

    val staging = ByteArray(chunkSize)
    val chunk = NativeBuffer(
        capacity = chunkSize,
        memoryLayout = wireFormat.memoryLayout,
        endian = wireFormat.endian,
        memoryBoundary = memoryBoundary,
    )
    var offset = 0L

    try {
        while (contentLength == null || offset < contentLength) {
            val remaining = contentLength?.minus(offset)
            val target = if (remaining != null && remaining < staging.size) {
                ByteArray(remaining.toInt())
            } else {
                staging
            }
            val count = readChunk(target)
            if (count == 0) break
            if (offset > maxSize - count) {
                throw IllegalArgumentException("NativeBuffer body exceeds maxSize $maxSize")
            }

            chunk.setByteArray(0, target)
            if (count != chunk.limit) chunk.resize(count)
            block(offset, chunk)
            offset += count
            if (count < target.size) break
        }

        require(contentLength == null || offset == contentLength) {
            "NativeBuffer body ended after $offset bytes; expected $contentLength"
        }
    } finally {
        chunk.release()
    }
}

private suspend fun ByteReadChannel.readInto(
    destination: NativeBuffer,
    contentLength: Long?,
    maxSize: Int,
    chunkSize: Int,
): Int {
    val stagingSize = when {
        contentLength != null && contentLength > 0L -> minOf(chunkSize.toLong(), contentLength).toInt()
        else -> minOf(chunkSize, maxOf(1, maxSize))
    }
    val staging = ByteArray(stagingSize)
    var capacity = destination.limit
    var destinationOffset = 0

    while (true) {
        val remaining = contentLength?.minus(destinationOffset.toLong())
        if (remaining == 0L) break
        val target = if (remaining != null && remaining < staging.size) {
            ByteArray(remaining.toInt())
        } else {
            staging
        }
        val count = readChunk(target)
        if (count == 0) break
        if (destinationOffset > maxSize - count) {
            throw IllegalArgumentException("NativeBuffer body exceeds maxSize $maxSize")
        }

        val required = destinationOffset + target.size
        if (required > capacity) {
            var newCapacity = maxOf(capacity, 1)
            while (newCapacity < required) {
                newCapacity = minOf(maxSize, maxOf(required, newCapacity + maxOf(1, newCapacity / 2)))
                if (newCapacity < required) {
                    throw IllegalArgumentException("NativeBuffer body exceeds maxSize $maxSize")
                }
            }
            destination.resize(newCapacity)
            capacity = newCapacity
        }

        destination.setByteArray(destinationOffset, target)
        destinationOffset += count
        if (count < target.size) break
    }

    require(contentLength == null || destinationOffset.toLong() == contentLength) {
        "NativeBuffer body ended after $destinationOffset bytes; expected $contentLength"
    }
    return destinationOffset
}

private suspend fun ByteReadChannel.readChunk(destination: ByteArray): Int {
    var offset = 0
    while (offset < destination.size) {
        val count = readAvailable(destination, offset, destination.size - offset)
        if (count < 0) break
        if (count == 0) continue
        offset += count
    }
    return offset
}
