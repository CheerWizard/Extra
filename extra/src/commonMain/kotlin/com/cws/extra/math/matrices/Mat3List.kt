package com.cws.extra.math.matrices

import com.cws.extra.lists.FloatList
import com.cws.extra.memory.ExtraDataSoA
import com.cws.extra.memory.IExtraList
import kotlin.random.Random
import kotlinx.serialization.Serializable

fun Mat3List(capacity: Int) = Mat3List(
   m00 = FloatList(capacity),
   m01 = FloatList(capacity),
   m02 = FloatList(capacity),
   m10 = FloatList(capacity),
   m11 = FloatList(capacity),
   m12 = FloatList(capacity),
   m20 = FloatList(capacity),
   m21 = FloatList(capacity),
   m22 = FloatList(capacity),
)

@ExtraDataSoA
data class Mat3List(
       val m00: FloatList,
   val m01: FloatList,
   val m02: FloatList,
   val m10: FloatList,
   val m11: FloatList,
   val m12: FloatList,
   val m20: FloatList,
   val m21: FloatList,
   val m22: FloatList,
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
   m10.clear()
   m11.clear()
   m12.clear()
   m20.clear()
   m21.clear()
   m22.clear()
    }

    operator fun set(i: Int, value: Mat3) {
       m00[i] = value.m00
   m01[i] = value.m01
   m02[i] = value.m02
   m10[i] = value.m10
   m11[i] = value.m11
   m12[i] = value.m12
   m20[i] = value.m20
   m21[i] = value.m21
   m22[i] = value.m22
    }

    fun add(value: Mat3) {
       m00.add(value.m00)
   m01.add(value.m01)
   m02.add(value.m02)
   m10.add(value.m10)
   m11.add(value.m11)
   m12.add(value.m12)
   m20.add(value.m20)
   m21.add(value.m21)
   m22.add(value.m22)
    }

    fun addAll(values: Mat3List) {
       m00.addAll(values.m00)
   m01.addAll(values.m01)
   m02.addAll(values.m02)
   m10.addAll(values.m10)
   m11.addAll(values.m11)
   m12.addAll(values.m12)
   m20.addAll(values.m20)
   m21.addAll(values.m21)
   m22.addAll(values.m22)
    }

   fun addFrom(
            source: Mat3List,
            index: Int
        ) {
               m00.addFrom(source.m00, index)
   m01.addFrom(source.m01, index)
   m02.addFrom(source.m02, index)
   m10.addFrom(source.m10, index)
   m11.addFrom(source.m11, index)
   m12.addFrom(source.m12, index)
   m20.addFrom(source.m20, index)
   m21.addFrom(source.m21, index)
   m22.addFrom(source.m22, index)
        }

    fun push(value: Mat3) = add(value)


    fun trimToSize() {
           m00.trimToSize()
   m01.trimToSize()
   m02.trimToSize()
   m10.trimToSize()
   m11.trimToSize()
   m12.trimToSize()
   m20.trimToSize()
   m21.trimToSize()
   m22.trimToSize()
    }

    fun reserve(capacity: Int) {
           m00.reserve(capacity)
   m01.reserve(capacity)
   m02.reserve(capacity)
   m10.reserve(capacity)
   m11.reserve(capacity)
   m12.reserve(capacity)
   m20.reserve(capacity)
   m21.reserve(capacity)
   m22.reserve(capacity)
    }

    fun resize(newSize: Int) {
           m00.resize(newSize)
   m01.resize(newSize)
   m02.resize(newSize)
   m10.resize(newSize)
   m11.resize(newSize)
   m12.resize(newSize)
   m20.resize(newSize)
   m21.resize(newSize)
   m22.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           m00.ensureCapacity(newCapacity)
   m01.ensureCapacity(newCapacity)
   m02.ensureCapacity(newCapacity)
   m10.ensureCapacity(newCapacity)
   m11.ensureCapacity(newCapacity)
   m12.ensureCapacity(newCapacity)
   m20.ensureCapacity(newCapacity)
   m21.ensureCapacity(newCapacity)
   m22.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           m00.removeAtSwap(index)
   m01.removeAtSwap(index)
   m02.removeAtSwap(index)
   m10.removeAtSwap(index)
   m11.removeAtSwap(index)
   m12.removeAtSwap(index)
   m20.removeAtSwap(index)
   m21.removeAtSwap(index)
   m22.removeAtSwap(index)
    }

    fun clone(): Mat3List {
        val copy = Mat3List(   m00.clone(),
   m01.clone(),
   m02.clone(),
   m10.clone(),
   m11.clone(),
   m12.clone(),
   m20.clone(),
   m21.clone(),
   m22.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           m00.shuffle(random)
   m01.shuffle(random)
   m02.shuffle(random)
   m10.shuffle(random)
   m11.shuffle(random)
   m12.shuffle(random)
   m20.shuffle(random)
   m21.shuffle(random)
   m22.shuffle(random)
    }

   inline fun forEach(block: Mat3List.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: Mat3List.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: Mat3List.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: Mat3List.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: Mat3List.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: Mat3List.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: Mat3List.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: Mat3List,
        predicate: Mat3List.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}