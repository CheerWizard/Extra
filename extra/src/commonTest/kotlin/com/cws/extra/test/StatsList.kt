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

import com.cws.extra.lists.IntList
import com.cws.extra.lists.FloatList
import com.cws.extra.lists.DoubleList
import com.cws.extra.lists.ShortList
import com.cws.extra.lists.BooleanList
import com.cws.extra.memory.ExtraDataSoA
import com.cws.extra.memory.IExtraList
import kotlin.random.Random
import kotlinx.serialization.Serializable

fun StatsList(capacity: Int) = StatsList(
   health = IntList(capacity),
   mana = FloatList(capacity),
   stamina = DoubleList(capacity),
   level = ShortList(capacity),
   alive = BooleanList(capacity),
)

@ExtraDataSoA
data class StatsList(
       val health: IntList,
   val mana: FloatList,
   val stamina: DoubleList,
   val level: ShortList,
   val alive: BooleanList,
): IExtraList {

    val capacity: Int get() = health.capacity

    val size: Int get() = health.size

    val isEmpty: Boolean
        get() = size == 0

    val isNotEmpty: Boolean
        get() = size != 0

    val indices: IntRange
        get() = 0 until size

    val lastIndex: Int
        get() = size - 1

    fun clear() {
       health.clear()
   mana.clear()
   stamina.clear()
   level.clear()
   alive.clear()
    }

    operator fun set(i: Int, value: Stats) {
       health[i] = value.health
   mana[i] = value.mana
   stamina[i] = value.stamina
   level[i] = value.level
   alive[i] = value.alive
    }

    fun add(value: Stats) {
       health.add(value.health)
   mana.add(value.mana)
   stamina.add(value.stamina)
   level.add(value.level)
   alive.add(value.alive)
    }

    fun addAll(values: StatsList) {
       health.addAll(values.health)
   mana.addAll(values.mana)
   stamina.addAll(values.stamina)
   level.addAll(values.level)
   alive.addAll(values.alive)
    }

   fun addFrom(
            source: StatsList,
            index: Int
        ) {
               health.addFrom(source.health, index)
   mana.addFrom(source.mana, index)
   stamina.addFrom(source.stamina, index)
   level.addFrom(source.level, index)
   alive.addFrom(source.alive, index)
        }

    fun push(value: Stats) = add(value)


    fun trimToSize() {
           health.trimToSize()
   mana.trimToSize()
   stamina.trimToSize()
   level.trimToSize()
   alive.trimToSize()
    }

    fun reserve(capacity: Int) {
           health.reserve(capacity)
   mana.reserve(capacity)
   stamina.reserve(capacity)
   level.reserve(capacity)
   alive.reserve(capacity)
    }

    fun resize(newSize: Int) {
           health.resize(newSize)
   mana.resize(newSize)
   stamina.resize(newSize)
   level.resize(newSize)
   alive.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           health.ensureCapacity(newCapacity)
   mana.ensureCapacity(newCapacity)
   stamina.ensureCapacity(newCapacity)
   level.ensureCapacity(newCapacity)
   alive.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           health.removeAtSwap(index)
   mana.removeAtSwap(index)
   stamina.removeAtSwap(index)
   level.removeAtSwap(index)
   alive.removeAtSwap(index)
    }

    fun clone(): StatsList {
        val copy = StatsList(   health.clone(),
   mana.clone(),
   stamina.clone(),
   level.clone(),
   alive.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           health.shuffle(random)
   mana.shuffle(random)
   stamina.shuffle(random)
   level.shuffle(random)
   alive.shuffle(random)
    }

   inline fun forEach(block: StatsList.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: StatsList.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: StatsList.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: StatsList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: StatsList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: StatsList.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: StatsList.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: StatsList,
        predicate: StatsList.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}