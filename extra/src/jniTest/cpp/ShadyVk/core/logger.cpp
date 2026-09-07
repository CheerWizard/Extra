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
#include "logger.hpp"

#include <thread>

Logger::Logger() {
    std::thread thread([this]() { runLoop(); });
    thread.detach();
}

Logger::~Logger() {
    running = false;
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::runLoop() {
    running = true;
    // todo: potentially insecure for CPU usage, maybe add small sleep duration
    while (running) {
        Log log;
        logQueue.pop(log);
        LogBridge_log(log.level, log.tag.data(), log.message.data(), log.exceptionMessage.data());
    }
}