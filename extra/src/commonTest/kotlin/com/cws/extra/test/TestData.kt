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

import com.cws.extra.math.vectors.*
import com.cws.extra.math.matrices.*
import com.cws.extra.memory.ExtraBridge
import com.cws.extra.memory.ExtraComponent
import com.cws.extra.memory.ExtraData
import com.cws.extra.memory.ExtraEnum
import com.cws.extra.memory.ExtraFixedSize
import com.cws.extra.memory.ExtraList
import com.cws.extra.memory.ExtraStringUtf16
import com.cws.extra.memory.NativeBuffer
import kotlinx.serialization.Serializable
import kotlin.math.PI

@ExtraEnum
@ExtraList
enum class TestEnumOrdinal {
    Ordinal_0,
    Ordinal_1,
    Ordinal_2,
    Ordinal_3,
    Ordinal_4,
    Ordinal_5,
}

@ExtraEnum
@ExtraList
enum class TestEnumRaw(val rawValue: Float) {
    Raw_0(0.125f),
    Raw_1(123.3f),
    Raw_2(1237.586f),
    Raw_3(0f),
    Raw_4(2442f),
    Raw_5(PI.toFloat()),
}

@ExtraData
data class TestData(
    val id: Long,
    val timestamp: Long,
    val name: String,
    val width: Int,
    val height: Int,
    val x: Float,
    val y: Float,
    val flag: Boolean,
    val age: Short,
    val ordinalEnum: TestEnumOrdinal,
    val rawEnum: TestEnumRaw,
    @ExtraFixedSize(12)
    val fixedStringUtf8: String,
    val stringUtf8: String,
    @ExtraFixedSize(18)
    @ExtraStringUtf16
    val fixedStringUtf16: String,
    @ExtraStringUtf16
    val stringUtf16: String,
    @ExtraFixedSize(24)
    val fixedBytes: ByteArray,
    val bytes: ByteArray,
    @ExtraFixedSize(48)
    val fixedShorts: ShortArray,
    val shorts: ShortArray,
    @ExtraFixedSize(64)
    val fixedInts: IntArray,
    val ints: IntArray,
    @ExtraFixedSize(36)
    val fixedLongs: LongArray,
    val longs: LongArray,
    @ExtraFixedSize(36)
    val fixedFloats: FloatArray,
    val floats: FloatArray,
    @ExtraFixedSize(36)
    val fixedDoubles: DoubleArray,
    val doubles: DoubleArray,
    val nestedDataBuffer: NativeBuffer,
    val data: List<NestedData>,
) {

    @ExtraData
    data class NestedData(
        val id: Long,
        val float2: Float2,
        val float3: Float3,
        val float4: Float4,
        val int2: Int2,
        val int3: Int3,
        val int4: Int4,
        val uint2: UInt2,
        val uInt3: UInt3,
        val uInt4: UInt4,
        val mat2: Mat2,
        val mat3: Mat3,
        val mat4: Mat4,
        val quaternion: Quaternion,
        val data: Map<String, String>,
        val subscribers: Set<String>,
    )

}

@ExtraEnum
enum class HeroClass {
    Warrior,
    Mage,
    Archer,
}

@ExtraList
data class Stats(
    var health: Int,
    val mana: Float,
    val stamina: Double,
    val level: Short,
    val alive: Boolean,
)

@ExtraList
data class Transform(
    var x: Float,
    var y: Float,
    var z: Float,
    val rotation: Float,
    val scale: Float,
)

@ExtraList
data class InventoryItem(
    val id: Int,
    val amount: Int,
)

@ExtraList
data class Hero(

    // Primitive lists
    val id: Int,
    var experience: Long,
    val speed: Float,
    val weight: Double,
    val level: Short,
    val prestige: Byte,
    val enabled: Boolean,
    val symbol: Char,

    // String
    val name: String,

    // Fixed-size string metadata
    @ExtraFixedSize(32)
    val tag: String,

    // Native enum
    val heroClass: HeroClass,

    // Nested NativeLists
    val transform: Transform,
    val stats: Stats,

    // Generic reference
    val nickname: String?,
)

@Serializable
@ExtraData
@ExtraList
@ExtraComponent(entityCountPercentage = 1f)
data class Movement(
    val speed: Float,
//    val dir: Float3,
)

@Serializable
@ExtraData
@ExtraList
@ExtraComponent(entityCountPercentage = 0.2f)
data class Camera(
    val fov: Float,
//    val position: Float3,
//    val lookAt: Float3,
//    val projection: Mat4,
)

@Serializable
@ExtraData
@ExtraList
@ExtraComponent(entityCountPercentage = 1f)
data class Velocity(
    val x: Float,
    val y: Float,
    val z: Float,
//    val dir: Float3,
)

@Serializable
@ExtraData
@ExtraList
@ExtraComponent(entityCountPercentage = 0.2f)
data class Renderable(
    val textureId: Int,
//    val dir: Float3,
)

@Serializable
@ExtraData
@ExtraList
@ExtraComponent(entityCountPercentage = 0.8f)
data class Health(
    val current: Float,
    val maximum: Float,
)

@Serializable
@ExtraData
@ExtraList
@ExtraComponent(entityCountPercentage = 0.35f)
data class Damage(
    val amount: Float,
    val armorPenetration: Float,
)

@Serializable
@ExtraData
@ExtraList
@ExtraComponent(entityCountPercentage = 0.25f)
data class Collision(
    val impulse: Float,
    val damageScale: Float,
)