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

fun reflect(
    i: Float2,
    n: Float2,
) = i - n * (2f * dot(n, i))

fun reflect(
    il: Float2List,
    ii: Int,
    nl: Float2List,
    ni: Int,
    out: Float2List,
    oi: Int,
): Float2List {
    val d = dot(nl, ni, il, ii)
    out.x[oi] = il.x[ii] - nl.x[ni] * (2f * d)
    out.y[oi] = il.y[ii] - nl.y[ni] * (2f * d)
    return out
}

fun reflect(
    i: Float3,
    n: Float3,
) = i - n * (2f * dot(n, i))

fun reflect(
    il: Float3List,
    ii: Int,
    nl: Float3List,
    ni: Int,
    out: Float3List,
    oi: Int,
): Float3List {
    val d = dot(nl, ni, il, ii)
    out.x[oi] = il.x[ii] - nl.x[ni] * (2f * d)
    out.y[oi] = il.y[ii] - nl.y[ni] * (2f * d)
    out.z[oi] = il.z[ii] - nl.z[ni] * (2f * d)
    return out
}

fun reflect(
    i: Float4,
    n: Float4,
) = i - n * (2f * dot(n, i))

fun reflect(
    il: Float4List,
    ii: Int,
    nl: Float4List,
    ni: Int,
    out: Float4List,
    oi: Int,
): Float4List {
    val d = dot(nl, ni, il, ii)
    out.x[oi] = il.x[ii] - nl.x[ni] * (2f * d)
    out.y[oi] = il.y[ii] - nl.y[ni] * (2f * d)
    out.z[oi] = il.z[ii] - nl.z[ni] * (2f * d)
    out.w[oi] = il.w[ii] - nl.w[ni] * (2f * d)
    return out
}
