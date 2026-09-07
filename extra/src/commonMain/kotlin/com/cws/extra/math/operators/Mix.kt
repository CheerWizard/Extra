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

fun mix(
    a: Float,
    b: Float,
    t: Float,
) = a + (b - a) * t

fun mix(
    a: Float2,
    b: Float2,
    t: Float,
) = Float2(mix(a.x, b.x, t), mix(a.y, b.y, t))

fun mix(
    al: Float2List,
    ai: Int,
    bl: Float2List,
    bi: Int,
    t: Float,
    out: Float2List,
    oi: Int,
): Float2List {
    out.x[oi] = mix(al.x[ai], bl.x[bi], t)
    out.y[oi] = mix(al.y[ai], bl.y[bi], t)
    return out
}

fun mix(
    a: Float3,
    b: Float3,
    t: Float,
) = Float3(mix(a.x, b.x, t), mix(a.y, b.y, t), mix(a.z, b.z, t))

fun mix(
    al: Float3List,
    ai: Int,
    bl: Float3List,
    bi: Int,
    t: Float,
    out: Float3List,
    oi: Int,
): Float3List {
    out.x[oi] = mix(al.x[ai], bl.x[bi], t)
    out.y[oi] = mix(al.y[ai], bl.y[bi], t)
    out.z[oi] = mix(al.z[ai], bl.z[bi], t)
    return out
}

fun mix(
    a: Float4,
    b: Float4,
    t: Float,
) = Float4(mix(a.x, b.x, t), mix(a.y, b.y, t), mix(a.z, b.z, t), mix(a.w, b.w, t))

fun mix(
    al: Float4List,
    ai: Int,
    bl: Float4List,
    bi: Int,
    t: Float,
    out: Float4List,
    oi: Int,
): Float4List {
    out.x[oi] = mix(al.x[ai], bl.x[bi], t)
    out.y[oi] = mix(al.y[ai], bl.y[bi], t)
    out.z[oi] = mix(al.z[ai], bl.z[bi], t)
    out.w[oi] = mix(al.w[ai], bl.w[bi], t)
    return out
}

fun mix(
    a: Float2,
    b: Float2,
    t: Float2,
) = Float2(mix(a.x, b.x, t.x), mix(a.y, b.y, t.y))

fun mix(
    al: Float2List,
    ai: Int,
    bl: Float2List,
    bi: Int,
    tl: Float2List,
    ti: Int,
    out: Float2List,
    oi: Int,
): Float2List {
    out.x[oi] = mix(al.x[ai], bl.x[bi], tl.x[ti])
    out.y[oi] = mix(al.y[ai], bl.y[bi], tl.y[ti])
    return out
}

fun mix(
    a: Float3,
    b: Float3,
    t: Float3,
) = Float3(mix(a.x, b.x, t.x), mix(a.y, b.y, t.y), mix(a.z, b.z, t.z))

fun mix(
    al: Float3List,
    ai: Int,
    bl: Float3List,
    bi: Int,
    tl: Float3List,
    ti: Int,
    out: Float3List,
    oi: Int,
): Float3List {
    out.x[oi] = mix(al.x[ai], bl.x[bi], tl.x[ti])
    out.y[oi] = mix(al.y[ai], bl.y[bi], tl.y[ti])
    out.z[oi] = mix(al.z[ai], bl.z[bi], tl.z[ti])
    return out
}

fun mix(
    a: Float4,
    b: Float4,
    t: Float4,
) = Float4(mix(a.x, b.x, t.x), mix(a.y, b.y, t.y), mix(a.z, b.z, t.z), mix(a.w, b.w, t.w))

fun mix(
    al: Float4List,
    ai: Int,
    bl: Float4List,
    bi: Int,
    tl: Float4List,
    ti: Int,
    out: Float4List,
    oi: Int,
): Float4List {
    out.x[oi] = mix(al.x[ai], bl.x[bi], tl.x[ti])
    out.y[oi] = mix(al.y[ai], bl.y[bi], tl.y[ti])
    out.z[oi] = mix(al.z[ai], bl.z[bi], tl.z[ti])
    out.w[oi] = mix(al.w[ai], bl.w[bi], tl.w[ti])
    return out
}
