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
#include <vulkan/vulkan_core.h>
#include "vk_mem_alloc.h"

#define VK_CALLBACKS &VulkanAllocator::getInstance().callbacks
#define VK_ALLOCATOR VulkanAllocator::getInstance().allocator

struct VulkanAllocator {

    VkAllocationCallbacks callbacks = {};
    VmaAllocator allocator = {};

    VulkanAllocator();

    static VulkanAllocator& getInstance();

    void New(VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device);
    void Delete() const;

    void* allocate(size_t size, size_t alignment, VkSystemAllocationScope scope);
    void free(void* address);
    void* reallocate(void* oldAddress, size_t size, size_t alignment, VkSystemAllocationScope scope);
    void allocateNotification(size_t size, VkInternalAllocationType type, VkSystemAllocationScope scope);
    void freeNotification(size_t size, VkInternalAllocationType type, VkSystemAllocationScope scope);

private:
    static constexpr auto TAG = "VulkanAllocator";
};

#endif //VULKANALLOCATOR_HPP