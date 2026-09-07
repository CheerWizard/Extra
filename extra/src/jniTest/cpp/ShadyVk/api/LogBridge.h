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
#ifndef LOG_BRIDGE_H
#define LOG_BRIDGE_H

typedef void (*LogBridgeFn) (int, const char*, const char*, const char*);

typedef enum LogLevel {
    LOG_LEVEL_NONE = 0,
    LOG_LEVEL_VERBOSE,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_FATAL,
} LogLevel;

#ifdef __cplusplus
extern "C" {
#endif

    void LogBridge_init(LogBridgeFn callback);
    void LogBridge_log(LogLevel level, const char* tag, const char* message, const char* exceptionMessage);

#ifdef __cplusplus
}
#endif

#endif //LOG_BRIDGE_H