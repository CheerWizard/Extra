package com.cws.extra.test

import com.cws.extra.lists.IntList
import com.cws.extra.memory.ExtraDataSoA
import com.cws.extra.memory.IExtraList
import kotlin.random.Random
import kotlinx.serialization.Serializable

fun InventoryItemList(capacity: Int) = InventoryItemList(
   id = IntList(capacity),
   amount = IntList(capacity),
)

@ExtraDataSoA
data class InventoryItemList(
       val id: IntList,
   val amount: IntList,
): IExtraList {

    val capacity: Int get() = id.capacity

    val size: Int get() = id.size

    val isEmpty: Boolean
        get() = size == 0

    val isNotEmpty: Boolean
        get() = size != 0

    val indices: IntRange
        get() = 0 until size

    val lastIndex: Int
        get() = size - 1

    fun clear() {
       id.clear()
   amount.clear()
    }

    operator fun set(i: Int, value: InventoryItem) {
       id[i] = value.id
   amount[i] = value.amount
    }

    fun add(value: InventoryItem) {
       id.add(value.id)
   amount.add(value.amount)
    }

    fun addAll(values: InventoryItemList) {
       id.addAll(values.id)
   amount.addAll(values.amount)
    }

   fun addFrom(
            source: InventoryItemList,
            index: Int
        ) {
               id.addFrom(source.id, index)
   amount.addFrom(source.amount, index)
        }

    fun push(value: InventoryItem) = add(value)


    fun trimToSize() {
           id.trimToSize()
   amount.trimToSize()
    }

    fun reserve(capacity: Int) {
           id.reserve(capacity)
   amount.reserve(capacity)
    }

    fun resize(newSize: Int) {
           id.resize(newSize)
   amount.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           id.ensureCapacity(newCapacity)
   amount.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           id.removeAtSwap(index)
   amount.removeAtSwap(index)
    }

    fun clone(): InventoryItemList {
        val copy = InventoryItemList(   id.clone(),
   amount.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           id.shuffle(random)
   amount.shuffle(random)
    }

   inline fun forEach(block: InventoryItemList.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: InventoryItemList.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: InventoryItemList.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: InventoryItemList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: InventoryItemList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: InventoryItemList.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: InventoryItemList.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: InventoryItemList,
        predicate: InventoryItemList.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}