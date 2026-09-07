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

fun dot(
    v1: Float2,
    v2: Float2,
): Float = v1.x * v2.x + v1.y * v2.y

fun dot(
    l1: Float2List,
    i1: Int,
    l2: Float2List,
    i2: Int,
): Float = l1.x[i1] * l2.x[i2] + l1.y[i1] * l2.y[i2]

fun dot(
    v1: Float3,
    v2: Float3,
): Float = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z

fun dot(
    l1: Float3List,
    i1: Int,
    l2: Float3List,
    i2: Int,
): Float = l1.x[i1] * l2.x[i2] + l1.y[i1] * l2.y[i2] + l1.z[i1] * l2.z[i2]

fun dot(
    v1: Float4,
    v2: Float4,
): Float = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w

fun dot(
    l1: Float4List,
    i1: Int,
    l2: Float4List,
    i2: Int,
): Float = l1.x[i1] * l2.x[i2] + l1.y[i1] * l2.y[i2] + l1.z[i1] * l2.z[i2] + l1.w[i1] * l2.w[i2]

fun dot(
    q1: Quaternion,
    q2: Quaternion,
): Float = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w

fun dot(
    l1: QuaternionList,
    i1: Int,
    l2: QuaternionList,
    i2: Int,
): Float = l1.x[i1] * l2.x[i2] + l1.y[i1] * l2.y[i2] + l1.z[i1] * l2.z[i2] + l1.w[i1] * l2.w[i2]
