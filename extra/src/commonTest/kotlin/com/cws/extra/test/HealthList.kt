package com.cws.extra.test

import com.cws.extra.lists.FloatList
import com.cws.extra.memory.ExtraDataSoA
import com.cws.extra.memory.IExtraList
import kotlin.random.Random
import kotlinx.serialization.Serializable

fun HealthList(capacity: Int) = HealthList(
   current = FloatList(capacity),
   maximum = FloatList(capacity),
)

@ExtraDataSoA
data class HealthList(
       val current: FloatList,
   val maximum: FloatList,
): IExtraList {

    val capacity: Int get() = current.capacity

    val size: Int get() = current.size

    val isEmpty: Boolean
        get() = size == 0

    val isNotEmpty: Boolean
        get() = size != 0

    val indices: IntRange
        get() = 0 until size

    val lastIndex: Int
        get() = size - 1

    fun clear() {
       current.clear()
   maximum.clear()
    }

    operator fun set(i: Int, value: Health) {
       current[i] = value.current
   maximum[i] = value.maximum
    }

    fun add(value: Health) {
       current.add(value.current)
   maximum.add(value.maximum)
    }

    fun addAll(values: HealthList) {
       current.addAll(values.current)
   maximum.addAll(values.maximum)
    }

   fun addFrom(
            source: HealthList,
            index: Int
        ) {
               current.addFrom(source.current, index)
   maximum.addFrom(source.maximum, index)
        }

    fun push(value: Health) = add(value)


    fun trimToSize() {
           current.trimToSize()
   maximum.trimToSize()
    }

    fun reserve(capacity: Int) {
           current.reserve(capacity)
   maximum.reserve(capacity)
    }

    fun resize(newSize: Int) {
           current.resize(newSize)
   maximum.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           current.ensureCapacity(newCapacity)
   maximum.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           current.removeAtSwap(index)
   maximum.removeAtSwap(index)
    }

    fun clone(): HealthList {
        val copy = HealthList(   current.clone(),
   maximum.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           current.shuffle(random)
   maximum.shuffle(random)
    }

   inline fun forEach(block: HealthList.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: HealthList.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: HealthList.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: HealthList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: HealthList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: HealthList.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: HealthList.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: HealthList,
        predicate: HealthList.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}