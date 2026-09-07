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

fun normalize(
    v: Float2,
    out: Float2,
): Float2 {
    val l = v.length
    if (l == 0f) return out
    out.x = v.x / l
    out.y = v.y / l
    return out
}

fun normalize(v: Float2): Float2 = normalize(v, v)

fun normalize(
    l: Float2List,
    i: Int,
    out: Float2List,
    outI: Int,
): Float2List {
    val len = length(l, i)
    if (len == 0f) return out
    out.x[outI] = l.x[i] / len
    out.y[outI] = l.y[i] / len
    return out
}

fun normalize(l: Float2List, i: Int): Float2List = normalize(l, i, l, i)

fun normalize(
    v: Int2,
    out: Int2,
): Int2 {
    val l = v.length
    if (l == 0) return out
    out.x = v.x / l
    out.y = v.y / l
    return out
}

fun normalize(v: Int2): Int2 = normalize(v, v)

fun normalize(
    l: Int2List,
    i: Int,
    out: Int2List,
    outI: Int,
): Int2List {
    val len = length(l, i)
    if (len == 0) return out
    out.x[outI] = l.x[i] / len
    out.y[outI] = l.y[i] / len
    return out
}

fun normalize(l: Int2List, i: Int): Int2List = normalize(l, i, l, i)

fun normalize(
    v: UInt2,
    out: UInt2,
): UInt2 {
    val l = v.length
    if (l == 0u) return out
    out.x = v.x / l
    out.y = v.y / l
    return out
}

fun normalize(v: UInt2): UInt2 = normalize(v, v)

fun normalize(
    l: UInt2List,
    i: Int,
    out: UInt2List,
    outI: Int,
): UInt2List {
    val len = length(l, i)
    if (len == 0u) return out
    out.x[outI] = l.x[i] / len
    out.y[outI] = l.y[i] / len
    return out
}

fun normalize(l: UInt2List, i: Int): UInt2List = normalize(l, i, l, i)

fun normalize(
    v: Float3,
    out: Float3,
): Float3 {
    val l = v.length
    if (l == 0f) return out
    out.x = v.x / l
    out.y = v.y / l
    out.z = v.z / l
    return out
}

fun normalize(v: Float3): Float3 = normalize(v, v)

fun normalize(
    l: Float3List,
    i: Int,
    out: Float3List,
    outI: Int,
): Float3List {
    val len = length(l, i)
    if (len == 0f) return out
    out.x[outI] = l.x[i] / len
    out.y[outI] = l.y[i] / len
    out.z[outI] = l.z[i] / len
    return out
}

fun normalize(l: Float3List, i: Int): Float3List = normalize(l, i, l, i)

fun normalize(
    v: Int3,
    out: Int3,
): Int3 {
    val l = v.length
    if (l == 0) return out
    out.x = v.x / l
    out.y = v.y / l
    out.z = v.z / l
    return out
}

fun normalize(v: Int3): Int3 = normalize(v, v)

fun normalize(
    l: Int3List,
    i: Int,
    out: Int3List,
    outI: Int,
): Int3List {
    val len = length(l, i)
    if (len == 0) return out
    out.x[outI] = l.x[i] / len
    out.y[outI] = l.y[i] / len
    out.z[outI] = l.z[i] / len
    return out
}

fun normalize(l: Int3List, i: Int): Int3List = normalize(l, i, l, i)

fun normalize(
    v: UInt3,
    out: UInt3,
): UInt3 {
    val l = v.length
    if (l == 0u) return out
    out.x = v.x / l
    out.y = v.y / l
    out.z = v.z / l
    return out
}

fun normalize(v: UInt3): UInt3 = normalize(v, v)

fun normalize(
    l: UInt3List,
    i: Int,
    out: UInt3List,
    outI: Int,
): UInt3List {
    val len = length(l, i)
    if (len == 0u) return out
    out.x[outI] = l.x[i] / len
    out.y[outI] = l.y[i] / len
    out.z[outI] = l.z[i] / len
    return out
}

fun normalize(l: UInt3List, i: Int): UInt3List = normalize(l, i, l, i)

fun normalize(
    v: Float4,
    out: Float4,
): Float4 {
    val l = v.length
    if (l == 0f) return out
    out.x = v.x / l
    out.y = v.y / l
    out.z = v.z / l
    out.w = v.w / l
    return out
}

fun normalize(v: Float4): Float4 = normalize(v, v)

fun normalize(
    l: Float4List,
    i: Int,
    out: Float4List,
    outI: Int,
): Float4List {
    val len = length(l, i)
    if (len == 0f) return out
    out.x[outI] = l.x[i] / len
    out.y[outI] = l.y[i] / len
    out.z[outI] = l.z[i] / len
    out.w[outI] = l.w[i] / len
    return out
}

fun normalize(l: Float4List, i: Int): Float4List = normalize(l, i, l, i)

fun normalize(
    v: Int4,
    out: Int4,
): Int4 {
    val l = v.length
    if (l == 0) return out
    out.x = v.x / l
    out.y = v.y / l
    out.z = v.z / l
    out.w = v.w / l
    return out
}

fun normalize(v: Int4): Int4 = normalize(v, v)

fun normalize(
    l: Int4List,
    i: Int,
    out: Int4List,
    outI: Int,
): Int4List {
    val len = length(l, i)
    if (len == 0) return out
    out.x[outI] = l.x[i] / len
    out.y[outI] = l.y[i] / len
    out.z[outI] = l.z[i] / len
    out.w[outI] = l.w[i] / len
    return out
}

fun normalize(l: Int4List, i: Int): Int4List = normalize(l, i, l, i)

fun normalize(
    v: UInt4,
    out: UInt4,
): UInt4 {
    val l = v.length
    if (l == 0u) return out
    out.x = v.x / l
    out.y = v.y / l
    out.z = v.z / l
    out.w = v.w / l
    return out
}

fun normalize(v: UInt4): UInt4 = normalize(v, v)

fun normalize(
    l: UInt4List,
    i: Int,
    out: UInt4List,
    outI: Int,
): UInt4List {
    val len = length(l, i)
    if (len == 0u) return out
    out.x[outI] = l.x[i] / len
    out.y[outI] = l.y[i] / len
    out.z[outI] = l.z[i] / len
    out.w[outI] = l.w[i] / len
    return out
}

fun normalize(l: UInt4List, i: Int): UInt4List = normalize(l, i, l, i)

fun normalize(
    v: Quaternion,
    out: Quaternion,
): Quaternion {
    val l = v.length
    if (l == 0f) return out
    out.x = v.x / l
    out.y = v.y / l
    out.z = v.z / l
    return out
}

fun normalize(v: Quaternion): Quaternion = normalize(v, v)

fun normalize(
    l: QuaternionList,
    i: Int,
    out: QuaternionList,
    outI: Int,
): QuaternionList {
    val len = length(l, i)
    if (len == 0f) return out
    out.x[outI] = l.x[i] / len
    out.y[outI] = l.y[i] / len
    out.z[outI] = l.z[i] / len
    out.w[outI] = l.w[i] / len
    return out
}

fun normalize(l: QuaternionList, i: Int): QuaternionList = normalize(l, i, l, i)
