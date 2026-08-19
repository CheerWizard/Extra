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

import com.google.devtools.ksp.processing.KSPLogger
import com.google.devtools.ksp.processing.Resolver
import com.google.devtools.ksp.symbol.KSClassDeclaration
import kotlin.sequences.forEach

data class ComponentType(
    val type: String,
    val genType: String,
)

class ExtraComponentStorageProcessor(
    private val logger: KSPLogger,
    private val fileGenerator: FileGenerator,
) {

    companion object {
        private const val TAG = "ExtraComponentStorageProcessor"
        const val PACKAGE_MEMORY = "com.cws.extra.memory"
        const val PACKAGE_ECS = "com.cws.extra.ecs"
        const val COMPONENT_REGISTRY = "ComponentRegistry"
    }

    private var componentIdCounter = 0
    private val componentTypes = mutableSetOf<ComponentType>()
    private val componentPackages = mutableSetOf<String>()

    fun process(resolver: Resolver) {
        logger.info("$TAG: Scanning for @ExtraComponent...")

        resolver
            .getSymbolsWithAnnotation("$PACKAGE_MEMORY.ExtraComponent")
            .filterIsInstance<KSClassDeclaration>()
            .filter { declaration ->
                declaration.annotations.any { it.shortName.asString() == "ExtraComponent" }
            }
            .forEach { declaration ->
                logger.info("$TAG: Generate from $declaration")
                generateForExtraComponent(declaration)
            }

        generateComponentRegistry()
    }

    private fun generateForExtraComponent(declaration: KSClassDeclaration) {
        val packageName = declaration.packageName.asString()
        val className = declaration.qualifiedName()
        val type = className.simpleName
        val genType = "${type}Storage"

        if (fileGenerator.contains(genType)) return

        val code = fileGenerator.readTemplate("ComponentStorage")
            .replace("#pkg", packageName)
            .replace("#T", type)
            .replace("#extension", "${type.lowercase()}s")
            .replace("#COMPONENT_ID", componentIdCounter.toString())

        componentIdCounter++

        componentTypes.add(ComponentType(type, genType))
        componentPackages.add(packageName)

        fileGenerator.generateFile(packageName, genType, code)
    }

    private fun generateComponentRegistry() {
        if (fileGenerator.contains(COMPONENT_REGISTRY)) return

        val code = buildString {
            appendLine("package $PACKAGE_ECS")
            appendLine()
            componentPackages.forEach { pkg ->
                appendLine("import ${pkg}.*")
            }
            appendLine("import $PACKAGE_MEMORY.ExtraData")
            appendLine()
            appendLine("inline fun <reified T> getComponentID(): Int {")
            appendLine("    return when (T::class) {")
            componentTypes.forEach { componentType ->
                appendLine("        ${componentType.type}::class -> ${componentType.type}.COMPONENT_ID")
            }
            appendLine("        else -> 0")
            appendLine("    }")
            appendLine("}")
            appendLine()
            appendLine("fun ComponentRegistry(capacity: Int) = ComponentRegistry(")
            componentTypes.forEach { componentType ->
                appendLine("    ${componentType.genType}(capacity),")
            }
            appendLine(")")
            appendLine()
            appendLine("@ExtraData")
            appendLine("data class ComponentRegistry(")
            componentTypes.forEach { componentType ->
                appendLine("    val ${componentType.type.lowercase()}s: ${componentType.genType},")
            }
            appendLine(") {")
            appendLine()
            appendLine("    private val components = mutableListOf(")
            componentTypes.forEach { componentType ->
                appendLine("        ${componentType.type.lowercase()}s,")
            }
            appendLine("    )")
            appendLine()
            appendLine("    val size: Int get() = components.size")
            appendLine()
            appendLine("    operator fun get(i: Int): ComponentStorage = components[i]")
            appendLine()
            appendLine("    fun clear() {")
            appendLine("        components.clear()")
            appendLine("    }")
            appendLine()
            appendLine("}")
        }

        fileGenerator.generateFile(PACKAGE_ECS, COMPONENT_REGISTRY, code)
    }

}