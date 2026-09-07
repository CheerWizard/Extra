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
#include "thread_pool.hpp"
#include "../api/LogBridge.h"

#define ASSERT(condition, tag, msg, ...) \
if (!(condition)) { \
    LOG_ASSERT(tag, msg, ##__VA_ARGS__); \
}

#ifdef DEBUG

#ifdef ANDROID

#define LOG_VERBOSE(tag, msg, ...) Logger::getInstance().log(LOG_LEVEL_VERBOSE, tag, msg, 0, ##__VA_ARGS__)
#define LOG_INFO(tag, msg, ...) Logger::getInstance().log(LOG_LEVEL_INFO, tag, msg, 0, ##__VA_ARGS__)
#define LOG_DEBUG(tag, msg, ...) Logger::getInstance().log(LOG_LEVEL_DEBUG, tag, msg, 0, ##__VA_ARGS__)
#define LOG_WARNING(tag, msg, ...) Logger::getInstance().log(LOG_LEVEL_WARNING, tag, msg, 0, ##__VA_ARGS__)
#define LOG_ERROR(tag, msg, ...) Logger::getInstance().log(LOG_LEVEL_ERROR, tag, msg, 0, ##__VA_ARGS__)
#define LOG_ASSERT(tag, msg, ...) Logger::getInstance().log(LOG_LEVEL_FATAL, tag, msg, 0, ##__VA_ARGS__)

#else

#define LOG_VERBOSE(tag, msg, ...) Logger::getInstance().log(LOG_LEVEL_VERBOSE, tag, msg, ##__VA_ARGS__)
#define LOG_INFO(tag, msg, ...) Logger::getInstance().log(LOG_LEVEL_INFO, tag, msg, ##__VA_ARGS__)
#define LOG_DEBUG(tag, msg, ...) Logger::getInstance().log(LOG_LEVEL_DEBUG, tag, msg, ##__VA_ARGS__)
#define LOG_WARNING(tag, msg, ...) Logger::getInstance().log(LOG_LEVEL_WARNING, tag, msg, ##__VA_ARGS__)
#define LOG_ERROR(tag, msg, ...) Logger::getInstance().log(LOG_LEVEL_ERROR, tag, msg, ##__VA_ARGS__)
#define LOG_ASSERT(tag, msg, ...) Logger::getInstance().log(LOG_LEVEL_FATAL, tag, msg, ##__VA_ARGS__)

#endif

#else

#define LOG_VERBOSE(tag,  msg, ...)
#define LOG_INFO(tag, msg, ...)
#define LOG_DEBUG(tag, msg, ...)
#define LOG_WARNING(tag, msg, ...)
#define LOG_ERROR(tag, msg, ...)
#define LOG_ASSERT(tag, msg, ...) std::abort()

#endif

using LogBuffer = std::array<char, 256>;

struct Log {
    LogLevel level;
    LogBuffer tag;
    LogBuffer message;
    LogBuffer exceptionMessage;
};

struct Logger {

    Logger();
    ~Logger();

    static Logger& getInstance();

    template<typename... Args>
    void log(
        LogLevel level,
        const char* tag,
        const char* msg,
        Args &&... args
    );

private:
    void runLoop();

    ConcurrentQueue<Log, 100> logQueue;
    std::mutex mutex;
    bool running = false;
};

template<typename ... Args>
void Logger::log(
    LogLevel level,
    const char* tag,
    const char* msg,
    Args &&... args
) {
    std::lock_guard lock(mutex);
    Log log;
#ifdef ANDROID
    std::snprintf(log.message.data(), log.message.size(), "%s", msg, args...);
    std::snprintf(log.tag.data(), log.tag.size(), "%s", tag);
#else
    std::snprintf(log.message.data(), log.message.size(), msg, args...);
    std::snprintf(log.tag.data(), log.tag.size(), tag);
#endif
    log.level = level;
    if (level >= LOG_LEVEL_ERROR) {
        log.exceptionMessage = log.message;
    }
    logQueue.push(log);
}

#endif //LOGGER_HPP
