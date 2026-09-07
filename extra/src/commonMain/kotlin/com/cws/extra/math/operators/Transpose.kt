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

import com.cws.extra.math.matrices.*

fun transpose(
    m: Mat2,
    out: Mat2,
): Mat2 {
    val m00 = m.m00
    val m01 = m.m01
    val m10 = m.m10
    val m11 = m.m11

    out.m00 = m00
    out.m01 = m10
    out.m10 = m01
    out.m11 = m11

    return out
}

fun transpose(
    l: Mat2List,
    i: Int,
    out: Mat2List,
    oi: Int,
): Mat2List {
    val m00 = l.m00[i]
    val m01 = l.m01[i]
    val m10 = l.m10[i]
    val m11 = l.m11[i]

    out.m00[oi] = m00
    out.m01[oi] = m10
    out.m10[oi] = m01
    out.m11[oi] = m11

    return out
}

fun transpose(m: Mat2): Mat2 = transpose(m, m.copy())

fun transpose(
    m: Mat3,
    out: Mat3,
): Mat3 {
    val m00 = m.m00
    val m01 = m.m01
    val m02 = m.m02

    val m10 = m.m10
    val m11 = m.m11
    val m12 = m.m12

    val m20 = m.m20
    val m21 = m.m21
    val m22 = m.m22

    out.m00 = m00
    out.m01 = m10
    out.m02 = m20

    out.m10 = m01
    out.m11 = m11
    out.m12 = m21

    out.m20 = m02
    out.m21 = m12
    out.m22 = m22

    return out
}

fun transpose(
    l: Mat3List,
    i: Int,
    out: Mat3List,
    oi: Int,
): Mat3List {
    val m00 = l.m00[i]
    val m01 = l.m01[i]
    val m02 = l.m02[i]

    val m10 = l.m10[i]
    val m11 = l.m11[i]
    val m12 = l.m12[i]

    val m20 = l.m20[i]
    val m21 = l.m21[i]
    val m22 = l.m22[i]

    out.m00[oi] = m00
    out.m01[oi] = m10
    out.m02[oi] = m20

    out.m10[oi] = m01
    out.m11[oi] = m11
    out.m12[oi] = m21

    out.m20[oi] = m02
    out.m21[oi] = m12
    out.m22[oi] = m22

    return out
}

fun transpose(m: Mat3): Mat3 = transpose(m, m.copy())

fun transpose(
    m: Mat4,
    out: Mat4,
): Mat4 {

    val m00 = m.m00
    val m01 = m.m01
    val m02 = m.m02
    val m03 = m.m03

    val m10 = m.m10
    val m11 = m.m11
    val m12 = m.m12
    val m13 = m.m13

    val m20 = m.m20
    val m21 = m.m21
    val m22 = m.m22
    val m23 = m.m23

    val m30 = m.m30
    val m31 = m.m31
    val m32 = m.m32
    val m33 = m.m33

    out.m00 = m00
    out.m01 = m10
    out.m02 = m20
    out.m03 = m30

    out.m10 = m01
    out.m11 = m11
    out.m12 = m21
    out.m13 = m31

    out.m20 = m02
    out.m21 = m12
    out.m22 = m22
    out.m23 = m32

    out.m30 = m03
    out.m31 = m13
    out.m32 = m23
    out.m33 = m33

    return out
}

fun transpose(
    l: Mat4List,
    i: Int,
    out: Mat4List,
    oi: Int,
): Mat4List {

    val m00 = l.m00[i]
    val m01 = l.m01[i]
    val m02 = l.m02[i]
    val m03 = l.m03[i]

    val m10 = l.m10[i]
    val m11 = l.m11[i]
    val m12 = l.m12[i]
    val m13 = l.m13[i]

    val m20 = l.m20[i]
    val m21 = l.m21[i]
    val m22 = l.m22[i]
    val m23 = l.m23[i]

    val m30 = l.m30[i]
    val m31 = l.m31[i]
    val m32 = l.m32[i]
    val m33 = l.m33[i]

    out.m00[oi] = m00
    out.m01[oi] = m10
    out.m02[oi] = m20
    out.m03[oi] = m30

    out.m10[oi] = m01
    out.m11[oi] = m11
    out.m12[oi] = m21
    out.m13[oi] = m31

    out.m20[oi] = m02
    out.m21[oi] = m12
    out.m22[oi] = m22
    out.m23[oi] = m32

    out.m30[oi] = m03
    out.m31[oi] = m13
    out.m32[oi] = m23
    out.m33[oi] = m33

    return out
}

fun transpose(m: Mat4): Mat4 = transpose(m, m.copy())
