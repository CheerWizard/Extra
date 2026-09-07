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
package com.cws.extra.client

import com.cws.extra.http.DEFAULT_NATIVE_BUFFER_CHUNK_SIZE
import com.cws.extra.http.NativeBufferHttpFormat
import com.cws.extra.http.forEachNativeBufferChunk
import com.cws.extra.http.readNativeBuffer
import com.cws.extra.http.toNativeBufferHttpFormat
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.NativeBuffer
import io.ktor.client.call.body
import io.ktor.client.statement.HttpResponse
import io.ktor.http.contentLength
import io.ktor.http.contentType
import io.ktor.utils.io.ByteReadChannel

suspend fun HttpResponse.bodyAsNativeBuffer(
    memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
    maxSize: Int = Int.MAX_VALUE,
    chunkSize: Int = DEFAULT_NATIVE_BUFFER_CHUNK_SIZE,
): NativeBuffer {
    val channel: ByteReadChannel = body()
    return channel.readNativeBuffer(
        wireFormat = nativeBufferHttpFormat(),
        contentLength = contentLength(),
        memoryBoundary = memoryBoundary,
        maxSize = maxSize,
        chunkSize = chunkSize,
    )
}

suspend fun <T> HttpResponse.decodeNativeBuffer(
    memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
    maxSize: Int = Int.MAX_VALUE,
    chunkSize: Int = DEFAULT_NATIVE_BUFFER_CHUNK_SIZE,
    decode: NativeBuffer.() -> T,
): T {
    val buffer = bodyAsNativeBuffer(memoryBoundary, maxSize, chunkSize)
    return try {
        buffer.decode()
    } finally {
        buffer.release()
    }
}

/**
 * Consumes the response using a single reused [NativeBuffer]. The chunk is only
 * valid for the duration of [block] and must be copied if it needs to be kept.
 */
suspend fun HttpResponse.forEachNativeBufferChunk(
    memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
    maxSize: Long = Long.MAX_VALUE,
    chunkSize: Int = DEFAULT_NATIVE_BUFFER_CHUNK_SIZE,
    block: suspend (offset: Long, chunk: NativeBuffer) -> Unit,
) {
    val channel: ByteReadChannel = body()
    channel.forEachNativeBufferChunk(
        wireFormat = nativeBufferHttpFormat(),
        contentLength = contentLength(),
        memoryBoundary = memoryBoundary,
        maxSize = maxSize,
        chunkSize = chunkSize,
        block = block,
    )
}

private fun HttpResponse.nativeBufferHttpFormat(): NativeBufferHttpFormat {
    val contentType = contentType() ?: throw IllegalArgumentException("NativeBuffer response has no Content-Type")
    return contentType.toNativeBufferHttpFormat()
}
