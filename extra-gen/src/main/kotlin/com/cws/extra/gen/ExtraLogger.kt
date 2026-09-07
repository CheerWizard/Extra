package com.cws.extra.gen

import com.google.devtools.ksp.processing.KSPLogger
import com.google.devtools.ksp.symbol.KSNode

enum class ExtraLogLevel {
    NONE,
    INFO,
    WARNING,
    ERROR,
}

fun String?.toExtraLogLevel() = when (this?.lowercase()) {
    "info" -> ExtraLogLevel.INFO
    "warning" -> ExtraLogLevel.WARNING
    "error" -> ExtraLogLevel.ERROR
    else -> ExtraLogLevel.NONE
}

class ExtraLogger(
    val logger: KSPLogger,
    val logLevel: ExtraLogLevel,
) {

    inline fun i(tag: String, symbol: KSNode? = null, message: () -> String) = log(ExtraLogLevel.INFO, tag, null, symbol, message)
    inline fun w(tag: String, symbol: KSNode? = null, message: () -> String) = log(ExtraLogLevel.WARNING, tag, null, symbol, message)
    inline fun e(tag: String, symbol: KSNode? = null, exception: Exception? = null, message: () -> String) = log(ExtraLogLevel.ERROR, tag, exception, symbol, message)

    inline fun log(level: ExtraLogLevel, tag: String, exception: Exception? = null, symbol: KSNode? = null, message: () -> String) {
        if (logLevel != ExtraLogLevel.NONE && level >= logLevel) {
            when (level) {
                ExtraLogLevel.INFO -> logger.info("${tag}: ${message()}", symbol)
                ExtraLogLevel.WARNING -> logger.warn("${tag}: ${message()}", symbol)
                ExtraLogLevel.ERROR -> logger.error("${tag}: ${message()}", symbol)
                else -> {}
            }
            if (exception != null) {
                logger.exception(exception)
            }
        }
    }

}