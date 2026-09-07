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

import com.cws.extra.math.operators.clamp

const val ComponentNull = -1
const val EntityNull = -1
const val RegistrationIndexNull = -1

inline fun <reified T> ComponentId() = T::class.hashCode() and 0x7FFFFFFF // subtract negative part to use it as index in array

inline fun validatePercentage(percentage: Float): Float = clamp(0f, 1f, percentage)
