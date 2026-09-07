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
@file:Suppress("NOTHING_TO_INLINE")
@file:OptIn(ExperimentalUnsignedTypes::class)

package com.cws.extra.lists

import com.cws.extra.memory.ExtraData
import com.cws.extra.memory.NativeBuffer
import com.cws.extra.memory.nextChar
import com.cws.extra.memory.nextDouble
import com.cws.extra.memory.pushChar
import com.cws.extra.memory.pushDouble
import kotlinx.serialization.Serializable

import kotlin.math.abs
import kotlin.math.roundToInt
import kotlin.random.Random

inline fun DoubleList(
    capacity: Int = 16,
    noinline init: (Int) -> Double = { 0.0 }
) = DoubleList(0, DoubleArray(capacity, init))

@Serializable
@ExtraData
class DoubleList(
    var size: Int = 0,
    var array: DoubleArray,
) {

    @PublishedApi
    internal var __sortStack: LongArray? = null

    inline val capacity: Int
        get() = array.size

    inline val isEmpty: Boolean
        get() = size == 0

    inline val isNotEmpty: Boolean
        get() = size != 0

    inline val indices: IntRange
        get() = 0 until size

    inline val lastIndex: Int
        get() = size - 1

    inline fun clear() {
        size = 0
    }

    inline fun first(): Double {
        return array[0]
    }

    inline fun last(): Double {
        return array[size - 1]
    }

    inline operator fun get(index: Int): Double {
        return array[index]
    }

    inline operator fun set(index: Int, value: Double) {
        array[index] = value
    }

    inline fun add(value: Double) {
        ensureCapacity(size + 1)
        addUnsafe(value)
    }

    inline fun addUnsafe(value: Double) {
        array[size++] = value
    }

    inline fun addAll(values: DoubleArray, start: Int = 0, end: Int = values.size) {
        ensureCapacity(size + abs(end - start))
        addAllUnsafe(values, start, end)
    }

    inline fun addAllUnsafe(values: DoubleArray, start: Int = 0, end: Int = values.size) {
        val valuesSize = abs(end - start)
        values.copyInto(
            destination = array,
            destinationOffset = size,
            startIndex = start,
            endIndex = end,
        )
        size += valuesSize
    }

    inline fun addAll(values: DoubleList) = addAll(values.array, 0, values.size)

    inline fun push(value: Double) = add(value)

    inline fun pop(): Double {
        return array[--size]
    }

    inline fun removeLast(): Double = pop()

    inline fun resize(newSize: Int) {
        if (newSize > capacity) {
            reallocate(newSize)
        }
        size = newSize
    }

    inline fun ensureCapacity(newCapacity: Int) {
        if (newCapacity > array.size) {
            reallocate(newCapacity)
        }
    }

    inline fun reallocate(newCapacity: Int) {
        array = array.copyOf((newCapacity * 1.1f).roundToInt())
    }

    inline fun trimToSize() {
        if (size != capacity) {
            array = array.copyOf(size)
        }
    }

    inline fun reserve(capacity: Int) {
        ensureCapacity(capacity)
    }

    inline fun removeAtSwap(index: Int): Double {
        val removed = array[index]
        val last = --size

        if (index != last) {
            array[index] = array[last]
        }

        return removed
    }

    inline fun clone(): DoubleList {
        return DoubleList(size, array.copyOf())
    }

    inline fun forEach(block: (Double) -> Unit) {
        for (i in 0 until size) {
            block(array[i])
        }
    }

    inline fun forEachIndexed(block: (Int, Double) -> Unit) {
        for (i in 0 until size) {
            block(i, array[i])
        }
    }

    inline fun find(block: (Double) -> Boolean): Double? {
        for (i in 0 until size) {
            val value = array[i]
            if (block(value)) {
                return value
            }
        }
        return null
    }

    inline fun findIndex(block: (Double) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(array[i])) {
                return i
            }
        }
        return -1
    }

    inline fun filter(block: (Double) -> Boolean): DoubleList {
        val result = DoubleList(size)

        for (i in 0 until size) {
            val value = array[i]
            if (block(value)) {
                result.add(value)
            }
        }

        return result
    }

    inline fun filterWith(block: (Double) -> Boolean): DoubleList {
        var writeIndex = 0
        for (readIndex in 0 until size) {
            val value = array[readIndex]
            if (block(value)) array[writeIndex++] = value
        }
        size = writeIndex
        return this
    }

    inline fun sort() {
        array.sort(0, size)
    }

    inline fun sortDescending() {
        array.sortDescending(0, size)
    }

    inline fun sorted(): DoubleList =
        clone().apply { sort() }

    inline fun sortedDescending(): DoubleList =
        clone().apply { sortDescending() }


    inline fun sortByInt(crossinline selector: (Double) -> Int) {
        if (size < 2) return
        val stack = __sortStack ?: LongArray(64).also { __sortStack = it }
        var stackSize = 0
        stack[stackSize++] = (size - 1).toLong() and 0xffffffffL

        while (stackSize > 0) {
            val range = stack[--stackSize]
            var from = (range ushr 32).toInt()
            var to = range.toInt()

            while (from < to) {
                var left = from
                var right = to
                val first = selector(array[from])
                val middle = selector(array[(from + to) ushr 1])
                val last = selector(array[to])
                val pivot = if (first < middle) {
                    if (middle < last) middle else if (first < last) last else first
                } else {
                    if (first < last) first else if (middle < last) last else middle
                }

                while (left <= right) {
                    while (selector(array[left]) < pivot) left++
                    while (selector(array[right]) > pivot) right--
                    if (left <= right) {
                        val value = array[left]
                        array[left++] = array[right]
                        array[right--] = value
                    }
                }

                if (right - from < to - left) {
                    if (left < to) stack[stackSize++] = (left.toLong() shl 32) or (to.toLong() and 0xffffffffL)
                    to = right
                } else {
                    if (from < right) stack[stackSize++] = (from.toLong() shl 32) or (right.toLong() and 0xffffffffL)
                    from = left
                }
            }
        }
    }

    inline fun sortByLong(crossinline selector: (Double) -> Long) {
        if (size < 2) return
        val stack = __sortStack ?: LongArray(64).also { __sortStack = it }
        var stackSize = 0
        stack[stackSize++] = (size - 1).toLong() and 0xffffffffL

        while (stackSize > 0) {
            val range = stack[--stackSize]
            var from = (range ushr 32).toInt()
            var to = range.toInt()

            while (from < to) {
                var left = from
                var right = to
                val first = selector(array[from])
                val middle = selector(array[(from + to) ushr 1])
                val last = selector(array[to])
                val pivot = if (first < middle) {
                    if (middle < last) middle else if (first < last) last else first
                } else {
                    if (first < last) first else if (middle < last) last else middle
                }

                while (left <= right) {
                    while (selector(array[left]) < pivot) left++
                    while (selector(array[right]) > pivot) right--
                    if (left <= right) {
                        val value = array[left]
                        array[left++] = array[right]
                        array[right--] = value
                    }
                }

                if (right - from < to - left) {
                    if (left < to) stack[stackSize++] = (left.toLong() shl 32) or (to.toLong() and 0xffffffffL)
                    to = right
                } else {
                    if (from < right) stack[stackSize++] = (from.toLong() shl 32) or (right.toLong() and 0xffffffffL)
                    from = left
                }
            }
        }
    }

    inline fun sortByFloat(crossinline selector: (Double) -> Float) {
        if (size < 2) return
        val stack = __sortStack ?: LongArray(64).also { __sortStack = it }
        var stackSize = 0
        stack[stackSize++] = (size - 1).toLong() and 0xffffffffL

        while (stackSize > 0) {
            val range = stack[--stackSize]
            var from = (range ushr 32).toInt()
            var to = range.toInt()

            while (from < to) {
                var left = from
                var right = to
                val first = selector(array[from])
                val middle = selector(array[(from + to) ushr 1])
                val last = selector(array[to])
                val pivot = if (first < middle) {
                    if (middle < last) middle else if (first < last) last else first
                } else {
                    if (first < last) first else if (middle < last) last else middle
                }

                while (left <= right) {
                    while (selector(array[left]) < pivot) left++
                    while (selector(array[right]) > pivot) right--
                    if (left <= right) {
                        val value = array[left]
                        array[left++] = array[right]
                        array[right--] = value
                    }
                }

                if (right - from < to - left) {
                    if (left < to) stack[stackSize++] = (left.toLong() shl 32) or (to.toLong() and 0xffffffffL)
                    to = right
                } else {
                    if (from < right) stack[stackSize++] = (from.toLong() shl 32) or (right.toLong() and 0xffffffffL)
                    from = left
                }
            }
        }
    }

    inline fun sortByDouble(crossinline selector: (Double) -> Double) {
        if (size < 2) return
        val stack = __sortStack ?: LongArray(64).also { __sortStack = it }
        var stackSize = 0
        stack[stackSize++] = (size - 1).toLong() and 0xffffffffL

        while (stackSize > 0) {
            val range = stack[--stackSize]
            var from = (range ushr 32).toInt()
            var to = range.toInt()

            while (from < to) {
                var left = from
                var right = to
                val first = selector(array[from])
                val middle = selector(array[(from + to) ushr 1])
                val last = selector(array[to])
                val pivot = if (first < middle) {
                    if (middle < last) middle else if (first < last) last else first
                } else {
                    if (first < last) first else if (middle < last) last else middle
                }

                while (left <= right) {
                    while (selector(array[left]) < pivot) left++
                    while (selector(array[right]) > pivot) right--
                    if (left <= right) {
                        val value = array[left]
                        array[left++] = array[right]
                        array[right--] = value
                    }
                }

                if (right - from < to - left) {
                    if (left < to) stack[stackSize++] = (left.toLong() shl 32) or (to.toLong() and 0xffffffffL)
                    to = right
                } else {
                    if (from < right) stack[stackSize++] = (from.toLong() shl 32) or (right.toLong() and 0xffffffffL)
                    from = left
                }
            }
        }
    }

    fun sortWith(comparator: (Double, Double) -> Int) {

        fun quicksort(from: Int, to: Int) {
            if (from >= to) return

            val pivot = this[(from + to) ushr 1]

            var i = from
            var j = to

            while (i <= j) {

                while (comparator(this[i], pivot) < 0) i++

                while (comparator(this[j], pivot) > 0) j--

                if (i <= j) {
                    val tmp = this[i]
                    this[i] = this[j]
                    this[j] = tmp
                    i++
                    j--
                }
            }

            if (from < j) quicksort(from, j)
            if (i < to) quicksort(i, to)
        }

        if (size > 1) {
            quicksort(0, size - 1)
        }
    }

    inline fun sortBy(crossinline selector: (Double) -> Int) {
        sortWith { a, b ->
            selector(a).compareTo(selector(b))
        }
    }

    fun sortedWith(comparator: (Double, Double) -> Int): DoubleList =
        clone().apply {
            sortWith(comparator)
        }

    inline fun sortedBy(crossinline selector: (Double) -> Int): DoubleList =
        clone().apply {
            sortBy(selector)
        }

    inline fun shuffle(random: Random = Random) {
        for (i in lastIndex downTo 1) {
            val j = random.nextInt(i + 1)

            val tmp = array[i]
            array[i] = array[j]
            array[j] = tmp
        }
    }

    inline fun shuffled(random: Random = Random): DoubleList =
        clone().apply {
            shuffle(random)
        }

    inline fun fill(value: Double) {
        for (i in 0 until size) {
            array[i] = value
        }
    }

    inline fun addFrom(source: DoubleList, index: Int) {
        ensureCapacity(index + source.size)
        source.array.copyInto(
            destination = array,
            destinationOffset = index,
            startIndex = 0,
            endIndex = source.size,
        )
        size += source.size
    }
}

inline fun DoubleList.encode(i: Int, buffer: NativeBuffer) = buffer.pushDouble(array[i])
inline fun DoubleList.encodeGpu(i: Int, buffer: NativeBuffer) = buffer.pushDouble(array[i])
inline fun DoubleList.encodePacked(i: Int, buffer: NativeBuffer) = buffer.pushDouble(array[i])

inline fun DoubleList.decode(i: Int, buffer: NativeBuffer) { array[i] = buffer.nextDouble() }
inline fun DoubleList.decodeGpu(i: Int, buffer: NativeBuffer) { array[i] = buffer.nextDouble() }
inline fun DoubleList.decodePacked(i: Int, buffer: NativeBuffer) { array[i] = buffer.nextDouble() }
