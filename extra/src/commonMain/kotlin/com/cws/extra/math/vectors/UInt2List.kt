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

fun UInt2List(capacity: Int) = UInt2List(
   x = UIntList(capacity),
   y = UIntList(capacity),
)

@ExtraDataSoA
data class UInt2List(
       val x: UIntList,
   val y: UIntList,
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
    }

    operator fun set(i: Int, value: UInt2) {
       x[i] = value.x
   y[i] = value.y
    }

    fun add(value: UInt2) {
       x.add(value.x)
   y.add(value.y)
    }

    fun addAll(values: UInt2List) {
       x.addAll(values.x)
   y.addAll(values.y)
    }

   fun addFrom(
            source: UInt2List,
            index: Int
        ) {
               x.addFrom(source.x, index)
   y.addFrom(source.y, index)
        }

    fun push(value: UInt2) = add(value)


    fun trimToSize() {
           x.trimToSize()
   y.trimToSize()
    }

    fun reserve(capacity: Int) {
           x.reserve(capacity)
   y.reserve(capacity)
    }

    fun resize(newSize: Int) {
           x.resize(newSize)
   y.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           x.ensureCapacity(newCapacity)
   y.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           x.removeAtSwap(index)
   y.removeAtSwap(index)
    }

    fun clone(): UInt2List {
        val copy = UInt2List(   x.clone(),
   y.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           x.shuffle(random)
   y.shuffle(random)
    }

   inline fun forEach(block: UInt2List.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: UInt2List.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: UInt2List.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: UInt2List.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: UInt2List.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: UInt2List.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: UInt2List.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: UInt2List,
        predicate: UInt2List.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}