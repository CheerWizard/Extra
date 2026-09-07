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

inline fun clamp(
    a: UInt,
    b: UInt,
    x: UInt,
): UInt =
    if (x < a) {
        a
    } else if (x > b) {
        b
    } else {
        x
    }

inline fun clamp(
    a: Int,
    b: Int,
    x: Int,
): Int =
    if (x < a) {
        a
    } else if (x > b) {
        b
    } else {
        x
    }

inline fun clamp(
    a: Long,
    b: Long,
    x: Long,
): Long =
    if (x < a) {
        a
    } else if (x > b) {
        b
    } else {
        x
    }

inline fun clamp(
    a: Float,
    b: Float,
    x: Float,
): Float =
    if (x < a) {
        a
    } else if (x > b) {
        b
    } else {
        x
    }

inline fun clamp(
    a: Double,
    b: Double,
    x: Double,
): Double =
    if (x < a) {
        a
    } else if (x > b) {
        b
    } else {
        x
    }

inline fun clamp(
    v: Float2,
    min: Float,
    max: Float,
) = Float2(clamp(min, max, v.x), clamp(min, max, v.y))

inline fun clamp(
    l: Float2List,
    i: Int,
    min: Float,
    max: Float,
    out: Float2List,
    oi: Int,
): Float2List {
    out.x[oi] = clamp(min, max, l.x[i])
    out.y[oi] = clamp(min, max, l.y[i])
    return out
}

inline fun clamp(
    v: Float3,
    min: Float,
    max: Float,
) = Float3(clamp(min, max, v.x), clamp(min, max, v.y), clamp(min, max, v.z))

inline fun clamp(
    l: Float3List,
    i: Int,
    min: Float,
    max: Float,
    out: Float3List,
    oi: Int,
): Float3List {
    out.x[oi] = clamp(min, max, l.x[i])
    out.y[oi] = clamp(min, max, l.y[i])
    out.z[oi] = clamp(min, max, l.z[i])
    return out
}

inline fun clamp(
    v: Float4,
    min: Float,
    max: Float,
) = Float4(clamp(min, max, v.x), clamp(min, max, v.y), clamp(min, max, v.z), clamp(min, max, v.w))

inline fun clamp(
    l: Float4List,
    i: Int,
    min: Float,
    max: Float,
    out: Float4List,
    oi: Int,
): Float4List {
    out.x[oi] = clamp(min, max, l.x[i])
    out.y[oi] = clamp(min, max, l.y[i])
    out.z[oi] = clamp(min, max, l.z[i])
    out.w[oi] = clamp(min, max, l.w[i])
    return out
}

inline fun clamp(
    v: Float2,
    min: Float2,
    max: Float2,
) = Float2(clamp(min.x, max.x, v.x), clamp(min.y, max.y, v.y))

inline fun clamp(
    l: Float2List,
    i: Int,
    minL: Float2List,
    minI: Int,
    maxL: Float2List,
    maxI: Int,
    out: Float2List,
    oi: Int,
): Float2List {
    out.x[oi] = clamp(minL.x[minI], maxL.x[maxI], l.x[i])
    out.y[oi] = clamp(minL.y[minI], maxL.y[maxI], l.y[i])
    return out
}

inline fun clamp(
    v: Float3,
    min: Float3,
    max: Float3,
) = Float3(clamp(min.x, max.x, v.x), clamp(min.y, max.y, v.y), clamp(min.z, max.z, v.z))

inline fun clamp(
    l: Float3List,
    i: Int,
    minL: Float3List,
    minI: Int,
    maxL: Float3List,
    maxI: Int,
    out: Float3List,
    oi: Int,
): Float3List {
    out.x[oi] = clamp(minL.x[minI], maxL.x[maxI], l.x[i])
    out.y[oi] = clamp(minL.y[minI], maxL.y[maxI], l.y[i])
    out.z[oi] = clamp(minL.z[minI], maxL.z[maxI], l.z[i])
    return out
}

inline fun clamp(
    v: Float4,
    min: Float4,
    max: Float4,
) = Float4(clamp(min.x, max.x, v.x), clamp(min.y, max.y, v.y), clamp(min.z, max.z, v.z), clamp(min.w, max.w, v.w))

inline fun clamp(
    l: Float4List,
    i: Int,
    minL: Float4List,
    minI: Int,
    maxL: Float4List,
    maxI: Int,
    out: Float4List,
    oi: Int,
): Float4List {
    out.x[oi] = clamp(minL.x[minI], maxL.x[maxI], l.x[i])
    out.y[oi] = clamp(minL.y[minI], maxL.y[maxI], l.y[i])
    out.z[oi] = clamp(minL.z[minI], maxL.z[maxI], l.z[i])
    out.w[oi] = clamp(minL.w[minI], maxL.w[maxI], l.w[i])
    return out
}
