package com.cws.extra.test

import com.cws.extra.lists.FloatList
import com.cws.extra.memory.ExtraDataSoA
import com.cws.extra.memory.IExtraList
import kotlin.random.Random
import kotlinx.serialization.Serializable

fun CollisionList(capacity: Int) = CollisionList(
   impulse = FloatList(capacity),
   damageScale = FloatList(capacity),
)

@ExtraDataSoA
data class CollisionList(
       val impulse: FloatList,
   val damageScale: FloatList,
): IExtraList {

    val capacity: Int get() = impulse.capacity

    val size: Int get() = impulse.size

    val isEmpty: Boolean
        get() = size == 0

    val isNotEmpty: Boolean
        get() = size != 0

    val indices: IntRange
        get() = 0 until size

    val lastIndex: Int
        get() = size - 1

    fun clear() {
       impulse.clear()
   damageScale.clear()
    }

    operator fun set(i: Int, value: Collision) {
       impulse[i] = value.impulse
   damageScale[i] = value.damageScale
    }

    fun add(value: Collision) {
       impulse.add(value.impulse)
   damageScale.add(value.damageScale)
    }

    fun addAll(values: CollisionList) {
       impulse.addAll(values.impulse)
   damageScale.addAll(values.damageScale)
    }

   fun addFrom(
            source: CollisionList,
            index: Int
        ) {
               impulse.addFrom(source.impulse, index)
   damageScale.addFrom(source.damageScale, index)
        }

    fun push(value: Collision) = add(value)


    fun trimToSize() {
           impulse.trimToSize()
   damageScale.trimToSize()
    }

    fun reserve(capacity: Int) {
           impulse.reserve(capacity)
   damageScale.reserve(capacity)
    }

    fun resize(newSize: Int) {
           impulse.resize(newSize)
   damageScale.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           impulse.ensureCapacity(newCapacity)
   damageScale.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           impulse.removeAtSwap(index)
   damageScale.removeAtSwap(index)
    }

    fun clone(): CollisionList {
        val copy = CollisionList(   impulse.clone(),
   damageScale.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           impulse.shuffle(random)
   damageScale.shuffle(random)
    }

   inline fun forEach(block: CollisionList.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: CollisionList.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: CollisionList.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: CollisionList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: CollisionList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: CollisionList.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: CollisionList.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: CollisionList,
        predicate: CollisionList.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}