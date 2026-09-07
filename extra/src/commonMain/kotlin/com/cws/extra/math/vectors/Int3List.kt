package com.cws.extra.math.vectors

import com.cws.extra.lists.IntList
import com.cws.extra.memory.ExtraDataSoA
import com.cws.extra.memory.IExtraList
import kotlin.random.Random
import kotlinx.serialization.Serializable

fun Int3List(capacity: Int) = Int3List(
   x = IntList(capacity),
   y = IntList(capacity),
   z = IntList(capacity),
)

@ExtraDataSoA
data class Int3List(
       val x: IntList,
   val y: IntList,
   val z: IntList,
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
    }

    operator fun set(i: Int, value: Int3) {
       x[i] = value.x
   y[i] = value.y
   z[i] = value.z
    }

    fun add(value: Int3) {
       x.add(value.x)
   y.add(value.y)
   z.add(value.z)
    }

    fun addAll(values: Int3List) {
       x.addAll(values.x)
   y.addAll(values.y)
   z.addAll(values.z)
    }

   fun addFrom(
            source: Int3List,
            index: Int
        ) {
               x.addFrom(source.x, index)
   y.addFrom(source.y, index)
   z.addFrom(source.z, index)
        }

    fun push(value: Int3) = add(value)


    fun trimToSize() {
           x.trimToSize()
   y.trimToSize()
   z.trimToSize()
    }

    fun reserve(capacity: Int) {
           x.reserve(capacity)
   y.reserve(capacity)
   z.reserve(capacity)
    }

    fun resize(newSize: Int) {
           x.resize(newSize)
   y.resize(newSize)
   z.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           x.ensureCapacity(newCapacity)
   y.ensureCapacity(newCapacity)
   z.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           x.removeAtSwap(index)
   y.removeAtSwap(index)
   z.removeAtSwap(index)
    }

    fun clone(): Int3List {
        val copy = Int3List(   x.clone(),
   y.clone(),
   z.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           x.shuffle(random)
   y.shuffle(random)
   z.shuffle(random)
    }

   inline fun forEach(block: Int3List.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: Int3List.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: Int3List.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: Int3List.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: Int3List.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: Int3List.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: Int3List.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: Int3List,
        predicate: Int3List.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}