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