package com.cws.extra.test

import com.cws.extra.lists.FloatList
import com.cws.extra.memory.ExtraDataSoA
import com.cws.extra.memory.IExtraList
import kotlin.random.Random
import kotlinx.serialization.Serializable

fun MovementList(capacity: Int) = MovementList(
   speed = FloatList(capacity),
)

@ExtraDataSoA
data class MovementList(
       val speed: FloatList,
): IExtraList {

    val capacity: Int get() = speed.capacity

    val size: Int get() = speed.size

    val isEmpty: Boolean
        get() = size == 0

    val isNotEmpty: Boolean
        get() = size != 0

    val indices: IntRange
        get() = 0 until size

    val lastIndex: Int
        get() = size - 1

    fun clear() {
       speed.clear()
    }

    operator fun set(i: Int, value: Movement) {
       speed[i] = value.speed
    }

    fun add(value: Movement) {
       speed.add(value.speed)
    }

    fun addAll(values: MovementList) {
       speed.addAll(values.speed)
    }

   fun addFrom(
            source: MovementList,
            index: Int
        ) {
               speed.addFrom(source.speed, index)
        }

    fun push(value: Movement) = add(value)


    fun trimToSize() {
           speed.trimToSize()
    }

    fun reserve(capacity: Int) {
           speed.reserve(capacity)
    }

    fun resize(newSize: Int) {
           speed.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           speed.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           speed.removeAtSwap(index)
    }

    fun clone(): MovementList {
        val copy = MovementList(   speed.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           speed.shuffle(random)
    }

   inline fun forEach(block: MovementList.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: MovementList.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: MovementList.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: MovementList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: MovementList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: MovementList.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: MovementList.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: MovementList,
        predicate: MovementList.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}