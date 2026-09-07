package com.cws.extra.gen

import com.google.devtools.ksp.symbol.KSFunctionDeclaration
import com.squareup.kotlinpoet.TypeName
import com.squareup.kotlinpoet.ksp.toTypeName

data class Function(
    val name: String,
    val returnType: TypeName,
    val args: List<Field>,
)

fun KSFunctionDeclaration.createFunction(): Function? {
    val name = simpleName.asString()
    val returnType = returnType?.toTypeName() ?: return null
    val args = parameters.mapNotNull { it.createField(packageName.asString()) }

    return Function(
        name = name,
        returnType = returnType,
        args = args,
    )
}
