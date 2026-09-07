package com.cws.extra.test

import com.cws.extra.lists.FloatList
import com.cws.extra.memory.ExtraDataSoA
import com.cws.extra.memory.IExtraList
import kotlin.random.Random
import kotlinx.serialization.Serializable

fun CameraList(capacity: Int) = CameraList(
   fov = FloatList(capacity),
)

@ExtraDataSoA
data class CameraList(
       val fov: FloatList,
): IExtraList {

    val capacity: Int get() = fov.capacity

    val size: Int get() = fov.size

    val isEmpty: Boolean
        get() = size == 0

    val isNotEmpty: Boolean
        get() = size != 0

    val indices: IntRange
        get() = 0 until size

    val lastIndex: Int
        get() = size - 1

    fun clear() {
       fov.clear()
    }

    operator fun set(i: Int, value: Camera) {
       fov[i] = value.fov
    }

    fun add(value: Camera) {
       fov.add(value.fov)
    }

    fun addAll(values: CameraList) {
       fov.addAll(values.fov)
    }

   fun addFrom(
            source: CameraList,
            index: Int
        ) {
               fov.addFrom(source.fov, index)
        }

    fun push(value: Camera) = add(value)


    fun trimToSize() {
           fov.trimToSize()
    }

    fun reserve(capacity: Int) {
           fov.reserve(capacity)
    }

    fun resize(newSize: Int) {
           fov.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           fov.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           fov.removeAtSwap(index)
    }

    fun clone(): CameraList {
        val copy = CameraList(   fov.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           fov.shuffle(random)
    }

   inline fun forEach(block: CameraList.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: CameraList.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: CameraList.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: CameraList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: CameraList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: CameraList.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: CameraList.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: CameraList,
        predicate: CameraList.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}