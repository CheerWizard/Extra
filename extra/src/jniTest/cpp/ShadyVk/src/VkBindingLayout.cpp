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
#include "VkBindingLayout.hpp"

#include "VkContext.hpp"
#include "VkDescriptors.hpp"

VkBindingLayout* VkBindingLayout_create(VkContext* context, VkBindingInfo* info) {
    return new VkBindingLayout(context->device, *info);
}

void VkBindingLayout_destroy(VkBindingLayout* layout) {
    delete layout;
}

void VkBindingLayout_setInfo(VkBindingLayout* layout, VkBindingInfo* info) {
    layout->update(*info);
}

VkBindingLayout::VkBindingLayout(VkDevice device, const VkBindingInfo &info) : device(device), info(info) {
    std::vector<VkDescriptorSetLayoutBinding> layoutBindings;
    layoutBindings.resize(info.bindingsCount);

    for (u32 i = 0 ; i < info.bindingsCount ; i++) {
        const auto& binding = info.bindings[i];
        layoutBindings[i] = {
            .binding = binding.binding,
            .descriptorType = (VkDescriptorType) binding.type,
            .descriptorCount = binding.count,
            .stageFlags = (VkShaderStageFlags) binding.shader_stages,
            .pImmutableSamplers = nullptr,
        };
        if (binding.type == VK_BINDING_TYPE_UNIFORM_BUFFER_DYNAMIC || binding.type == VK_BINDING_TYPE_STORAGE_BUFFER_DYNAMIC) {
            // TODO need to get a frame stride
            dynamicOffsets.emplace_back();
        }
    }

    VkDescriptorSetLayoutCreateInfo create_info = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
        .bindingCount = (uint32_t) info.bindingsCount,
        .pBindings = layoutBindings.data(),
    };

    VK_CHECK(vkCreateDescriptorSetLayout(device, &create_info, VK_CALLBACKS, &layout));
    VK_DEBUG_NAME_FORMAT(device, VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT, layout, "VkDescriptorLayout-" << info.name);

    VkDescriptors::newPool(this);
    VkDescriptors::newSet(this);
}

VkBindingLayout::~VkBindingLayout() {
    if (layout) {
        vkDestroyDescriptorSetLayout(device, layout, VK_CALLBACKS);
        layout = nullptr;
        VkDescriptors::deletePool(this);
        VkDescriptors::deleteSet(this);
        dynamicOffsets.clear();
    }
}

void VkBindingLayout::update(const VkBindingInfo &newInfo) {
    this->info = newInfo;
    this->~VkBindingLayout();
    new (this) VkBindingLayout(device, newInfo);
}
