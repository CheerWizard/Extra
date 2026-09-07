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
package com.cws.extra.math.vectors

import com.cws.extra.lists.UIntList
import com.cws.extra.memory.ExtraDataSoA
import com.cws.extra.memory.IExtraList
import kotlin.random.Random
import kotlinx.serialization.Serializable

fun UInt4List(capacity: Int) = UInt4List(
   x = UIntList(capacity),
   y = UIntList(capacity),
   z = UIntList(capacity),
   w = UIntList(capacity),
)

@ExtraDataSoA
data class UInt4List(
       val x: UIntList,
   val y: UIntList,
   val z: UIntList,
   val w: UIntList,
): IExtraList {

    val capacity: Int get() = x.capacity

    val size: Int get() = x.size

    val isEmpty: Boolean
        get() = size == 0

    val isNotEmpty: Boolean
        get() = size != 0

    val indices: IntRange
        get() = 0 until size

    val lastIndex: Int
        get() = size - 1

    fun clear() {
       x.clear()
   y.clear()
   z.clear()
   w.clear()
    }

    operator fun set(i: Int, value: UInt4) {
       x[i] = value.x
   y[i] = value.y
   z[i] = value.z
   w[i] = value.w
    }

    fun add(value: UInt4) {
       x.add(value.x)
   y.add(value.y)
   z.add(value.z)
   w.add(value.w)
    }

    fun addAll(values: UInt4List) {
       x.addAll(values.x)
   y.addAll(values.y)
   z.addAll(values.z)
   w.addAll(values.w)
    }

   fun addFrom(
            source: UInt4List,
            index: Int
        ) {
               x.addFrom(source.x, index)
   y.addFrom(source.y, index)
   z.addFrom(source.z, index)
   w.addFrom(source.w, index)
        }

    fun push(value: UInt4) = add(value)


    fun trimToSize() {
           x.trimToSize()
   y.trimToSize()
   z.trimToSize()
   w.trimToSize()
    }

    fun reserve(capacity: Int) {
           x.reserve(capacity)
   y.reserve(capacity)
   z.reserve(capacity)
   w.reserve(capacity)
    }

    fun resize(newSize: Int) {
           x.resize(newSize)
   y.resize(newSize)
   z.resize(newSize)
   w.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           x.ensureCapacity(newCapacity)
   y.ensureCapacity(newCapacity)
   z.ensureCapacity(newCapacity)
   w.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           x.removeAtSwap(index)
   y.removeAtSwap(index)
   z.removeAtSwap(index)
   w.removeAtSwap(index)
    }

    fun clone(): UInt4List {
        val copy = UInt4List(   x.clone(),
   y.clone(),
   z.clone(),
   w.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           x.shuffle(random)
   y.shuffle(random)
   z.shuffle(random)
   w.shuffle(random)
    }

   inline fun forEach(block: UInt4List.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: UInt4List.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: UInt4List.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: UInt4List.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: UInt4List.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: UInt4List.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: UInt4List.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: UInt4List,
        predicate: UInt4List.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}