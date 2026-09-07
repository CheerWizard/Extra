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

import com.cws.extra.lists.FloatList
import com.cws.extra.memory.ExtraDataSoA
import com.cws.extra.memory.IExtraList
import kotlin.random.Random
import kotlinx.serialization.Serializable

fun TestEnumRawList(capacity: Int) = TestEnumRawList(
   rawValue = FloatList(capacity),
)

@ExtraDataSoA
data class TestEnumRawList(
       val rawValue: FloatList,
): IExtraList {

    val capacity: Int get() = rawValue.capacity

    val size: Int get() = rawValue.size

    val isEmpty: Boolean
        get() = size == 0

    val isNotEmpty: Boolean
        get() = size != 0

    val indices: IntRange
        get() = 0 until size

    val lastIndex: Int
        get() = size - 1

    fun clear() {
       rawValue.clear()
    }

    operator fun set(i: Int, value: TestEnumRaw) {
       rawValue[i] = value.rawValue
    }

    fun add(value: TestEnumRaw) {
       rawValue.add(value.rawValue)
    }

    fun addAll(values: TestEnumRawList) {
       rawValue.addAll(values.rawValue)
    }

   fun addFrom(
            source: TestEnumRawList,
            index: Int
        ) {
               rawValue.addFrom(source.rawValue, index)
        }

    fun push(value: TestEnumRaw) = add(value)


    fun trimToSize() {
           rawValue.trimToSize()
    }

    fun reserve(capacity: Int) {
           rawValue.reserve(capacity)
    }

    fun resize(newSize: Int) {
           rawValue.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           rawValue.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           rawValue.removeAtSwap(index)
    }

    fun clone(): TestEnumRawList {
        val copy = TestEnumRawList(   rawValue.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           rawValue.shuffle(random)
    }

   inline fun forEach(block: TestEnumRawList.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: TestEnumRawList.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: TestEnumRawList.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: TestEnumRawList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: TestEnumRawList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: TestEnumRawList.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: TestEnumRawList.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: TestEnumRawList,
        predicate: TestEnumRawList.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}