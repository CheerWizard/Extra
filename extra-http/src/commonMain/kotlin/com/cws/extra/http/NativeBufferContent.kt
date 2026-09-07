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

import com.cws.extra.memory.NativeBuffer
import com.cws.print.Print
import io.ktor.http.ContentType
import io.ktor.http.HttpStatusCode
import io.ktor.http.content.OutgoingContent
import io.ktor.utils.io.ByteWriteChannel
import io.ktor.utils.io.writeFully

const val DEFAULT_NATIVE_BUFFER_CHUNK_SIZE: Int = 64 * 1024

/**
 * Direction-neutral Ktor body content. Ktor Client uses it for request bodies;
 * Ktor Server uses the same class for response bodies.
 *
 * The caller owns [buffer] and must keep it alive until Ktor finishes writing
 * this content.
 */
class NativeBufferContent(
    private val buffer: NativeBuffer,
    private val offset: Int = 0,
    private val size: Int = buffer.limit - offset,
    private val chunkSize: Int = DEFAULT_NATIVE_BUFFER_CHUNK_SIZE,
    wireFormat: NativeBufferHttpFormat = NativeBufferHttpFormat(
        memoryLayout = buffer.memoryLayout,
        endian = buffer.endian,
    ),
    override val contentType: ContentType = wireFormat.toContentType(),
    override val status: HttpStatusCode? = null,
) : OutgoingContent.WriteChannelContent() {

    companion object {
        private const val TAG = "NativeBufferContent"
    }

    override val contentLength: Long = size.toLong()

    override suspend fun writeTo(channel: ByteWriteChannel) {
        writeNativeBuffer(channel, buffer, offset, size, chunkSize)
    }

    private suspend fun writeNativeBuffer(
        channel: ByteWriteChannel,
        buffer: NativeBuffer,
        offset: Int = 0,
        size: Int = buffer.limit - offset,
        chunkSize: Int = DEFAULT_NATIVE_BUFFER_CHUNK_SIZE,
    ) {
        if (offset < 0) {
            Print.e(TAG) {
                "NativeBuffer offset must be non-negative. offset = $offset"
            }
            return
        }

        if (size <= 0) {
            Print.e(TAG) {
                "NativeBuffer size must be non-negative and not zero. size = $size"
            }
            return
        }

        if (offset > buffer.limit - size) {
            Print.e(TAG) {
                "NativeBuffer range [$offset, ${offset + size}) exceeds limit ${buffer.limit}"
            }
            return
        }

        if (chunkSize < 0) {
            Print.e(TAG) {
                "Chunk size must be non-negative. chunkSize = $chunkSize"
            }
            return
        }

        val chunk = ByteArray(minOf(chunkSize, size))
        var srcOffset = offset
        var remaining = size
        while (remaining > 0) {
            val sizeBytes = minOf(chunk.size, remaining)
            buffer.copyToByteArray(chunk, srcOffset, sizeBytes)
            channel.writeFully(chunk, 0, sizeBytes)
            srcOffset += sizeBytes
            remaining -= sizeBytes
        }
    }
}
