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

import com.cws.extra.lists.IntList
import com.cws.extra.memory.ExtraDataSoA
import com.cws.extra.memory.IExtraList
import kotlin.random.Random
import kotlinx.serialization.Serializable

fun RenderableList(capacity: Int) = RenderableList(
   textureId = IntList(capacity),
)

@ExtraDataSoA
data class RenderableList(
       val textureId: IntList,
): IExtraList {

    val capacity: Int get() = textureId.capacity

    val size: Int get() = textureId.size

    val isEmpty: Boolean
        get() = size == 0

    val isNotEmpty: Boolean
        get() = size != 0

    val indices: IntRange
        get() = 0 until size

    val lastIndex: Int
        get() = size - 1

    fun clear() {
       textureId.clear()
    }

    operator fun set(i: Int, value: Renderable) {
       textureId[i] = value.textureId
    }

    fun add(value: Renderable) {
       textureId.add(value.textureId)
    }

    fun addAll(values: RenderableList) {
       textureId.addAll(values.textureId)
    }

   fun addFrom(
            source: RenderableList,
            index: Int
        ) {
               textureId.addFrom(source.textureId, index)
        }

    fun push(value: Renderable) = add(value)


    fun trimToSize() {
           textureId.trimToSize()
    }

    fun reserve(capacity: Int) {
           textureId.reserve(capacity)
    }

    fun resize(newSize: Int) {
           textureId.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           textureId.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           textureId.removeAtSwap(index)
    }

    fun clone(): RenderableList {
        val copy = RenderableList(   textureId.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           textureId.shuffle(random)
    }

   inline fun forEach(block: RenderableList.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: RenderableList.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: RenderableList.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: RenderableList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: RenderableList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: RenderableList.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: RenderableList.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: RenderableList,
        predicate: RenderableList.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}