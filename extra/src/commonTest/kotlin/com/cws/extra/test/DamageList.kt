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
package com.cws.extra.test

import com.cws.extra.lists.FloatList
import com.cws.extra.memory.ExtraDataSoA
import com.cws.extra.memory.IExtraList
import kotlin.random.Random
import kotlinx.serialization.Serializable

fun DamageList(capacity: Int) = DamageList(
   amount = FloatList(capacity),
   armorPenetration = FloatList(capacity),
)

@ExtraDataSoA
data class DamageList(
       val amount: FloatList,
   val armorPenetration: FloatList,
): IExtraList {

    val capacity: Int get() = amount.capacity

    val size: Int get() = amount.size

    val isEmpty: Boolean
        get() = size == 0

    val isNotEmpty: Boolean
        get() = size != 0

    val indices: IntRange
        get() = 0 until size

    val lastIndex: Int
        get() = size - 1

    fun clear() {
       amount.clear()
   armorPenetration.clear()
    }

    operator fun set(i: Int, value: Damage) {
       amount[i] = value.amount
   armorPenetration[i] = value.armorPenetration
    }

    fun add(value: Damage) {
       amount.add(value.amount)
   armorPenetration.add(value.armorPenetration)
    }

    fun addAll(values: DamageList) {
       amount.addAll(values.amount)
   armorPenetration.addAll(values.armorPenetration)
    }

   fun addFrom(
            source: DamageList,
            index: Int
        ) {
               amount.addFrom(source.amount, index)
   armorPenetration.addFrom(source.armorPenetration, index)
        }

    fun push(value: Damage) = add(value)


    fun trimToSize() {
           amount.trimToSize()
   armorPenetration.trimToSize()
    }

    fun reserve(capacity: Int) {
           amount.reserve(capacity)
   armorPenetration.reserve(capacity)
    }

    fun resize(newSize: Int) {
           amount.resize(newSize)
   armorPenetration.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           amount.ensureCapacity(newCapacity)
   armorPenetration.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           amount.removeAtSwap(index)
   armorPenetration.removeAtSwap(index)
    }

    fun clone(): DamageList {
        val copy = DamageList(   amount.clone(),
   armorPenetration.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           amount.shuffle(random)
   armorPenetration.shuffle(random)
    }

   inline fun forEach(block: DamageList.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: DamageList.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: DamageList.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: DamageList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: DamageList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: DamageList.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: DamageList.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: DamageList,
        predicate: DamageList.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}