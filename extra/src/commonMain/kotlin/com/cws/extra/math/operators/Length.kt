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
package com.cws.extra.math.operators

import com.cws.extra.math.vectors.*
import kotlin.math.sqrt as ksqrt

fun length(v: Float2) = ksqrt(v.x * v.x + v.y * v.y)

fun length(l: Float2List, i: Int) = ksqrt(l.x[i] * l.x[i] + l.y[i] * l.y[i])

fun length(l: Int2List, i: Int) = sqrt(l.x[i] * l.x[i] + l.y[i] * l.y[i])

fun length(l: UInt2List, i: Int) = sqrt(l.x[i] * l.x[i] + l.y[i] * l.y[i])

fun length(v: Float3) = ksqrt(v.x * v.x + v.y * v.y + v.z * v.z)

fun length(l: Float3List, i: Int) = ksqrt(l.x[i] * l.x[i] + l.y[i] * l.y[i] + l.z[i] * l.z[i])

fun length(l: Int3List, i: Int) = sqrt(l.x[i] * l.x[i] + l.y[i] * l.y[i] + l.z[i] * l.z[i])

fun length(l: UInt3List, i: Int) = sqrt(l.x[i] * l.x[i] + l.y[i] * l.y[i] + l.z[i] * l.z[i])

fun length(v: Float4) = ksqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w)

fun length(l: Float4List, i: Int) = ksqrt(l.x[i] * l.x[i] + l.y[i] * l.y[i] + l.z[i] * l.z[i] + l.w[i] * l.w[i])

fun length(l: Int4List, i: Int) = sqrt(l.x[i] * l.x[i] + l.y[i] * l.y[i] + l.z[i] * l.z[i] + l.w[i] * l.w[i])

fun length(l: UInt4List, i: Int) = sqrt(l.x[i] * l.x[i] + l.y[i] * l.y[i] + l.z[i] * l.z[i] + l.w[i] * l.w[i])

fun length(l: QuaternionList, i: Int) = ksqrt(l.x[i] * l.x[i] + l.y[i] * l.y[i] + l.z[i] * l.z[i] + l.w[i] * l.w[i])

fun lengthSquared(v: Float2) = v.x * v.x + v.y * v.y

fun lengthSquared(l: Float2List, i: Int) = l.x[i] * l.x[i] + l.y[i] * l.y[i]

fun lengthSquared(v: Float3) = v.x * v.x + v.y * v.y + v.z * v.z

fun lengthSquared(l: Float3List, i: Int) = l.x[i] * l.x[i] + l.y[i] * l.y[i] + l.z[i] * l.z[i]

fun lengthSquared(v: Float4) = v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w

fun lengthSquared(l: Float4List, i: Int) = l.x[i] * l.x[i] + l.y[i] * l.y[i] + l.z[i] * l.z[i] + l.w[i] * l.w[i]

fun lengthSquared(l: QuaternionList, i: Int) = l.x[i] * l.x[i] + l.y[i] * l.y[i] + l.z[i] * l.z[i] + l.w[i] * l.w[i]
