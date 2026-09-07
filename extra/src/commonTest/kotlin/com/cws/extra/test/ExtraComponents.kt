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

import com.cws.extra.ecs.ComponentRegistry
import com.cws.extra.ecs.validatePercentage
import kotlin.math.roundToInt

import com.cws.extra.test.*

object ExtraComponents {

    fun registerAll() {
        ComponentRegistry.register<Movement>("com.cws.extra.test.Movement", validatePercentage(1.0f)) {
             MovementStorage((it.toFloat() * validatePercentage(1.0f)).roundToInt())
        }
        ComponentRegistry.register<Camera>("com.cws.extra.test.Camera", validatePercentage(0.2f)) {
             CameraStorage((it.toFloat() * validatePercentage(0.2f)).roundToInt())
        }
        ComponentRegistry.register<Velocity>("com.cws.extra.test.Velocity", validatePercentage(1.0f)) {
             VelocityStorage((it.toFloat() * validatePercentage(1.0f)).roundToInt())
        }
        ComponentRegistry.register<Renderable>("com.cws.extra.test.Renderable", validatePercentage(0.2f)) {
             RenderableStorage((it.toFloat() * validatePercentage(0.2f)).roundToInt())
        }
        ComponentRegistry.register<Health>("com.cws.extra.test.Health", validatePercentage(0.8f)) {
             HealthStorage((it.toFloat() * validatePercentage(0.8f)).roundToInt())
        }
        ComponentRegistry.register<Damage>("com.cws.extra.test.Damage", validatePercentage(0.35f)) {
             DamageStorage((it.toFloat() * validatePercentage(0.35f)).roundToInt())
        }
        ComponentRegistry.register<Collision>("com.cws.extra.test.Collision", validatePercentage(0.25f)) {
             CollisionStorage((it.toFloat() * validatePercentage(0.25f)).roundToInt())
        }
    }

}
