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
package com.cws.extra.server

import com.cws.extra.http.DEFAULT_NATIVE_BUFFER_CHUNK_SIZE
import com.cws.extra.http.forEachNativeBufferChunk
import com.cws.extra.http.readNativeBuffer
import com.cws.extra.http.toNativeBufferHttpFormat
import com.cws.extra.memory.MemoryBoundary
import com.cws.extra.memory.NativeBuffer
import io.ktor.server.application.ApplicationCall
import io.ktor.server.request.contentLength
import io.ktor.server.request.contentType
import io.ktor.server.request.receiveChannel

suspend fun ApplicationCall.receiveNativeBuffer(
    memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
    maxSize: Int = Int.MAX_VALUE,
    chunkSize: Int = DEFAULT_NATIVE_BUFFER_CHUNK_SIZE,
): NativeBuffer = receiveChannel().readNativeBuffer(
    wireFormat = request.contentType().toNativeBufferHttpFormat(),
    contentLength = request.contentLength(),
    memoryBoundary = memoryBoundary,
    maxSize = maxSize,
    chunkSize = chunkSize,
)

suspend fun <T> ApplicationCall.receiveDecodedNativeBuffer(
    memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
    maxSize: Int = Int.MAX_VALUE,
    chunkSize: Int = DEFAULT_NATIVE_BUFFER_CHUNK_SIZE,
    decode: NativeBuffer.() -> T,
): T {
    val buffer = receiveNativeBuffer(memoryBoundary, maxSize, chunkSize)
    return try {
        buffer.decode()
    } finally {
        buffer.release()
    }
}

/**
 * Consumes the request using a single reused [NativeBuffer]. The chunk is only
 * valid for the duration of [block] and must be copied if it needs to be kept.
 */
suspend fun ApplicationCall.forEachNativeBufferChunk(
    memoryBoundary: MemoryBoundary = MemoryBoundary.KOTLIN_HEAP,
    maxSize: Long = Long.MAX_VALUE,
    chunkSize: Int = DEFAULT_NATIVE_BUFFER_CHUNK_SIZE,
    block: suspend (offset: Long, chunk: NativeBuffer) -> Unit,
) {
    receiveChannel().forEachNativeBufferChunk(
        wireFormat = request.contentType().toNativeBufferHttpFormat(),
        contentLength = request.contentLength(),
        memoryBoundary = memoryBoundary,
        maxSize = maxSize,
        chunkSize = chunkSize,
        block = block,
    )
}
