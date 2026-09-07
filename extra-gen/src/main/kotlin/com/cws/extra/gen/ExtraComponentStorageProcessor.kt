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

import com.google.devtools.ksp.processing.Resolver
import com.google.devtools.ksp.symbol.KSClassDeclaration
import kotlin.sequences.forEach

data class ComponentType(
    val type: String,
    val genType: String,
    val qualifiedName: String,
    val entityCountPercentage: Float,
)

class ExtraComponentStorageProcessor(
    private val logger: ExtraLogger,
    private val fileGenerator: FileGenerator,
    private val fileTemplateManager: FileTemplateManager,
) {

    companion object {
        private const val TAG = "ExtraComponentStorageProcessor"
        const val PACKAGE_MEMORY = "com.cws.extra.memory"
    }

    private val componentTypes = mutableSetOf<ComponentType>()
    private val componentPackages = mutableSetOf<String>()

    fun process(resolver: Resolver, projectName: String) {
        logger.i(TAG) { "Scanning for @ExtraComponent..." }

        val components = resolver
            .getSymbolsWithAnnotation("$PACKAGE_MEMORY.ExtraComponent")
            .filterIsInstance<KSClassDeclaration>()
            .filter { declaration ->
                declaration.annotations.any { it.shortName.asString() == "ExtraComponent" }
            }

        val projectPackage = components.firstOrNull()?.packageName?.asString().orEmpty()

        components.forEach { declaration ->
            logger.i(TAG) { "Generate from $declaration" }
            generateForExtraComponent(declaration)
        }

        generateComponentRegistry(projectName, projectPackage)
    }

    private fun generateForExtraComponent(declaration: KSClassDeclaration) {
        val packageName = declaration.packageName.asString()
        val className = declaration.qualifiedName()
        val type = className.simpleName
        val genType = "${type}Storage"

        if (fileGenerator.contains(genType)) return

        val code = fileTemplateManager.read("ComponentStorage.txt")
            .replace("#pkg", packageName)
            .replace("#T", type)
            .replace("#extension", type.lowercase())

        componentTypes.add(ComponentType(
            type,
            genType,
            declaration.qualifiedName?.asString().orEmpty(),
            declaration.extraEntityCountPercentage()
        ))
        componentPackages.add(packageName)

        fileGenerator.generateFile(packageName, genType, code)
    }

    private fun generateComponentRegistry(projectName: String, projectPackage: String) {
        // always starts naming with uppercase char
        val filename = "${projectName.replaceFirstChar { it.uppercase() }}Components"

        if (fileGenerator.contains(filename)) return

        val code = buildString {
            appendLine("package $projectPackage")
            appendLine()
            appendLine("import com.cws.extra.ecs.ComponentRegistry")
            appendLine("import com.cws.extra.ecs.validatePercentage")
            appendLine("import kotlin.math.roundToInt")
            appendLine()
            componentPackages.forEach { pkg ->
                appendLine("import ${pkg}.*")
            }
            appendLine()
            appendLine("object $filename {")
            appendLine()
            appendLine("    fun registerAll() {")
            componentTypes.forEach { componentType ->
                val genType = componentType.genType
                val entityCountPercentage = componentType.entityCountPercentage
                appendLine("        ComponentRegistry.register<${componentType.type}>(\"${componentType.qualifiedName}\", validatePercentage(${entityCountPercentage}f)) {\n" +
                        "             ${genType}((it.toFloat() * validatePercentage(${entityCountPercentage}f)).roundToInt())" +
                "\n        }")
            }
            appendLine("    }")
            appendLine()
            appendLine("}")
        }

        fileGenerator.generateFile(projectPackage, filename, code)
    }

}