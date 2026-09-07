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
#include "VkCommon.hpp"

struct VkQueueFamilyIndices {
    u32 graphics = 0;
    u32 present = 0;
    u32 compute = 0;
    u32 transfer = 0;
};

struct VkDeviceQueue {
    VkDevice device = nullptr;
    VkQueue queue = nullptr;
    VkCommandPool pool = nullptr;
    u32 family_index = 0;

    VkDeviceQueue(VkDevice device, const char* name, u32 family_index);
    ~VkDeviceQueue();

    void reset();
};

#endif //CATCH_VKDEVICEQUEUE_HPP
