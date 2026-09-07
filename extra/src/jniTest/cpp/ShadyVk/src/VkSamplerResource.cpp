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
#include "VkSamplerResource.hpp"

#include "VkBindingLayout.hpp"
#include "VkContext.hpp"
#include "VkDescriptors.hpp"

VkSamplerResource* VkSamplerResource_create(VkContext* context, VkSamplerInfo* info) {
    return new VkSamplerResource(context, *info);
}

void VkSamplerResource_destroy(VkSamplerResource* sampler_resource) {
    delete sampler_resource;
}

void VkSamplerResource_setInfo(VkSamplerResource* sampler_resource, VkSamplerInfo* info) {
    sampler_resource->info = *info;
}

VkSamplerResource::VkSamplerResource(VkContext* context, const VkSamplerInfo &info)
: context(context), info(info) {
    VkSamplerCreateInfo createInfo = {
            .sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
            .magFilter = info.magFilter,
            .minFilter = info.minFilter,
            .mipmapMode = info.mipmapMode,
            .addressModeU = info.addressModeU,
            .addressModeV = info.addressModeV,
            .addressModeW = info.addressModeW,
            .mipLodBias = info.mipLodBias,
            .anisotropyEnable = info.enableAnisotropy,
            .maxAnisotropy = info.maxAnisotropy,
            .compareEnable = info.enableCompare,
            .compareOp = info.compareOp,
            .minLod = info.minLod,
            .maxLod = info.maxLod,
            .borderColor = info.borderColor,
            .unnormalizedCoordinates = info.unnormalizedCoordinates,
    };
    VK_CHECK(vkCreateSampler(context->device, &createInfo, VK_CALLBACKS, &sampler));
    VK_DEBUG_NAME(context->device, VK_OBJECT_TYPE_SAMPLER, sampler, info.name);
}

VkSamplerResource::~VkSamplerResource() {
    if (sampler) {
        vkDestroySampler(context->device, sampler, VK_CALLBACKS);
        sampler = nullptr;
    }
}

void VkSamplerResource::updateBinding(u32 frame) {
    VkBinding* binding = info.binding;
    VkBindingLayout* binding_layout = info.binding_layout;
    VkDescriptorSet set = VkDescriptors::getSet(binding_layout, frame);

    if (binding && binding_layout && set) {
        VkDescriptorImageInfo imageInfo = {
            .sampler = sampler,
            .imageView = VK_NULL_HANDLE,
            .imageLayout = VK_IMAGE_LAYOUT_GENERAL,
        };

        VkWriteDescriptorSet descriptorWrite = {
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .dstSet = set,
            .dstBinding = binding->binding,
            .dstArrayElement = 0,
            .descriptorCount = binding->count,
            .descriptorType = (VkDescriptorType) binding->type,
            .pImageInfo = &imageInfo,
        };

        vkUpdateDescriptorSets(context->device, 1, &descriptorWrite, 0, nullptr);
    }
}