package com.cws.extra.math.matrices

import com.cws.extra.lists.FloatList
import com.cws.extra.memory.ExtraDataSoA
import com.cws.extra.memory.IExtraList
import kotlin.random.Random
import kotlinx.serialization.Serializable

fun Mat2List(capacity: Int) = Mat2List(
   m00 = FloatList(capacity),
   m01 = FloatList(capacity),
   m10 = FloatList(capacity),
   m11 = FloatList(capacity),
)

@ExtraDataSoA
data class Mat2List(
       val m00: FloatList,
   val m01: FloatList,
   val m10: FloatList,
   val m11: FloatList,
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
   m10.clear()
   m11.clear()
    }

    operator fun set(i: Int, value: Mat2) {
       m00[i] = value.m00
   m01[i] = value.m01
   m10[i] = value.m10
   m11[i] = value.m11
    }

    fun add(value: Mat2) {
       m00.add(value.m00)
   m01.add(value.m01)
   m10.add(value.m10)
   m11.add(value.m11)
    }

    fun addAll(values: Mat2List) {
       m00.addAll(values.m00)
   m01.addAll(values.m01)
   m10.addAll(values.m10)
   m11.addAll(values.m11)
    }

   fun addFrom(
            source: Mat2List,
            index: Int
        ) {
               m00.addFrom(source.m00, index)
   m01.addFrom(source.m01, index)
   m10.addFrom(source.m10, index)
   m11.addFrom(source.m11, index)
        }

    fun push(value: Mat2) = add(value)


    fun trimToSize() {
           m00.trimToSize()
   m01.trimToSize()
   m10.trimToSize()
   m11.trimToSize()
    }

    fun reserve(capacity: Int) {
           m00.reserve(capacity)
   m01.reserve(capacity)
   m10.reserve(capacity)
   m11.reserve(capacity)
    }

    fun resize(newSize: Int) {
           m00.resize(newSize)
   m01.resize(newSize)
   m10.resize(newSize)
   m11.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           m00.ensureCapacity(newCapacity)
   m01.ensureCapacity(newCapacity)
   m10.ensureCapacity(newCapacity)
   m11.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           m00.removeAtSwap(index)
   m01.removeAtSwap(index)
   m10.removeAtSwap(index)
   m11.removeAtSwap(index)
    }

    fun clone(): Mat2List {
        val copy = Mat2List(   m00.clone(),
   m01.clone(),
   m10.clone(),
   m11.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           m00.shuffle(random)
   m01.shuffle(random)
   m10.shuffle(random)
   m11.shuffle(random)
    }

   inline fun forEach(block: Mat2List.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: Mat2List.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: Mat2List.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: Mat2List.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: Mat2List.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: Mat2List.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: Mat2List.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: Mat2List,
        predicate: Mat2List.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}