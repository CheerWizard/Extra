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
#include "VulkanAllocator.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"
#pragma clang diagnostic pop

#include "../core/logger.hpp"

VKAPI_ATTR void* VKAPI_CALL vk_allocate(void* userData, size_t size, size_t alignment, VkSystemAllocationScope scope) {
    return static_cast<VulkanAllocator*>(userData)->allocate(size, alignment, scope);
}

VKAPI_ATTR void VKAPI_CALL vk_free(void* userData, void* memory) {
    static_cast<VulkanAllocator*>(userData)->free(memory);
}

VKAPI_ATTR void* VKAPI_CALL vk_reallocate(void* userData, void* oldMemory, size_t size, size_t alignment, VkSystemAllocationScope scope) {
    return static_cast<VulkanAllocator*>(userData)->reallocate(oldMemory, size, alignment, scope);
}

VKAPI_ATTR void VKAPI_CALL vk_allocate_notification(void* userData, size_t size, VkInternalAllocationType type, VkSystemAllocationScope scope) {
    static_cast<VulkanAllocator*>(userData)->allocateNotification(size, type, scope);
}

VKAPI_ATTR void VKAPI_CALL vk_free_notification(void* userData, size_t size, VkInternalAllocationType type, VkSystemAllocationScope scope) {
    static_cast<VulkanAllocator*>(userData)->freeNotification(size, type, scope);
}

VulkanAllocator::VulkanAllocator() {
    callbacks.pUserData = this;
    callbacks.pfnAllocation = vk_allocate;
    callbacks.pfnFree = vk_free;
    callbacks.pfnReallocation = vk_reallocate;
    callbacks.pfnInternalAllocation = vk_allocate_notification;
    callbacks.pfnInternalFree = vk_free_notification;
}

VulkanAllocator& VulkanAllocator::getInstance() {
    static VulkanAllocator instance;
    return instance;
}

void VulkanAllocator::New(VkInstance instance, VkPhysicalDevice physicalDevice, VkDevice device) {
    VmaVulkanFunctions functions = {
        .vkGetInstanceProcAddr = vkGetInstanceProcAddr,
        .vkGetDeviceProcAddr = vkGetDeviceProcAddr,
    };
    VmaAllocatorCreateInfo createInfo = {
        .physicalDevice = physicalDevice,
        .device = device,
        .pAllocationCallbacks = &callbacks,
        .pVulkanFunctions = &functions,
        .instance = instance,
        .vulkanApiVersion = VK_API_VERSION_1_3,
    };
    vmaCreateAllocator(&createInfo, &allocator);
}

void VulkanAllocator::Delete() const {
    vmaDestroyAllocator(allocator);
}

void* VulkanAllocator::allocate(size_t size, size_t alignment, VkSystemAllocationScope scope) {
    LOG_INFO(TAG, "allocate: size=%d, alignment=%d, scope=%d", size, alignment, scope);

    if (alignment < sizeof(void*)) {
        alignment = sizeof(void*);
    }

    // Overallocate: extra space for alignment + to store original pointer
    size_t total_size = size + alignment - 1 + sizeof(void*);
    void *original = malloc(total_size);
    if (!original) return nullptr;

    // Calculate aligned address within the allocated block
    uintptr_t raw = (uintptr_t)original + sizeof(void*);
    uintptr_t aligned = (raw + alignment - 1) & ~(uintptr_t)(alignment - 1);

    // Store original pointer just before aligned pointer
    ((void**)aligned)[-1] = original;

    return (void*) aligned;
}

void VulkanAllocator::free(void *address) {
    LOG_INFO(TAG, "free: %p", address);
    if (address) {
        // Retrieve original pointer and free
        ::free(((void**)address)[-1]);
    }
}

void* VulkanAllocator::VulkanAllocator::reallocate(void *oldAddress, size_t size, size_t alignment, VkSystemAllocationScope scope) {
    LOG_INFO(TAG, "reallocate: size=%d, alignment=%d, scope=%d", size, alignment, scope);
    void* newAddress = allocate(size, alignment, scope);
    memcpy(newAddress, oldAddress, size);
    free(oldAddress);
    return newAddress;
}

void VulkanAllocator::allocateNotification(size_t size, VkInternalAllocationType type, VkSystemAllocationScope scope) {
    LOG_INFO(TAG, "allocateNotification: size=%d, type=%d, scope=%d", size, type, scope);
}

void VulkanAllocator::freeNotification(size_t size, VkInternalAllocationType type, VkSystemAllocationScope scope) {
    LOG_INFO(TAG, "freeNotification: size=%d, type=%d, scope=%d", size, type, scope);
}