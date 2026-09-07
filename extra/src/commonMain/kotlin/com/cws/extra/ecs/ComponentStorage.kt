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
package com.cws.extra.ecs

import com.cws.extra.memory.IExtraList
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer

interface ComponentStorage {
    val list: IExtraList
    fun <T> add(componentIndex: Int, component: T)
    fun <T> has(component: T): Boolean
    fun remove(componentIndex: Int)

    fun sizeBytes(memoryLayout: MemoryLayout): Int
    fun sizeBytesPacked(memoryLayout: MemoryLayout): Int

    fun encode(buffer: NativeBuffer)
    fun encodeGpu(buffer: NativeBuffer)
    fun encodePacked(buffer: NativeBuffer)

    fun decode(buffer: NativeBuffer)
    fun decodeGpu(buffer: NativeBuffer)
    fun decodePacked(buffer: NativeBuffer)
}