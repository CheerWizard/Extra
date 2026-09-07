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
package com.cws.extra.math.matrices

import com.cws.extra.lists.FloatList
import com.cws.extra.memory.ExtraDataSoA
import com.cws.extra.memory.IExtraList
import kotlin.random.Random
import kotlinx.serialization.Serializable

fun Mat4List(capacity: Int) = Mat4List(
   m00 = FloatList(capacity),
   m01 = FloatList(capacity),
   m02 = FloatList(capacity),
   m03 = FloatList(capacity),
   m10 = FloatList(capacity),
   m11 = FloatList(capacity),
   m12 = FloatList(capacity),
   m13 = FloatList(capacity),
   m20 = FloatList(capacity),
   m21 = FloatList(capacity),
   m22 = FloatList(capacity),
   m23 = FloatList(capacity),
   m30 = FloatList(capacity),
   m31 = FloatList(capacity),
   m32 = FloatList(capacity),
   m33 = FloatList(capacity),
)

@ExtraDataSoA
data class Mat4List(
       val m00: FloatList,
   val m01: FloatList,
   val m02: FloatList,
   val m03: FloatList,
   val m10: FloatList,
   val m11: FloatList,
   val m12: FloatList,
   val m13: FloatList,
   val m20: FloatList,
   val m21: FloatList,
   val m22: FloatList,
   val m23: FloatList,
   val m30: FloatList,
   val m31: FloatList,
   val m32: FloatList,
   val m33: FloatList,
): IExtraList {

    val capacity: Int get() = m00.capacity

    val size: Int get() = m00.size

    val isEmpty: Boolean
        get() = size == 0

    val isNotEmpty: Boolean
        get() = size != 0

    val indices: IntRange
        get() = 0 until size

    val lastIndex: Int
        get() = size - 1

    fun clear() {
       m00.clear()
   m01.clear()
   m02.clear()
   m03.clear()
   m10.clear()
   m11.clear()
   m12.clear()
   m13.clear()
   m20.clear()
   m21.clear()
   m22.clear()
   m23.clear()
   m30.clear()
   m31.clear()
   m32.clear()
   m33.clear()
    }

    operator fun set(i: Int, value: Mat4) {
       m00[i] = value.m00
   m01[i] = value.m01
   m02[i] = value.m02
   m03[i] = value.m03
   m10[i] = value.m10
   m11[i] = value.m11
   m12[i] = value.m12
   m13[i] = value.m13
   m20[i] = value.m20
   m21[i] = value.m21
   m22[i] = value.m22
   m23[i] = value.m23
   m30[i] = value.m30
   m31[i] = value.m31
   m32[i] = value.m32
   m33[i] = value.m33
    }

    fun add(value: Mat4) {
       m00.add(value.m00)
   m01.add(value.m01)
   m02.add(value.m02)
   m03.add(value.m03)
   m10.add(value.m10)
   m11.add(value.m11)
   m12.add(value.m12)
   m13.add(value.m13)
   m20.add(value.m20)
   m21.add(value.m21)
   m22.add(value.m22)
   m23.add(value.m23)
   m30.add(value.m30)
   m31.add(value.m31)
   m32.add(value.m32)
   m33.add(value.m33)
    }

    fun addAll(values: Mat4List) {
       m00.addAll(values.m00)
   m01.addAll(values.m01)
   m02.addAll(values.m02)
   m03.addAll(values.m03)
   m10.addAll(values.m10)
   m11.addAll(values.m11)
   m12.addAll(values.m12)
   m13.addAll(values.m13)
   m20.addAll(values.m20)
   m21.addAll(values.m21)
   m22.addAll(values.m22)
   m23.addAll(values.m23)
   m30.addAll(values.m30)
   m31.addAll(values.m31)
   m32.addAll(values.m32)
   m33.addAll(values.m33)
    }

   fun addFrom(
            source: Mat4List,
            index: Int
        ) {
               m00.addFrom(source.m00, index)
   m01.addFrom(source.m01, index)
   m02.addFrom(source.m02, index)
   m03.addFrom(source.m03, index)
   m10.addFrom(source.m10, index)
   m11.addFrom(source.m11, index)
   m12.addFrom(source.m12, index)
   m13.addFrom(source.m13, index)
   m20.addFrom(source.m20, index)
   m21.addFrom(source.m21, index)
   m22.addFrom(source.m22, index)
   m23.addFrom(source.m23, index)
   m30.addFrom(source.m30, index)
   m31.addFrom(source.m31, index)
   m32.addFrom(source.m32, index)
   m33.addFrom(source.m33, index)
        }

    fun push(value: Mat4) = add(value)


    fun trimToSize() {
           m00.trimToSize()
   m01.trimToSize()
   m02.trimToSize()
   m03.trimToSize()
   m10.trimToSize()
   m11.trimToSize()
   m12.trimToSize()
   m13.trimToSize()
   m20.trimToSize()
   m21.trimToSize()
   m22.trimToSize()
   m23.trimToSize()
   m30.trimToSize()
   m31.trimToSize()
   m32.trimToSize()
   m33.trimToSize()
    }

    fun reserve(capacity: Int) {
           m00.reserve(capacity)
   m01.reserve(capacity)
   m02.reserve(capacity)
   m03.reserve(capacity)
   m10.reserve(capacity)
   m11.reserve(capacity)
   m12.reserve(capacity)
   m13.reserve(capacity)
   m20.reserve(capacity)
   m21.reserve(capacity)
   m22.reserve(capacity)
   m23.reserve(capacity)
   m30.reserve(capacity)
   m31.reserve(capacity)
   m32.reserve(capacity)
   m33.reserve(capacity)
    }

    fun resize(newSize: Int) {
           m00.resize(newSize)
   m01.resize(newSize)
   m02.resize(newSize)
   m03.resize(newSize)
   m10.resize(newSize)
   m11.resize(newSize)
   m12.resize(newSize)
   m13.resize(newSize)
   m20.resize(newSize)
   m21.resize(newSize)
   m22.resize(newSize)
   m23.resize(newSize)
   m30.resize(newSize)
   m31.resize(newSize)
   m32.resize(newSize)
   m33.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           m00.ensureCapacity(newCapacity)
   m01.ensureCapacity(newCapacity)
   m02.ensureCapacity(newCapacity)
   m03.ensureCapacity(newCapacity)
   m10.ensureCapacity(newCapacity)
   m11.ensureCapacity(newCapacity)
   m12.ensureCapacity(newCapacity)
   m13.ensureCapacity(newCapacity)
   m20.ensureCapacity(newCapacity)
   m21.ensureCapacity(newCapacity)
   m22.ensureCapacity(newCapacity)
   m23.ensureCapacity(newCapacity)
   m30.ensureCapacity(newCapacity)
   m31.ensureCapacity(newCapacity)
   m32.ensureCapacity(newCapacity)
   m33.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           m00.removeAtSwap(index)
   m01.removeAtSwap(index)
   m02.removeAtSwap(index)
   m03.removeAtSwap(index)
   m10.removeAtSwap(index)
   m11.removeAtSwap(index)
   m12.removeAtSwap(index)
   m13.removeAtSwap(index)
   m20.removeAtSwap(index)
   m21.removeAtSwap(index)
   m22.removeAtSwap(index)
   m23.removeAtSwap(index)
   m30.removeAtSwap(index)
   m31.removeAtSwap(index)
   m32.removeAtSwap(index)
   m33.removeAtSwap(index)
    }

    fun clone(): Mat4List {
        val copy = Mat4List(   m00.clone(),
   m01.clone(),
   m02.clone(),
   m03.clone(),
   m10.clone(),
   m11.clone(),
   m12.clone(),
   m13.clone(),
   m20.clone(),
   m21.clone(),
   m22.clone(),
   m23.clone(),
   m30.clone(),
   m31.clone(),
   m32.clone(),
   m33.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           m00.shuffle(random)
   m01.shuffle(random)
   m02.shuffle(random)
   m03.shuffle(random)
   m10.shuffle(random)
   m11.shuffle(random)
   m12.shuffle(random)
   m13.shuffle(random)
   m20.shuffle(random)
   m21.shuffle(random)
   m22.shuffle(random)
   m23.shuffle(random)
   m30.shuffle(random)
   m31.shuffle(random)
   m32.shuffle(random)
   m33.shuffle(random)
    }

   inline fun forEach(block: Mat4List.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: Mat4List.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: Mat4List.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: Mat4List.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: Mat4List.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: Mat4List.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: Mat4List.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: Mat4List,
        predicate: Mat4List.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}