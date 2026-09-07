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
#include "VkDeviceQueue.hpp"

void VkDeviceQueue_reset(VkDeviceQueue* device_queue) {
    device_queue->reset();
}

VkDeviceQueue::VkDeviceQueue(VkDevice device, const char* name, u32 familyIndex) {
    vkGetDeviceQueue(device, familyIndex, 0, &queue);
    VkCommandPoolCreateInfo poolInfo = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
            .queueFamilyIndex = familyIndex,
    };
    VK_CHECK(vkCreateCommandPool(device, &poolInfo, VK_CALLBACKS, &pool));

    char debugName[64];
    sprintf(debugName, "VkCommandPool-%s", name);
    VK_DEBUG_NAME(device, VK_OBJECT_TYPE_COMMAND_POOL, pool, debugName);
}

VkDeviceQueue::~VkDeviceQueue() {
    queue = nullptr;
    if (pool) {
        vkDestroyCommandPool(device, pool, VK_CALLBACKS);
        pool = nullptr;
    }
}

void VkDeviceQueue::reset() {
    VK_CHECK(vkResetCommandPool(device, pool, 0));
}