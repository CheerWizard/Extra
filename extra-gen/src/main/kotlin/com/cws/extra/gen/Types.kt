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
package com.cws.extra.gen

val primitiveTypes = setOf(
    "Boolean", "Byte", "UByte",
    "Short", "Char", "UShort",
    "Int", "Long", "UInt", "ULong",
    "Float", "Double",
)

val primitiveListTypes = setOf(
    "BooleanList", "ByteList", "UByteList",
    "ShortList", "CharList", "UShortList",
    "IntList", "LongList", "UIntList", "ULongList",
    "FloatList", "DoubleList",
)

val matrices = setOf("Mat2", "Mat3", "Mat4")

val matricesList = setOf("Mat2List", "Mat3List", "Mat4List")

val variableLengthTypes = setOf(
    "ByteArray", "UByteArray", "BooleanArray",
    "ShortArray", "CharArray", "UShortArray",
    "IntArray", "LongArray", "UIntArray", "ULongArray",
    "FloatArray", "DoubleArray",
    "String",
)

val kotlinToCppTypes = mapOf(
    "Boolean" to "bool",
    "Byte" to "int8_t",
    "Short" to "int16_t",
    "Char" to "uint16_t",
    "Int" to "int32_t",
    "Long" to "int64_t",
    "Float" to "float",
    "Double" to "double",
)

val kotlinToJniTypes = mapOf(
    "Boolean" to "jboolean",
    "Byte" to "jbyte",
    "Short" to "jshort",
    "Char" to "jchar",
    "Int" to "jint",
    "Long" to "jlong",
    "Float" to "jfloat",
    "Double" to "jdouble",
    "ByteArray" to "jbyteArray",
    "BooleanArray" to "jbooleanArray",
    "ShortArray" to "jshortArray",
    "CharArray" to "jcharArray",
    "IntArray" to "jintArray",
    "LongArray" to "jlongArray",
    "FloatArray" to "jfloatArray",
    "DoubleArray" to "jdoubleArray",
    "String" to "jstring",
    "Unit" to "void",
    "Any" to "jobject"
)

val String.isVariableLength get() = this in variableLengthTypes
val Field.isVariableLength get() = type.isVariableLength

val String.isString get() = this == "String"
val Field.isString get() = type.isString

val String.isMatrix get() = this in matrices

val Field.isMatrix get() = type.isMatrix

val String.isMatrixList get() = this in matrices

val Field.isMatrixList get() = type.isMatrixList

val String.isPrimitive get() = this in primitiveTypes
val Field.isPrimitive get() = type.isPrimitive

val String.isPrimitiveList get() = this in primitiveListTypes
val Field.isPrimitiveList get() = type.isPrimitiveList

val Field.isNested get() = !isPrimitive && !isVariableLength
val String.isNested get() = !isPrimitive && !isVariableLength

val String.isArray get() = this == "Array"
val Field.isArray get() = type.isArray

val String.isList get() = this == "List" || this == "MutableList" || this == "ArrayList"
val Field.isList get() = type.isList

val String.isSet get() = this == "Set" || this == "MutableSet" || this == "HashSet"
val Field.isSet get() = type.isSet

val String.isMap get() = this == "Map" || this == "MutableMap" || this == "HashMap"
val Field.isMap get() = type.isMap

val String.isGenericList get() = this == "GenericList"
val Field.isGenericList get() = type.isGenericList

val String.isListCollection get() = isArray || isList || isSet || isGenericList
val Field.isListCollection get() = type.isListCollection

val String.isCollection get() = isListCollection || isMap
val Field.isCollection get() = type.isCollection

val String.isNativeBuffer get() = this == "NativeBuffer"
val Field.isNativeBuffer get() = type.isNativeBuffer

val typesWithDefaults = mapOf(
    "Boolean" to "false",
    "Byte" to "0",
    "UByte" to "0u",
    "Short" to "0",
    "UShort" to "0u",
    "Char" to "'\\u0000'",
    "Int" to "0",
    "UInt" to "0u",
    "Long" to "0L",
    "ULong" to "0uL",
    "Float" to "0f",
    "Double" to "0.0",
    "ByteArray" to "ByteArray(0)",
    "BooleanArray" to "BooleanArray(0)",
    "UByteArray" to "UByteArray(0)",
    "ShortArray" to "ShortArray(0)",
    "UShortArray" to "UShortArray(0)",
    "CharArray" to "CharArray(0)",
    "IntArray" to "IntArray(0)",
    "UIntArray" to "UIntArray(0)",
    "LongArray" to "LongArray(0)",
    "ULongArray" to "ULongArray(0)",
    "FloatArray" to "FloatArray(0)",
    "DoubleArray" to "DoubleArray(0)",
    "String" to "\"\"",
    "Mat2" to "Mat2()",
    "Mat3" to "Mat3()",
    "Mat4" to "Mat4()",
    "Array" to "arrayOf()",
    "List" to "emptyList()",
    "ArrayList" to "ArrayList()",
    "MutableList" to "mutableListOf()",
    "Set" to "emptySet()",
    "HashSet" to "HashSet()",
    "MutableSet" to "mutableSetOf()",
    "Map" to "emptyMap()",
    "HashMap" to "HashMap()",
    "MutableMap" to "mutableMapOf()",
)

fun String.sizeBytes(fixedSize: Int?, isStringUtf16: Boolean, ref: String): String? = when {
    isPrimitive -> "${this}.SIZE_BYTES"
    isString -> {
        if (fixedSize != null) {
            // fixed size - use compile time constant, no runtime length needed
            if (isStringUtf16) {
                "$fixedSize * Char.SIZE_BYTES"
            } else {
                "$fixedSize * Byte.SIZE_BYTES"
            }
        } else {
            // dynamic - runtime length + prefix
            val length = if (isStringUtf16) {
                "$ref.orEmpty().sizeBytesUtf16(memoryLayout)"
            } else {
                "$ref.orEmpty().sizeBytesUtf8(memoryLayout)"
            }
            "Int.SIZE_BYTES + $length"
        }
    }
    isVariableLength -> {
        if (fixedSize != null) {
            // fixed size - use compile time constant, no runtime length needed
            "$fixedSize * ${removeSuffix("Array")}.SIZE_BYTES"
        } else {
            // dynamic - runtime length + prefix
            val length = "$ref.sizeBytes(memoryLayout)"
            "Int.SIZE_BYTES + $length"
        }
    }
    else -> null
}

fun String.sizeBytesPacked(isStringUtf16: Boolean, ref: String): String? = when {
    isPrimitive -> "${this}.SIZE_BYTES"
    isString -> {
        if (isStringUtf16) {
            "$ref.orEmpty().sizeBytesUtf16(memoryLayout)"
        } else {
            "$ref.orEmpty().sizeBytesUtf8(memoryLayout)"
        }
    }
    isVariableLength -> {
        "$ref.sizeBytes(memoryLayout)"
    }
    else -> null
}