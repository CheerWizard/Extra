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
import kotlin.math.sqrt

fun refract(
    i: Float2,
    n: Float2,
    eta: Float,
): Float2 {
    val d = dot(n, i)
    val k = 1f - eta * eta * (1f - d * d)
    return if (k < 0f) Float2(0f, 0f) else i * eta - n * (eta * d + sqrt(k))
}

fun refract(
    il: Float2List,
    ii: Int,
    nl: Float2List,
    ni: Int,
    eta: Float,
    out: Float2List,
    oi: Int,
): Float2List {
    val d = dot(nl, ni, il, ii)
    val k = 1f - eta * eta * (1f - d * d)
    if (k < 0f) {
        out.x[oi] = 0f
        out.y[oi] = 0f
    } else {
        val s = eta * d + sqrt(k)
        out.x[oi] = il.x[ii] * eta - nl.x[ni] * s
        out.y[oi] = il.y[ii] * eta - nl.y[ni] * s
    }
    return out
}

fun refract(
    i: Float3,
    n: Float3,
    eta: Float,
): Float3 {
    val d = dot(n, i)
    val k = 1f - eta * eta * (1f - d * d)
    return if (k < 0f) Float3(0f, 0f, 0f) else i * eta - n * (eta * d + sqrt(k))
}

fun refract(
    il: Float3List,
    ii: Int,
    nl: Float3List,
    ni: Int,
    eta: Float,
    out: Float3List,
    oi: Int,
): Float3List {
    val d = dot(nl, ni, il, ii)
    val k = 1f - eta * eta * (1f - d * d)
    if (k < 0f) {
        out.x[oi] = 0f
        out.y[oi] = 0f
        out.z[oi] = 0f
    } else {
        val s = eta * d + sqrt(k)
        out.x[oi] = il.x[ii] * eta - nl.x[ni] * s
        out.y[oi] = il.y[ii] * eta - nl.y[ni] * s
        out.z[oi] = il.z[ii] * eta - nl.z[ni] * s
    }
    return out
}

fun refract(
    i: Float4,
    n: Float4,
    eta: Float,
): Float4 {
    val d = dot(n, i)
    val k = 1f - eta * eta * (1f - d * d)
    return if (k < 0f) Float4(0f, 0f, 0f, 0f) else i * eta - n * (eta * d + sqrt(k))
}

fun refract(
    il: Float4List,
    ii: Int,
    nl: Float4List,
    ni: Int,
    eta: Float,
    out: Float4List,
    oi: Int,
): Float4List {
    val d = dot(nl, ni, il, ii)
    val k = 1f - eta * eta * (1f - d * d)
    if (k < 0f) {
        out.x[oi] = 0f
        out.y[oi] = 0f
        out.z[oi] = 0f
        out.w[oi] = 0f
    } else {
        val s = eta * d + sqrt(k)
        out.x[oi] = il.x[ii] * eta - nl.x[ni] * s
        out.y[oi] = il.y[ii] * eta - nl.y[ni] * s
        out.z[oi] = il.z[ii] * eta - nl.z[ni] * s
        out.w[oi] = il.w[ii] * eta - nl.w[ni] * s
    }
    return out
}
