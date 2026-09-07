package com.cws.extra.gen

import com.cws.extra.gen.ExtraProcessor.Companion.PACKAGE_CORE
import com.google.devtools.ksp.processing.Dependencies
import com.google.devtools.ksp.processing.SymbolProcessorEnvironment
import com.google.devtools.ksp.symbol.ClassKind
import com.google.devtools.ksp.symbol.KSClassDeclaration
import com.google.devtools.ksp.symbol.KSFile
import com.squareup.kotlinpoet.ClassName
import com.squareup.kotlinpoet.ParameterizedTypeName
import com.squareup.kotlinpoet.TypeName
import java.io.File
import kotlin.collections.get
import kotlin.text.appendLine

data class CppBridgeData(
    val name: String,
    val fields: List<Field>,
    val dependencies: List<String>,
    val containingFile: KSFile?,
) {

    val hasComplexFields: Boolean = fields.any {
        it.fixedSize == null && (it.isVariableLength || it.isCollection)
    }

    fun isComplex(nativeDataByName: Map<String, CppBridgeData>): Boolean {
        if (hasComplexFields) return true
        return fields
            .filter { it.isNested }
            .mapNotNull { nativeDataByName[it.type] }
            .any { it.isComplex(nativeDataByName) }
    }

}

data class CppBridge(
    val packageName: String,
    val jniPackageName: String,
    val name: String,
    val libName: String,
    val functions: List<Function>,
    val dependencies: List<String>,
)

data class CppBridgeEnum(
    val name: String,
    val parentType: String,
    val entries: List<Pair<String, Any>>,
    val containingFile: KSFile?,
)

class ExtraCppProcessor(
    private val environment: SymbolProcessorEnvironment,
    private val logger: ExtraLogger,
    private val fileTemplateManager: FileTemplateManager,
    private val projectPath: String,
) {

    companion object {
        private const val TAG = "ExtraCppProcessor"
    }

    private val collectedExtraBridgeData = mutableListOf<CppBridgeData>()
    private val collectedExtraBridgeEnum = mutableListOf<CppBridgeEnum>()
    private val collectedExtraBridge = mutableListOf<CppBridge>()
    private var collectedExtraBridgeDataByName = mapOf<String, CppBridgeData>()

    private val defaultTypesIncludes = listOf("\"ExtraTypes.h\"")

    private val cppOutputPath = environment.options["cpp_output_path"]
    private val cppTypePrefix = environment.options["cpp_type_prefix"]
    private val cppTypesIncludes = environment.options["cpp_types_includes"]?.split(",").orEmpty()
    private val cppBridgeIncludes = environment.options["cpp_bridge_includes"]?.split(",").orEmpty()
    private val cppTypesName = "${cppTypePrefix}Types.h"
    private val cppTypesPath = "${cppOutputPath}/${cppTypesName}"

    fun collectExtraBridge(declaration: KSClassDeclaration) {
        val dependencies = mutableSetOf<String>()
        val nestedDependencies = mutableSetOf<String>()
        val functions = declaration.createFunctions()
        functions.forEach { function ->
            function.args.forEach { arg ->
                when {
                    arg.isNested -> dependencies.add(arg.typeName.toString())
                    arg.isCollection -> nestedDependencies.addAll(arg.nestedDependencies())
                }
            }
        }
        val packageName = declaration.packageName.asString()

        collectedExtraBridge += CppBridge(
            packageName = packageName,
            jniPackageName = packageName.replace(".", "_"),
            name = declaration.simpleName.asString(),
            libName = declaration.extraBridgeLibName(),
            functions = functions,
            dependencies = (dependencies + nestedDependencies).toList(),
        )
    }

    fun collectExtraBridgeData(declaration: KSClassDeclaration) {
        val fields = declaration.createFields()
        val dependencies = fields.filter { it.isNested }.map { it.type }
        val nestedDependencies = fields.filter { it.isCollection }.flatMap { it.nestedDependencies() }

        collectedExtraBridgeData += CppBridgeData(
            name = declaration.simpleName.asString(),
            fields = fields,
            dependencies = dependencies + nestedDependencies,
            containingFile = declaration.containingFile,
        )
    }

    private fun Field.nestedDependencies(): List<String> {
        val parameterized = typeName as? ParameterizedTypeName ?: return emptyList()
        return parameterized.typeArguments
            .filterIsInstance<ClassName>()
            .filter { !it.simpleName.isPrimitive && !it.simpleName.isVariableLength }
            .map { it.simpleName }
    }

    fun collectExtraBridgeEnum(declaration: KSClassDeclaration) {
        val parentType = getEnumParentType(declaration)
        val entries = declaration.resolveEnumEntries()

        collectedExtraBridgeEnum += CppBridgeEnum(
            name = declaration.simpleName.asString(),
            parentType = parentType,
            entries = entries,
            containingFile = declaration.containingFile,
        )
    }

    private fun KSClassDeclaration.resolveEnumEntries(): List<Pair<String, Any>> {
        val rawValueParamIndex = primaryConstructor
            ?.parameters
            ?.indexOfFirst { it.name?.asString() == "rawValue" }
            ?: -1

        val sourceText = containingFile?.filePath?.let { File(it).readText() }

        return declarations
            .filterIsInstance<KSClassDeclaration>()
            .filter { it.classKind == ClassKind.ENUM_ENTRY }
            .mapIndexed { ordinal, entry ->
                val rawValue = if (rawValueParamIndex >= 0 && sourceText != null) {
                    val entryName = entry.simpleName.asString()
                    Regex("""^\s*$entryName\s*\(([^)]+)\)""", RegexOption.MULTILINE)
                        .find(sourceText)
                        ?.groupValues
                        ?.getOrNull(1)
                        ?.split(",")
                        ?.getOrNull(rawValueParamIndex)
                        ?.trim()
                        ?.toIntOrNull()
                } else null
                entry.simpleName.asString() to (rawValue ?: ordinal)
            }
            .toList()
    }

    fun generate() {
        if (collectedExtraBridge.isEmpty()) return

        if (cppOutputPath == null) {
            logger.w(TAG) {
                "Failed to generate C++ code. Please specify cpp_output_path in your Gradle module ksp {} block."
            }
            return
        }

        collectedExtraBridgeDataByName = collectedExtraBridgeData.associateBy { it.name }

        registerAggregatingDeps()
        copyExtraTypes()
        copyExtraJni()
        generateTypes(defaultTypesIncludes + cppTypesIncludes)

        if (cppTypesName.isNotEmpty()) {
            collectedExtraBridge.forEach { bridge ->
                generateCppBridge(bridge, cppBridgeIncludes + "\"${cppTypesName}\"")
                generateCppBridgeJni(bridge)
                generateKotlinBridgeJni(bridge)
            }
        } else {
            logger.w(TAG) {
                "Failed to generate C++ bridge. C++ type file is null or empty."
            }
        }
    }

    private fun generateTypes(includes: List<String>) {
        val output = buildString {
            appendLine("// Generated from Kotlin Extra library")
            appendLine()
            appendLine("#pragma once")
            appendLine()
            includes.forEach { include ->
                appendLine("#include $include")
            }
            appendLine()
            generateForwardDeclarations()
            appendLine()
            appendLine("// -------------- ExtraEnum -----------------")
            appendLine()
            collectedExtraBridgeEnum.forEach { enum ->
                logger.i(TAG) {
                    "Generating ${enum.name} into $cppTypesPath"
                }
                append(generateCppEnum(enum))
                appendLine()
            }
            appendLine("// -------------- ExtraData -----------------")
            appendLine()
            topologicallySorted(collectedExtraBridgeData).forEach { struct ->
                logger.i(TAG) {
                    "Generating ${struct.name} into $cppTypesPath"
                }
                append(generateCppStruct(struct))
                appendLine()
            }
        }
        writeToFile(cppTypesPath, output)
    }

    private fun generateCppBridge(bridge: CppBridge, includes: List<String>) {
        val output = buildString {
            appendLine("// Generated from Kotlin Extra library")
            appendLine()
            appendLine("#pragma once")
            appendLine()
            includes.forEach { include ->
                appendLine("#include $include")
            }
            appendLine()
            generateBridgeDeclarations(bridge)
        }
        writeToFile("${cppOutputPath}/${bridge.name}.h", output)
    }

    private fun StringBuilder.generateBridgeDeclarations(cppBridge: CppBridge?) {
        cppBridge ?: return
        appendLine("// -------------- ${cppBridge.name} -----------------")
        cppBridge.functions.forEach { function ->
            appendLine()
            append("inline ${function.returnType.toCppReturnType()} ${cppBridge.name}_${function.name}")
            append('(')
            function.args.forEachIndexed { i, arg ->
                if (arg.isPrimitive) {
                    append("${arg.toCppType()} ${arg.name}")
                } else {
                    append("const ${arg.toCppType()}& ${arg.name}")
                }
                if (i != function.args.lastIndex) {
                    append(", ")
                }
            }
            append(')')
            appendLine()
            appendLine("{")
            appendLine("    // TODO: not implemented!")
            appendLine("}")
        }
    }

    private fun generateCppBridgeJni(bridge: CppBridge) {
        val output = buildString {
            appendLine("// Generated from Kotlin Extra library")
            appendLine()
            appendLine("#include \"${bridge.name}.h\"")
            appendLine("#include \"ExtraJni.h\"")
            appendLine()
            generateBridgeJniDeclarations(bridge)
        }
        writeToFile("${cppOutputPath}/${bridge.name}Jni.cpp", output)
    }

    private fun StringBuilder.generateBridgeJniDeclarations(cppBridge: CppBridge) {
        appendLine("// -------------- ${cppBridge.name} JNI -----------------")
        cppBridge.functions.forEach { function ->
            appendLine()
            append("extern \"C\" JNIEXPORT ${function.returnType.toCppJniReturnType()} Java_${cppBridge.jniPackageName}_${cppBridge.name}_jni_${function.name}")
            append('(')
            append("JNIEnv* env, jobject thiz")
            if (function.args.isNotEmpty()) {
                append(", ")
            }
            function.args.forEachIndexed { i, arg ->
                if (arg.isNested) {
                    append("jobject ${arg.name}ByteBuffer, jbyteArray ${arg.name}ByteArray")
                } else {
                    append("${arg.toCppJniType()} ${arg.name}")
                }
                if (i != function.args.lastIndex) {
                    append(", ")
                }
            }
            append(')')
            appendLine()
            appendLine("{")
            append("    ")
            if (function.returnType.toString() != "kotlin.Unit") {
                append("return ")
            }
            append("${cppBridge.name}_${function.name}(")
            function.args.forEachIndexed { i, arg ->
                appendLine()
                if (arg.isNested) {
                    append("        JniDecode<${cppTypePrefix}${arg.type}>(${arg.name}ByteBuffer, ${arg.name}ByteArray)")
                } else {
                    append("        ${arg.name}")
                }
                if (i != function.args.lastIndex) {
                    appendLine(",")
                } else {
                    appendLine()
                }
            }
            appendLine("    );")
            appendLine("}")
        }
    }

    private fun generateKotlinBridgeJni(bridge: CppBridge) {
        val output = buildString {
            appendLine("// Generated from Kotlin Extra library")
            appendLine()
            appendLine("package ${bridge.packageName}")
            appendLine()
            appendLine("import com.cws.print.JniLibrary")
            appendLine("import com.cws.extra.memory.NativeBuffer")
            appendLine("import java.nio.ByteBuffer")
            bridge.dependencies.forEach { dependency ->
                appendLine("import $dependency")
                if (dependency.isNested) {
                    appendLine("import ${dependency.replaceAfterLast(".", "encode")}")
                }
            }
            appendLine()
            generateKotlinBridgeJniDeclarations(bridge)
        }
        writeToFile("${projectPath}/build/generated/ksp/metadata/jniMain/kotlin/${bridge.packageName.replace('.', '/')}/${bridge.name}.jni.kt", output)
    }

    private fun StringBuilder.generateKotlinBridgeJniDeclarations(bridge: CppBridge) {
        val jniBridge = "${bridge.name}Jni"
        appendLine("object $jniBridge : ${bridge.name} {")
        appendLine()
        appendLine("    init {")
        appendLine("        JniLibrary.load(\"${bridge.libName}\")")
        appendLine("    }")
        appendLine()
        bridge.functions.forEach { function ->
            appendLine("    override fun ${function.name}(")
            function.args.forEach { arg ->
                appendLine("        ${arg.name}: ${arg.type},")
            }
            appendLine("    ) : ${function.returnType} {")
            val params = StringBuilder()
            val jniArgs = StringBuilder()
            function.args.forEachIndexed { i, arg ->
                when {
                    arg.isNativeBuffer -> {
                        params.append("${arg.name}.directBuffer, ${arg.name}.byteArray")
                        jniArgs.append("        ${arg.name}ByteBuffer: ByteBuffer?, ${arg.name}ByteArray: ByteArray?")
                    }
                    arg.isNested -> {
                        val nativeBuffer = "${arg.name}NativeBuffer"
                        appendLine("        val $nativeBuffer = ${arg.name}.encode()")
                        params.append("${nativeBuffer}.directBuffer, ${nativeBuffer}.byteArray")
                        jniArgs.append("        ${arg.name}ByteBuffer: ByteBuffer?, ${arg.name}ByteArray: ByteArray?")
                    }
                    else -> {
                        params.append(arg.name)
                        jniArgs.append("        ${arg.name}: ${arg.type}")
                    }
                }
                if (i != function.args.lastIndex) {
                    params.append(", ")
                    jniArgs.append(", ")
                }
                jniArgs.appendLine()
            }
            if (function.returnType.toString() == "kotlin.Unit") {
                appendLine("        jni_${function.name}($params)")
            } else {
                appendLine("        return jni_${function.name}($params)")
            }
            appendLine("    }")
            appendLine()
            appendLine("    external fun jni_${function.name}(\n$jniArgs\n    ) : ${function.returnType}")
            appendLine()
        }
        appendLine("}")
    }

    private fun copyExtraTypes() {
        val extraTypes = fileTemplateManager.read("ExtraTypes.h")
        writeToFile("${cppOutputPath}/ExtraTypes.h", extraTypes)
    }

    private fun copyExtraJni() {
        val extraJni = fileTemplateManager.read("ExtraJni.h")
        writeToFile("${cppOutputPath}/ExtraJni.h", extraJni)
    }

    private fun writeToFile(filepath: String, output: String) {
        val outputFile = File(filepath)
        logger.w(TAG) { "writeToFile ${outputFile.path}" }
        outputFile.parentFile.mkdirs()
        if (!outputFile.exists()) outputFile.createNewFile()
        outputFile.writeText(output)
    }

    private fun registerAggregatingDeps() {
        val sourceFiles = (
                collectedExtraBridgeEnum.mapNotNull { it.containingFile } +
                collectedExtraBridgeData.mapNotNull { it.containingFile }
        ).distinct().toTypedArray()

        environment.codeGenerator.createNewFile(
            Dependencies(aggregating = true, *sourceFiles),
            "${PACKAGE_CORE}.tracker",
            "ExtraCppOutputTracker",
            "kt",
        ).bufferedWriter().use {
            it.write("// aggregating tracker for Extra C++ output — do not edit\n")
        }
    }

    private fun StringBuilder.generateForwardDeclarations() {
        appendLine("// -------------- Forward declarations -----------------")
        appendLine()
        collectedExtraBridgeEnum.forEach {
            appendLine("enum class ${cppTypePrefix}${it.name} : ${it.parentType};")
        }
        appendLine()
        collectedExtraBridgeData.forEach {
            appendLine("struct ${cppTypePrefix}${it.name};")
        }
    }

    private fun getEnumParentType(enum: KSClassDeclaration): String {
        val rawValue = enum.getAllProperties().find { it.simpleName.asString() == "rawValue" }
        val rawValueType = rawValue?.type?.resolve()?.declaration?.simpleName?.asString()
        return kotlinToCppTypes[rawValueType] ?: "int32_t"
    }

    private fun generateCppEnum(enum: CppBridgeEnum): String {
        return buildString {
            appendLine("enum class ${cppTypePrefix}${enum.name} : ${enum.parentType}")
            appendLine("{")
            enum.entries.forEach { (name, value) -> appendLine("    $name = $value,") }
            appendLine("};")
        }
    }

    private fun generateCppStruct(struct: CppBridgeData): String {
        val typeName = "$cppTypePrefix${struct.name}"
        return buildString {
            // struct definition
            if (struct.isComplex(collectedExtraBridgeDataByName)) {
                appendLine("struct $typeName")
            } else {
                appendLine("EXTRA_STRUCT $typeName")
            }
            appendLine("{")

            // fields
            struct.fields.forEach { field ->
                val cppType = field.toCppType() ?: return@forEach
                if (field.fixedSize != null) appendLine("    $cppType ${field.name}[${field.fixedSize}];")
                else                          appendLine("    $cppType ${field.name};")
            }
            appendLine()

            // SizeOf
            appendLine("    static inline int32_t SizeOf(const $typeName& s)")
            appendLine("    {")
            if (struct.isComplex(collectedExtraBridgeDataByName)) {
                appendLine("        int32_t size = 0;")
                struct.fields.forEach { field ->
                    generateCppSizeOfField(field)?.let { appendLine("        $it") }
                }
                appendLine("        return size;")
            } else {
                appendLine("        return static_cast<int32_t>(sizeof($typeName));")
            }
            appendLine("    }")
            appendLine()

            // Decode
            appendLine("    static inline $typeName Decode(const uint8_t* bytes)")
            appendLine("    {")
            appendLine("        $typeName s;")
            if (struct.isComplex(collectedExtraBridgeDataByName)) {
                appendLine("        const uint8_t* p = bytes;")
                struct.fields.forEach { field ->
                    generateCppDecodeField(field)?.let { appendLine("        $it") }
                }
            } else {
                appendLine("        std::memcpy(&s, bytes, sizeof($typeName));")
            }
            appendLine("        return s;")
            appendLine("    }")
            appendLine()

            // Encode
            appendLine("    static inline void Encode(const $typeName& s, uint8_t* bytes)")
            appendLine("    {")
            if (struct.isComplex(collectedExtraBridgeDataByName)) {
                appendLine("        uint8_t* p = bytes;")
                struct.fields.forEach { field ->
                    generateCppEncodeField(field)?.let { appendLine("        $it") }
                }
            } else {
                appendLine("        std::memcpy(bytes, &s, sizeof($typeName));")
            }
            appendLine("    }")

            appendLine("};")
        }
    }

    private fun generateCppDecodeField(field: Field): String? = when {
        field.isPrimitive -> {
            val cppType = field.toCppType()
            "s.${field.name} = ExtraNextPrimitive<$cppType>(p);"
        }

        field.isVariableLength && field.fixedSize != null -> {
            val elementType = field.toCppStandardType()
            val byteSize = "${field.fixedSize} * sizeof($elementType)"
            "std::memcpy(s.${field.name}, p, $byteSize); p += $byteSize;"
        }

        field.isVariableLength -> {
            if (field.isString) {
                if (field.isStringUtf16) {
                    "s.${field.name} = ExtraNextString16(p);"
                } else {
                    "s.${field.name} = ExtraNextString(p);"
                }
            } else {
                val elementType = field.toCppStandardType()
                "s.${field.name} = ExtraNextArray<$elementType>(p);"
            }
        }

        field.isList || field.isSet -> {
            val param = field.typeName as ParameterizedTypeName
            val elementTypeName = param.typeArguments.first()
            val elementType = elementTypeName.toCppType() ?: return null
            val advanceFn = collectionElementNextFn(elementTypeName)
            "s.${field.name} = ExtraNextList<$elementType>(p, [](const uint8_t*& p) { $advanceFn; });"
        }

        field.isMap -> {
            val param = field.typeName as ParameterizedTypeName
            val keyTypeName   = param.typeArguments[0]
            val valueTypeName = param.typeArguments[1]
            val keyType   = keyTypeName.toCppType()   ?: return null
            val valueType = valueTypeName.toCppType() ?: return null
            val advanceKey   = collectionElementNextFn(keyTypeName)
            val advanceValue = collectionElementNextFn(valueTypeName)
            "s.${field.name} = ExtraNextMap<$keyType, $valueType>(p, [](const uint8_t*& p) { $advanceKey; }, [](const uint8_t*& p) { $advanceValue; });"
        }

        field.isNested -> {
            val nestedType = "$cppTypePrefix${field.type}"
            val nestedStruct = collectedExtraBridgeData.find { it.name == field.type }
            if (nestedStruct?.isComplex(collectedExtraBridgeDataByName) == true) {
                "s.${field.name} = $nestedType::Decode(p); p += $nestedType::SizeOf(s.${field.name});"
            } else {
                "std::memcpy(&s.${field.name}, p, sizeof($nestedType)); p += sizeof($nestedType);"
            }
        }

        else -> null
    }

    private fun generateCppEncodeField(field: Field): String? = when {
        field.isPrimitive -> {
            val cppType = field.toCppType()
            "ExtraPushPrimitive<$cppType>(s.${field.name}, p);"
        }

        field.isVariableLength && field.fixedSize != null -> {
            val elementType = field.toCppStandardType()
            val byteSize = "${field.fixedSize} * sizeof($elementType)"
            "std::memcpy(p, s.${field.name}, $byteSize); p += $byteSize;"
        }

        field.isVariableLength -> {
            if (field.isString) {
                if (field.isStringUtf16) {
                    "ExtraPushString16(s.${field.name}, p);"
                } else {
                    "ExtraPushString(s.${field.name}, p);"
                }
            } else {
                val elementType = field.toCppStandardType()
                "ExtraPushArray<$elementType>(s.${field.name}, p);"
            }
        }

        field.isList || field.isSet -> {
            val param = field.typeName as ParameterizedTypeName
            val elementTypeName = param.typeArguments.first()
            val elementType = elementTypeName.toCppType() ?: return null
            val pushFn = collectionElementPushFn(elementTypeName)
            "ExtraPushList<$elementType>(s.${field.name}, p, [](const uint8_t*& r, uint8_t*& p) { $pushFn; });"
        }

        field.isMap -> {
            val param = field.typeName as ParameterizedTypeName
            val keyTypeName   = param.typeArguments[0]
            val valueTypeName = param.typeArguments[1]
            val keyType   = keyTypeName.toCppType()   ?: return null
            val valueType = valueTypeName.toCppType() ?: return null
            val pushKey   = collectionElementPushFn(keyTypeName)
            val pushValue = collectionElementPushFn(valueTypeName)
            "ExtraPushMap<$keyType, $valueType>(s.${field.name}, p, [](const uint8_t*& r, uint8_t*& p) { $pushKey; }, [](const uint8_t*& r, uint8_t*& p) { $pushValue; });"
        }

        field.isNested -> {
            val nestedType = "$cppTypePrefix${field.type}"
            val nestedStruct = collectedExtraBridgeData.find { it.name == field.type }
            if (nestedStruct?.isComplex(collectedExtraBridgeDataByName) == true) {
                "$nestedType::Encode(s.${field.name}, p); p += $nestedType::SizeOf(s.${field.name});"
            } else {
                "std::memcpy(p, &s.${field.name}, sizeof($nestedType)); p += sizeof($nestedType);"
            }
        }

        else -> null
    }

    private fun generateCppSizeOfField(field: Field): String? = when {
        field.isPrimitive -> {
            val cppType = field.toCppType()
            "size += sizeof($cppType);"
        }

        field.fixedSize != null -> {
            val elementType = field.toCppType()
            "size += ${field.fixedSize} * sizeof($elementType);"
        }

        field.isVariableLength -> {
            val elementType = field.toCppStandardType()
            "size += sizeof(int32_t) + s.${field.name}.length * sizeof($elementType);"
        }

        field.isList || field.isSet -> {
            val param = field.typeName as ParameterizedTypeName
            val elementTypeName = param.typeArguments.first()
            val isPrimitiveElement = elementTypeName is ClassName && elementTypeName.simpleName.isPrimitive
            if (isPrimitiveElement) {
                val elementType = elementTypeName.toCppType()
                "size += sizeof(int32_t) + s.${field.name}.count * sizeof($elementType);"
            } else {
                val advanceFn = collectionElementNextFn(elementTypeName)
                    .replace(Regex("\\bp\\b"), "r")
                """size += sizeof(int32_t);
        { const uint8_t* r = s.${field.name}.data; for (int32_t i = 0; i < s.${field.name}.count; i++) { auto before = r; $advanceFn; size += static_cast<int32_t>(r - before); } }"""
            }
        }

        field.isMap -> {
            val param = field.typeName as ParameterizedTypeName
            val keyTypeName   = param.typeArguments[0]
            val valueTypeName = param.typeArguments[1]
            val keyIsPrimitive   = keyTypeName   is ClassName && keyTypeName.simpleName.isPrimitive
            val valueIsPrimitive = valueTypeName is ClassName && valueTypeName.simpleName.isPrimitive
            if (keyIsPrimitive && valueIsPrimitive) {
                val keyType   = keyTypeName.toCppType()
                val valueType = valueTypeName.toCppType()
                "size += sizeof(int32_t) + s.${field.name}.count * (sizeof($keyType) + sizeof($valueType));"
            } else {
                // variable size elements — iterate raw data
                val advanceKey = collectionElementNextFn(keyTypeName)
                    .replace(Regex("\\bp\\b"), "r")
                val advanceValue = collectionElementNextFn(valueTypeName)
                    .replace(Regex("\\bp\\b"), "r")
                """size += sizeof(int32_t);
        { const uint8_t* r = s.${field.name}.data; for (int32_t i = 0; i < s.${field.name}.count; i++) { auto before = r; $advanceKey; $advanceValue; size += static_cast<int32_t>(r - before); } }"""
            }
        }

        field.isNested -> {
            val nestedType = "$cppTypePrefix${field.type}"
            val nestedStruct = collectedExtraBridgeData.find { it.name == field.type }
            if (nestedStruct?.isComplex(collectedExtraBridgeDataByName) == true) {
                "size += $nestedType::SizeOf(s.${field.name});"
            } else {
                "size += sizeof($nestedType);"
            }
        }

        else -> null
    }

    private fun collectionElementNextFn(typeName: TypeName): String {
        val nonNull = when (typeName) {
            is ParameterizedTypeName -> typeName.copy(nullable = false)
            is ClassName             -> typeName.copy(nullable = false)
            else                     -> typeName
        }

        return when (nonNull) {
            is ClassName -> when (nonNull.simpleName) {
                "String"                              -> "ExtraNextString(p)"
                "Boolean"                             -> "ExtraNextPrimitive<bool>(p)"
                "Byte"                                -> "ExtraNextPrimitive<int8_t>(p)"
                "Short"                               -> "ExtraNextPrimitive<int16_t>(p)"
                "Char"                                -> "ExtraNextPrimitive<uint16_t>(p)"
                "Int"                                 -> "ExtraNextPrimitive<int32_t>(p)"
                "Long"                                -> "ExtraNextPrimitive<int64_t>(p)"
                "Float"                               -> "ExtraNextPrimitive<float>(p)"
                "Double"                              -> "ExtraNextPrimitive<double>(p)"
                else -> {
                    val nestedType = "$cppTypePrefix${nonNull.simpleName}"
                    val nestedStruct = collectedExtraBridgeData.find { it.name == nonNull.simpleName }
                    if (nestedStruct?.isComplex(collectedExtraBridgeDataByName) == true) {
                        "{ auto tmp = $nestedType::Decode(p); p += $nestedType::SizeOf(tmp); }"
                    } else {
                        "p += sizeof($nestedType)"
                    }
                }
            }

            is ParameterizedTypeName -> when {
                nonNull.rawType.simpleName.isList || nonNull.rawType.simpleName.isSet -> {
                    val inner = collectionElementNextFn(nonNull.typeArguments.first())
                    "{ int32_t c = ExtraNextPrimitive<int32_t>(p); for (int32_t i = 0; i < c; i++) { $inner; } }"
                }
                nonNull.rawType.simpleName.isMap -> {
                    val advKey   = collectionElementNextFn(nonNull.typeArguments[0])
                    val advValue = collectionElementNextFn(nonNull.typeArguments[1])
                    "{ int32_t c = ExtraNextPrimitive<int32_t>(p); for (int32_t i = 0; i < c; i++) { $advKey; $advValue; } }"
                }
                else -> "/* unsupported */"
            }

            else -> "/* unsupported */"
        }
    }

    private fun collectionElementPushFn(typeName: TypeName): String {
        val nonNull = when (typeName) {
            is ParameterizedTypeName -> typeName.copy(nullable = false)
            is ClassName             -> typeName.copy(nullable = false)
            else                     -> typeName
        }
        return when (nonNull) {
            is ClassName -> when (nonNull.simpleName) {
                "String"   -> "ExtraPushString(ExtraNextString(r), p)"
                "Boolean"  -> "ExtraPushPrimitive<bool>(ExtraNextPrimitive<bool>(r), p)"
                "Byte"     -> "ExtraPushPrimitive<int8_t>(ExtraNextPrimitive<int8_t>(r), p)"
                "Short"    -> "ExtraPushPrimitive<int16_t>(ExtraNextPrimitive<int16_t>(r), p)"
                "Char"     -> "ExtraPushPrimitive<uint16_t>(ExtraNextPrimitive<uint16_t>(r), p)"
                "Int"      -> "ExtraPushPrimitive<int32_t>(ExtraNextPrimitive<int32_t>(r), p)"
                "Long"     -> "ExtraPushPrimitive<int64_t>(ExtraNextPrimitive<int64_t>(r), p)"
                "Float"    -> "ExtraPushPrimitive<float>(ExtraNextPrimitive<float>(r), p)"
                "Double"   -> "ExtraPushPrimitive<double>(ExtraNextPrimitive<double>(r), p)"
                else -> {
                    val nestedType = "$cppTypePrefix${nonNull.simpleName}"
                    val nestedStruct = collectedExtraBridgeData.find { it.name == nonNull.simpleName }
                    if (nestedStruct?.isComplex(collectedExtraBridgeDataByName) == true) {
                        "{ auto tmp = $nestedType::Decode(r); $nestedType::Encode(tmp, p); p += $nestedType::SizeOf(tmp); }"
                    } else {
                        "{ std::memcpy(p, r, sizeof($nestedType)); p += sizeof($nestedType); r += sizeof($nestedType); }"
                    }
                }
            }
            else -> "/* unsupported */"
        }
    }

    private fun TypeName.toCppReturnType(): String? {
        return if (toString() == "kotlin.Unit") "void" else toCppType()
    }

    private fun TypeName.toCppJniReturnType(): String? {
        return if (toString() == "kotlin.Unit") "void" else toCppJniType()
    }

    private fun Field.toCppStandardType(): String = when (type) {
        "Boolean"     -> "bool"
        "Byte"        -> "int8_t"
        "Short"       -> "int16_t"
        "Int"         -> "int32_t"
        "Long"        -> "int64_t"
        "Float"       -> "float"
        "Double"      -> "double"
        "String"      -> if (isStringUtf16) "uint16_t" else "char"
        "ByteArray"   -> "uint8_t"
        "ShortArray"  -> "int16_t"
        "CharArray"   -> "uint16_t"
        "IntArray"    -> "int32_t"
        "LongArray"   -> "int64_t"
        "FloatArray"  -> "float"
        "DoubleArray" -> "double"
        else -> "uint8_t"
    }

    private fun String.toCppPrimitiveType() = kotlinToCppTypes[this]

    private fun String.toCppJniType() = kotlinToJniTypes[this] ?: "jobject"

    private fun String.toCppType(field: Field): String = when (this) {
        "Boolean"     -> "bool"
        "Byte"        -> "int8_t"
        "Short"       -> "int16_t"
        "Int"         -> "int32_t"
        "Long"        -> "int64_t"
        "Float"       -> "float"
        "Double"      -> "double"
        "String"      -> if (field.isStringUtf16) {
            if (field.fixedSize != null) "uint16_t" else "ExtraString16"
        } else {
            if (field.fixedSize != null) "char" else "ExtraString"
        }
        "ByteArray"   -> if (field.fixedSize != null) "uint8_t"  else "ExtraByteArray"
        "ShortArray"  -> if (field.fixedSize != null) "int16_t"  else "ExtraShortArray"
        "CharArray"   -> if (field.fixedSize != null) "uint16_t" else "ExtraChar16Array"
        "IntArray"    -> if (field.fixedSize != null) "int32_t"  else "ExtraIntArray"
        "LongArray"   -> if (field.fixedSize != null) "int64_t"  else "ExtraLongArray"
        "FloatArray"  -> if (field.fixedSize != null) "float"    else "ExtraFloatArray"
        "DoubleArray" -> if (field.fixedSize != null) "double"   else "ExtraDoubleArray"
        else          -> "$cppTypePrefix$this"
    }

    private fun Field.toCppType(): String? = when {
        isCollection -> typeName.toCppType()
        else         -> type.toCppType(this)
    }

    private fun Field.toCppJniType(): String = type.toCppJniType()

    private fun TypeName.toCppType(): String? {
        val nonNull = when (this) {
            is ParameterizedTypeName -> copy(nullable = false)
            is ClassName             -> copy(nullable = false)
            else                     -> this
        }
        return when (nonNull) {
            is ClassName -> nonNull.simpleName.toCppPrimitiveType()
                ?: when (nonNull.simpleName) {
                    "String"      -> "ExtraString"
                    "ByteArray"   -> "ExtraByteArray"
                    "ShortArray"  -> "ExtraShortArray"
                    "CharArray"   -> "ExtraChar16Array"
                    "IntArray"    -> "ExtraIntArray"
                    "LongArray"   -> "ExtraLongArray"
                    "FloatArray"  -> "ExtraFloatArray"
                    "DoubleArray" -> "ExtraDoubleArray"
                    else          -> "$cppTypePrefix${nonNull.simpleName}"
                }
            is ParameterizedTypeName -> when {
                nonNull.rawType.simpleName.isList || nonNull.rawType.simpleName.isSet -> {
                    val element = nonNull.typeArguments.first().toCppType() ?: return null
                    "ExtraList<$element>"
                }
                nonNull.rawType.simpleName.isMap -> {
                    val key   = nonNull.typeArguments[0].toCppType() ?: return null
                    val value = nonNull.typeArguments[1].toCppType() ?: return null
                    "ExtraMap<$key, $value>"
                }
                else -> null
            }
            else -> null
        }
    }

    private fun TypeName.toCppJniType(): String? {
        val nonNull = when (this) {
            is ParameterizedTypeName -> copy(nullable = false)
            is ClassName             -> copy(nullable = false)
            else                     -> this
        }

        return when (nonNull) {
            is ClassName -> nonNull.simpleName.toCppJniType()
            else -> "jobject"
        }
    }

    private fun topologicallySorted(structs: List<CppBridgeData>): List<CppBridgeData> {
        val nameToStruct = structs.associateBy { it.name }
        val visited = mutableSetOf<String>()
        val result = mutableListOf<CppBridgeData>()

        fun visit(struct: CppBridgeData) {
            if (struct.name in visited) return
            visited += struct.name
            struct.dependencies
                .mapNotNull { nameToStruct[it] }
                .forEach { visit(it) }
            result += struct
        }

        structs.forEach { visit(it) }
        return result
    }
}