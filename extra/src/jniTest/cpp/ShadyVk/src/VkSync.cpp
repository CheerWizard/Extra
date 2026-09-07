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
#include "VkSync.hpp"
#include "VkContext.hpp"

VkFenceResource::VkFenceResource(VkDevice device, const char* name, bool signaled) {
    VkFenceCreateInfo createInfo = { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };
    if (signaled) {
        createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    }
    VK_CHECK(vkCreateFence(device, &createInfo, VK_CALLBACKS, &fence));
    this->device = device;
    VK_DEBUG_NAME_FORMAT(device, VK_OBJECT_TYPE_COMMAND_BUFFER, fence, "VkFence-" << name);
}

VkFenceResource::~VkFenceResource() {
    if (fence) {
        vkDestroyFence(device, fence, VK_CALLBACKS);
        fence = nullptr;
    }
}

void VkFenceResource::wait(u64 timeout) {
    VK_CHECK(vkWaitForFences(device, 1, &fence, VK_TRUE, timeout));
}

void VkFenceResource::reset() {
    VK_CHECK(vkResetFences(device, 1, &fence));
}

VkSemaphoreResource::VkSemaphoreResource(VkDevice device, const char* name) {
    VkSemaphoreCreateInfo createInfo = { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO };
    VK_CHECK(vkCreateSemaphore(device, &createInfo, VK_CALLBACKS, &semaphore));
    VK_DEBUG_NAME_FORMAT(device, VK_OBJECT_TYPE_COMMAND_BUFFER, semaphore, "VkSemaphore-" << name);
}

VkSemaphoreResource::~VkSemaphoreResource() {
    if (semaphore) {
        vkDestroySemaphore(device, semaphore, VK_CALLBACKS);
        semaphore = nullptr;
    }
}
