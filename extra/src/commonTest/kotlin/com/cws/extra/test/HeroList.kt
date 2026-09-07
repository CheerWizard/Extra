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
import com.cws.extra.lists.LongList
import com.cws.extra.lists.FloatList
import com.cws.extra.lists.DoubleList
import com.cws.extra.lists.ShortList
import com.cws.extra.lists.ByteList
import com.cws.extra.lists.BooleanList
import com.cws.extra.lists.CharList
import com.cws.extra.lists.GenericList
import com.cws.extra.test.TransformList
import com.cws.extra.test.StatsList
import com.cws.extra.memory.ExtraDataSoA
import com.cws.extra.memory.IExtraList
import kotlin.random.Random
import kotlinx.serialization.Serializable

fun HeroList(capacity: Int) = HeroList(
   id = IntList(capacity),
   experience = LongList(capacity),
   speed = FloatList(capacity),
   weight = DoubleList(capacity),
   level = ShortList(capacity),
   prestige = ByteList(capacity),
   enabled = BooleanList(capacity),
   symbol = CharList(capacity),
   name = GenericList<String?>(capacity),
   tag = GenericList<String?>(capacity),
   heroClass = GenericList<HeroClass?>(capacity),
   transform = TransformList(capacity),
   stats = StatsList(capacity),
   nickname = GenericList<String?>(capacity),
)

@ExtraDataSoA
data class HeroList(
       val id: IntList,
   val experience: LongList,
   val speed: FloatList,
   val weight: DoubleList,
   val level: ShortList,
   val prestige: ByteList,
   val enabled: BooleanList,
   val symbol: CharList,
   val name: GenericList<String?>,
   val tag: GenericList<String?>,
   val heroClass: GenericList<HeroClass?>,
   val transform: TransformList,
   val stats: StatsList,
   val nickname: GenericList<String?>,
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
   experience.clear()
   speed.clear()
   weight.clear()
   level.clear()
   prestige.clear()
   enabled.clear()
   symbol.clear()
   name.clear()
   tag.clear()
   heroClass.clear()
   transform.clear()
   stats.clear()
   nickname.clear()
    }

    operator fun set(i: Int, value: Hero) {
       id[i] = value.id
   experience[i] = value.experience
   speed[i] = value.speed
   weight[i] = value.weight
   level[i] = value.level
   prestige[i] = value.prestige
   enabled[i] = value.enabled
   symbol[i] = value.symbol
   name[i] = value.name
   tag[i] = value.tag
   heroClass[i] = value.heroClass
   transform[i] = value.transform
   stats[i] = value.stats
   nickname[i] = value.nickname
    }

    fun add(value: Hero) {
       id.add(value.id)
   experience.add(value.experience)
   speed.add(value.speed)
   weight.add(value.weight)
   level.add(value.level)
   prestige.add(value.prestige)
   enabled.add(value.enabled)
   symbol.add(value.symbol)
   name.add(value.name)
   tag.add(value.tag)
   heroClass.add(value.heroClass)
   transform.add(value.transform)
   stats.add(value.stats)
   nickname.add(value.nickname)
    }

    fun addAll(values: HeroList) {
       id.addAll(values.id)
   experience.addAll(values.experience)
   speed.addAll(values.speed)
   weight.addAll(values.weight)
   level.addAll(values.level)
   prestige.addAll(values.prestige)
   enabled.addAll(values.enabled)
   symbol.addAll(values.symbol)
   name.addAll(values.name)
   tag.addAll(values.tag)
   heroClass.addAll(values.heroClass)
   transform.addAll(values.transform)
   stats.addAll(values.stats)
   nickname.addAll(values.nickname)
    }

   fun addFrom(
            source: HeroList,
            index: Int
        ) {
               id.addFrom(source.id, index)
   experience.addFrom(source.experience, index)
   speed.addFrom(source.speed, index)
   weight.addFrom(source.weight, index)
   level.addFrom(source.level, index)
   prestige.addFrom(source.prestige, index)
   enabled.addFrom(source.enabled, index)
   symbol.addFrom(source.symbol, index)
   name.addFrom(source.name, index)
   tag.addFrom(source.tag, index)
   heroClass.addFrom(source.heroClass, index)
   transform.addFrom(source.transform, index)
   stats.addFrom(source.stats, index)
   nickname.addFrom(source.nickname, index)
        }

    fun push(value: Hero) = add(value)


    fun trimToSize() {
           id.trimToSize()
   experience.trimToSize()
   speed.trimToSize()
   weight.trimToSize()
   level.trimToSize()
   prestige.trimToSize()
   enabled.trimToSize()
   symbol.trimToSize()
   name.trimToSize()
   tag.trimToSize()
   heroClass.trimToSize()
   transform.trimToSize()
   stats.trimToSize()
   nickname.trimToSize()
    }

    fun reserve(capacity: Int) {
           id.reserve(capacity)
   experience.reserve(capacity)
   speed.reserve(capacity)
   weight.reserve(capacity)
   level.reserve(capacity)
   prestige.reserve(capacity)
   enabled.reserve(capacity)
   symbol.reserve(capacity)
   name.reserve(capacity)
   tag.reserve(capacity)
   heroClass.reserve(capacity)
   transform.reserve(capacity)
   stats.reserve(capacity)
   nickname.reserve(capacity)
    }

    fun resize(newSize: Int) {
           id.resize(newSize)
   experience.resize(newSize)
   speed.resize(newSize)
   weight.resize(newSize)
   level.resize(newSize)
   prestige.resize(newSize)
   enabled.resize(newSize)
   symbol.resize(newSize)
   name.resize(newSize)
   tag.resize(newSize)
   heroClass.resize(newSize)
   transform.resize(newSize)
   stats.resize(newSize)
   nickname.resize(newSize)
    }

    fun ensureCapacity(newCapacity: Int) {
           id.ensureCapacity(newCapacity)
   experience.ensureCapacity(newCapacity)
   speed.ensureCapacity(newCapacity)
   weight.ensureCapacity(newCapacity)
   level.ensureCapacity(newCapacity)
   prestige.ensureCapacity(newCapacity)
   enabled.ensureCapacity(newCapacity)
   symbol.ensureCapacity(newCapacity)
   name.ensureCapacity(newCapacity)
   tag.ensureCapacity(newCapacity)
   heroClass.ensureCapacity(newCapacity)
   transform.ensureCapacity(newCapacity)
   stats.ensureCapacity(newCapacity)
   nickname.ensureCapacity(newCapacity)
    }

    fun removeAtSwap(index: Int) {
           id.removeAtSwap(index)
   experience.removeAtSwap(index)
   speed.removeAtSwap(index)
   weight.removeAtSwap(index)
   level.removeAtSwap(index)
   prestige.removeAtSwap(index)
   enabled.removeAtSwap(index)
   symbol.removeAtSwap(index)
   name.removeAtSwap(index)
   tag.removeAtSwap(index)
   heroClass.removeAtSwap(index)
   transform.removeAtSwap(index)
   stats.removeAtSwap(index)
   nickname.removeAtSwap(index)
    }

    fun clone(): HeroList {
        val copy = HeroList(   id.clone(),
   experience.clone(),
   speed.clone(),
   weight.clone(),
   level.clone(),
   prestige.clone(),
   enabled.clone(),
   symbol.clone(),
   name.clone(),
   tag.clone(),
   heroClass.clone(),
   transform.clone(),
   stats.clone(),
   nickname.clone())
        return copy
    }

    fun shuffle(random: Random = Random) {
           id.shuffle(random)
   experience.shuffle(random)
   speed.shuffle(random)
   weight.shuffle(random)
   level.shuffle(random)
   prestige.shuffle(random)
   enabled.shuffle(random)
   symbol.shuffle(random)
   name.shuffle(random)
   tag.shuffle(random)
   heroClass.shuffle(random)
   transform.shuffle(random)
   stats.shuffle(random)
   nickname.shuffle(random)
    }

   inline fun forEach(block: HeroList.(index: Int) -> Unit) {
        for (i in 0 until size) {
            block(i)
        }
    }

   inline fun find(block: HeroList.(index: Int) -> Boolean): Int {
        for (i in 0 until size) {
            if (block(i)) {
                return i
            }
        }
        return -1
    }

   inline fun any(block: HeroList.(index: Int) -> Boolean): Boolean {
        for (i in 0 until size) {
            if (block(i)) {
                return true
            }
        }
        return false
    }

   inline fun all(block: HeroList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == size
    }

   inline fun none(block: HeroList.(index: Int) -> Boolean): Boolean {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found == 0
    }

   inline fun count(block: HeroList.(index: Int) -> Boolean): Int {
        var found = 0
        for (i in 0 until size) {
            if (block(i)) found++
        }
        return found
    }

   inline fun removeIf(block: HeroList.(index: Int) -> Boolean) {
        for (i in 0 until size) {
            if (block(i)) {
                removeAtSwap(i)
            }
        }
    }

   inline fun copyTo(
        destination: HeroList,
        predicate: HeroList.(Int) -> Boolean
    ) {
        for (i in indices) {
            if (predicate(i)) {
                destination.addFrom(this, i)
            }
        }
    }
}