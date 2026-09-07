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
import com.cws.extra.http.NativeBufferContent
import com.cws.extra.http.NativeBufferHttpFormat
import com.cws.extra.http.toContentType
import com.cws.extra.memory.NativeBuffer
import io.ktor.http.ContentType
import io.ktor.http.HttpStatusCode
import io.ktor.server.application.ApplicationCall
import io.ktor.server.response.respond

suspend fun ApplicationCall.respondNativeBuffer(
    buffer: NativeBuffer,
    offset: Int = 0,
    size: Int = buffer.limit - offset,
    chunkSize: Int = DEFAULT_NATIVE_BUFFER_CHUNK_SIZE,
    status: HttpStatusCode? = null,
    contentType: ContentType = NativeBufferHttpFormat(
        memoryLayout = buffer.memoryLayout,
        endian = buffer.endian,
    ).toContentType(),
) {
    respond(NativeBufferContent(buffer, offset, size, chunkSize, contentType = contentType, status = status))
}
