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

import com.google.devtools.ksp.symbol.KSAnnotated
import com.squareup.kotlinpoet.TypeName

fun KSAnnotated.extraFixedSize(): Int? = findAnnotation("ExtraFixedSize", "size")

fun KSAnnotated.extraStringUtf16(): Boolean = hasAnnotation("ExtraStringUtf16")

fun TypeName.extraStringUtf16(): Boolean = hasAnnotation("ExtraStringUtf16")

fun KSAnnotated.extraEntityCountPercentage(): Float = findAnnotation("ExtraComponent", "entityCountPercentage") ?: 0.2f

fun KSAnnotated.extraBridgeLibName(): String = findAnnotation("ExtraBridge", "libName") ?: ""

fun KSAnnotated.extraBridgeTransport(): String = findAnnotation("ExtraBridge", "transport") ?: ""

fun TypeName.extraFixedSize(): Int? {
    val annotation = annotations.find {
        it.typeName.toString().endsWith("ExtraFixedSize")
    } ?: return null

    return annotation.members
        .firstOrNull()
        ?.toString()
        ?.trim()
        ?.toIntOrNull()
}

private fun KSAnnotated.hasAnnotation(name: String): Boolean {
    return annotations.any { it.shortName.asString() == name }
}

private fun TypeName.hasAnnotation(name: String): Boolean {
    return annotations.any { it.typeName.toString() == name }
}

private fun <T> KSAnnotated.findAnnotation(annotationName: String, argName: String): T? {
    return annotations
        .find { it.shortName.asString() == annotationName }
        ?.arguments
        ?.firstOrNull { it.name?.asString() == argName }
        ?.value as? T
}