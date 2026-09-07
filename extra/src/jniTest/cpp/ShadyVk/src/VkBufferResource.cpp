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
#include "VkDescriptors.hpp"
#include "VkBufferResource.hpp"

#include "VkContext.hpp"

VkBufferResource* VkBufferResource_create(VkContext* context, VkBufferInfo* info) {
    return new VkBufferResource(context, *info);
}

void VkBufferResource_destroy(VkBufferResource* buffer_resource) {
    delete buffer_resource;
}

void VkBufferResource_setInfo(VkBufferResource* buffer_resource, VkBufferInfo* info) {
    buffer_resource->info = *info;
}

void* VkBufferResource_map(VkBufferResource* buffer_resource, u32 frame) {
    return buffer_resource->map(frame);
}

void VkBufferResource_unmap(VkBufferResource* buffer_resource) {
    buffer_resource->unmap();
}

VkBufferResource::VkBufferResource(
    VkContext* context,
    const VkBufferInfo& info
) : context(context), info(info) {

    u32 frameCount = context->info.frameCount;
    if (info.isStatic) {
        frameCount = 1;
    }

    if (info.usages & VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT) {
        u32 minAlignment = context->properties.limits.minUniformBufferOffsetAlignment;
        frameStride = (info.size + minAlignment - 1) & ~(minAlignment - 1);
    }
    else if (info.usages & VK_BUFFER_USAGE_STORAGE_BUFFER_BIT) {
        u32 minAlignment = context->properties.limits.minStorageBufferOffsetAlignment;
        frameStride = (info.size + minAlignment - 1) & ~(minAlignment - 1);
    }
    else {
        frameStride = info.size;
    }

    VkBufferCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .size = frameStride * frameCount,
        .usage = info.usages,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    };

    VmaMemoryUsage memoryUsage;

    switch (info.memoryType) {
        case VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT:
            memoryUsage = VMA_MEMORY_USAGE_AUTO_PREFER_HOST;
            break;
        case VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT:
            memoryUsage = VMA_MEMORY_USAGE_AUTO_PREFER_DEVICE;
            break;
        default:
            memoryUsage = VMA_MEMORY_USAGE_AUTO;
            break;
    }

    VmaAllocationCreateInfo allocInfo = {
            .usage = memoryUsage
    };

    VK_CHECK(vmaCreateBuffer(VK_ALLOCATOR, &createInfo, &allocInfo, &buffer, &allocation, nullptr));
    VK_DEBUG_NAME(context->device, VK_OBJECT_TYPE_BUFFER, buffer, info.name);
}

VkBufferResource::~VkBufferResource() {
    unmap();
    if (buffer) {
        vmaDestroyBuffer(VK_ALLOCATOR, buffer, allocation);
        buffer = nullptr;
    }
}

void* VkBufferResource::map(u32 frame) {
    VK_CHECK(vmaMapMemory(VK_ALLOCATOR, allocation, &mapped));
    ASSERT(!mapped, TAG, "Failed to map VkBufferResource memory");

    u32 actualFrame = frame;
    if (info.isStatic) {
        actualFrame = 1;
    }

    return static_cast<char*>(mapped) + actualFrame * info.size;
}

void VkBufferResource::unmap() {
    if (mapped) {
        vmaUnmapMemory(VK_ALLOCATOR, allocation);
        mapped = nullptr;
    }
}

void VkBufferResource::resize(size_t size) {
    info.size = size;
    this->~VkBufferResource();
    new (this) VkBufferResource(context, info);
}

void VkBufferResource::updateBinding(u32 frame) {
    VkBinding* binding = info.binding;
    VkBindingLayout* binding_layout = info.binding_layout;
    VkDescriptorSet set = VkDescriptors::getSet(binding_layout, frame);

    u32 actualFrame = frame;
    if (info.isStatic) {
        actualFrame = 0;
    }

    if (binding && binding_layout && set) {
        VkDescriptorBufferInfo bufferInfo = {
            .buffer = buffer,
            .offset = info.size * actualFrame,
            .range = info.size,
        };

        VkWriteDescriptorSet descriptorWrite = {
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .dstSet = set,
            .dstBinding = binding->binding,
            .dstArrayElement = 0,
            .descriptorCount = binding->count,
            .descriptorType = (VkDescriptorType) binding->type,
            .pBufferInfo = &bufferInfo,
        };

        vkUpdateDescriptorSets(context->device, 1, &descriptorWrite, 0, nullptr);
    }
}
