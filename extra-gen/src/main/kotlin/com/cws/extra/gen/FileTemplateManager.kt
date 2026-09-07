package com.cws.extra.gen

class FileTemplateManager(private val logger: ExtraLogger) {

    companion object {
        private const val TAG = "FileTemplateManager"
    }

    fun read(name: String): String {
        val file = "templates/$name"
        logger.w(TAG) { "readTemplate: $file" }
        return FileGenerator::class.java.classLoader
            .getResourceAsStream(file)
            ?.bufferedReader()
            ?.readText()
            ?: error("File not found $file")
    }

}