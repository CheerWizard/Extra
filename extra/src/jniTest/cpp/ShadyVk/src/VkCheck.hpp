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
#include "../api/ResultBridge.h"
#include "../core/logger.hpp"

#include <volk.h>

#include <sstream>
#include <ostream>

#define VK_CHECK(fn)                                        \
do {                                                        \
    VkResult _r = (fn);                                    \
    if (_r != VK_SUCCESS) {                                \
        LOG_ERROR("VK call failed: %s (%d) at %s:%d", #fn, _r, __FILE__, __LINE__);                  \
        ResultBridge_send(_r);                             \
    }                                                       \
} while (0)

#define VK_DEBUG_NAME(device, type, handle, name)                     \
do {                                                                        \
    VkDebugUtilsObjectNameInfoEXT nameInfo {                                \
        .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,        \
        .objectType = type,                                           \
        .objectHandle = reinterpret_cast<uint64_t>(handle),                 \
        .pObjectName = name,                                                \
    };                                                                      \
    vkSetDebugUtilsObjectNameEXT(device, &nameInfo);                        \
} while (0)

#define VK_DEBUG_NAME_FORMAT(device, type, handle, ...)                     \
do {                                                                        \
    std::ostringstream ss;                                                  \
    ss << __VA_ARGS__;                                                      \
    auto debugName = ss.str();                                              \
    VK_DEBUG_NAME(device, type, handle, debugName.c_str());                 \
} while (0)

#endif //VK_CHECK_HPP
