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
package com.cws.extra.ecs

import com.cws.extra.test.Collision
import com.cws.extra.test.CollisionList
import com.cws.extra.test.Damage
import com.cws.extra.test.DamageList
import com.cws.extra.test.ExtraComponents
import com.cws.extra.test.Health
import com.cws.extra.test.HealthList
import kotlin.math.max
import kotlin.test.BeforeTest
import kotlin.test.Test
import kotlin.test.assertEquals

class GameSystemQueryTest {

    private lateinit var scene: Scene

    @BeforeTest
    fun setup() {
        ExtraComponents.registerAll()
        scene = Scene(entityCount = 64)
    }

    @Test
    fun `damage collision system updates only entities having all three components`() {
        val hit = scene.create(
            Health(current = 100f, maximum = 100f),
            Damage(amount = 20f, armorPenetration = 0.25f),
            Collision(impulse = 2f, damageScale = 1.5f),
        )
        val lethalHit = scene.create(
            Health(current = 15f, maximum = 100f),
            Damage(amount = 50f, armorPenetration = 0f),
            Collision(impulse = 1f, damageScale = 1f),
        )
        val noCollision = scene.create(
            Health(current = 80f, maximum = 100f),
            Damage(amount = 30f, armorPenetration = 0.5f),
        )
        scene.create(Damage(amount = 999f, armorPenetration = 1f), Collision(10f, 10f))

        runDamageSystem(scene)

        assertEquals(25f, healthOf(hit))
        assertEquals(0f, healthOf(lethalHit))
        assertEquals(80f, healthOf(noCollision))
    }

    @Test
    fun `materialized combat query can be reused across frames and refreshes after changes`() {
        val first = scene.create(Health(100f, 100f), Damage(10f, 0f), Collision(1f, 1f))
        val query = combatQuery(scene).also { it.ensureIndices() }

        runDamageSystem(query)
        assertEquals(90f, healthOf(first))

        val second = scene.create(Health(50f, 50f), Damage(5f, 0f), Collision(2f, 2f))
        scene.remove<Damage>(first)
        runDamageSystem(query)

        assertEquals(90f, healthOf(first))
        assertEquals(30f, healthOf(second))
        assertEquals(1, query.count())
    }

    @Test
    fun `collision threshold processes gameplay events without materializing a query`() {
        scene.create(Health(100f, 100f), Damage(10f, 0f), Collision(0.25f, 1f))
        val strong = scene.create(Health(100f, 100f), Damage(10f, 0f), Collision(3f, 1f))

        combatQuery(scene).forEachWhere(
            predicate = { _, _, _, _, _, collisions, ci -> collisions.impulse[ci] >= 1f },
            block = { _, health, hi, damage, di, collision, ci ->
                health.current[hi] -= damage.amount[di] * collision.impulse[ci]
            },
        )

        assertEquals(100f, healthOf(0))
        assertEquals(70f, healthOf(strong))
    }

    private fun healthOf(entity: Int): Float {
        var value = Float.NaN
        scene.query<Health, HealthList>().forEachWhere(
            predicate = { currentEntity, _, _ -> currentEntity == entity },
            block = { _, health, index -> value = health.current[index] },
        )
        return value
    }

    private fun combatQuery(scene: Scene) =
        scene.query<Health, HealthList, Damage, DamageList, Collision, CollisionList>()

    private fun runDamageSystem(scene: Scene) = runDamageSystem(combatQuery(scene))

    private fun runDamageSystem(
        query: Query3<Health, HealthList, Damage, DamageList, Collision, CollisionList>,
    ) {
        query.forEach { _, health, hi, damage, di, collision, ci ->
            val hitDamage = damage.amount[di] * (1f + damage.armorPenetration[di]) *
                collision.impulse[ci] * collision.damageScale[ci]
            health.current[hi] = max(0f, health.current[hi] - hitDamage)
        }
    }
}
