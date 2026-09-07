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

import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryLayout
import io.ktor.http.ContentType

/**
 * Describes how raw NativeBuffer bytes are represented in an HTTP body.
 * Memory boundary is deliberately absent because it is a local allocation
 * policy selected independently by the sender and receiver.
 */
data class NativeBufferHttpFormat(
    val memoryLayout: MemoryLayout = MemoryLayout.KOTLIN,
    val endian: Endian = Endian.LITTLE,
) {
    companion object {
        const val MEDIA_TYPE = "application/vnd.extra.native-buffer"
        const val VERSION_PARAMETER = "version"
        const val MEMORY_LAYOUT_PARAMETER = "layout"
        const val ENDIAN_PARAMETER = "endian"
    }
}

val NativeBufferContentType: ContentType = ContentType.parse(NativeBufferHttpFormat.MEDIA_TYPE)

fun NativeBufferHttpFormat.toContentType(): ContentType = NativeBufferContentType
    .withParameter(NativeBufferHttpFormat.MEMORY_LAYOUT_PARAMETER, memoryLayout.name.lowercase())
    .withParameter(NativeBufferHttpFormat.ENDIAN_PARAMETER, endian.name.lowercase())

fun ContentType.toNativeBufferHttpFormat(): NativeBufferHttpFormat {
    require(match(NativeBufferContentType)) {
        "Expected ${NativeBufferHttpFormat.MEDIA_TYPE}, received $this"
    }

    val memoryLayout = enumParameter(
        NativeBufferHttpFormat.MEMORY_LAYOUT_PARAMETER,
        MemoryLayout.KOTLIN,
        MemoryLayout.entries,
    )

    val endian = enumParameter(
        NativeBufferHttpFormat.ENDIAN_PARAMETER,
        Endian.LITTLE,
        Endian.entries,
    )

    return NativeBufferHttpFormat(memoryLayout, endian)
}

private fun <T : Enum<T>> ContentType.enumParameter(
    name: String,
    default: T,
    entries: List<T>,
): T {
    val value = parameter(name) ?: return default
    return entries.firstOrNull { it.name.equals(value, ignoreCase = true) }
        ?: throw IllegalArgumentException("Unsupported $name value: $value")
}
