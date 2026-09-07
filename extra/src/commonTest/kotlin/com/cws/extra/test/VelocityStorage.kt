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

import com.cws.extra.ecs.*
import com.cws.extra.memory.*

val Scene.velocity: VelocityList get() = components.getComponentList<Velocity, VelocityList>()

inline fun VelocityStorage(componentCount: Int) = VelocityStorage(VelocityList(componentCount))

data class VelocityStorage(
    override val list: VelocityList,
) : ComponentStorage {

    override fun <T> has(component: T): Boolean = component as? Velocity != null

    override fun <T> add(componentIndex: Int, component: T) {
        val c = component as? Velocity ?: return
        if (componentIndex == list.size) {
            list.add(c)
        } else {
            list[componentIndex] = c
        }
    }

    override fun remove(componentIndex: Int) {
        list.removeAtSwap(componentIndex)
    }

    override fun sizeBytes(memoryLayout: MemoryLayout): Int = list.sizeBytes(memoryLayout)
    override fun sizeBytesPacked(memoryLayout: MemoryLayout): Int = list.sizeBytesPacked(memoryLayout)

    override fun encode(buffer: NativeBuffer) = list.encode(buffer)
    override fun encodeGpu(buffer: NativeBuffer) = list.encodeGpu(buffer)
    override fun encodePacked(buffer: NativeBuffer) = list.encodePacked(buffer)

    override fun decode(buffer: NativeBuffer) {
        list.resize(buffer.nextInt())
        for (i in 0 until list.size) {
            list.decode(i, buffer)
        }
    }

    override fun decodeGpu(buffer: NativeBuffer) {
        list.resize(buffer.nextInt())
        for (i in 0 until list.size) {
            list.decodeGpu(i, buffer)
        }
    }

    override fun decodePacked(buffer: NativeBuffer) {
        list.resize(buffer.nextInt())
        for (i in 0 until list.size) {
            list.decodeGpu(i, buffer)
        }
    }

}