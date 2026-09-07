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
#include "VkShader.hpp"
#include "VkBindingLayout.hpp"
#include "VkContext.hpp"
#include "VkPipe.hpp"

VkShader* VkShader_create(VkContext* context, VkShaderInfo* info) {
    return new VkShader(context->device, *info);
}

void VkShader_destroy(VkShader* shader) {
    delete shader;
}

void VkShader_setInfo(VkShader* shader, VkShaderInfo* info) {
    shader->update(*info);
}

VkShader::VkShader(VkDevice device, const VkShaderInfo &info)
: device(device), info(info) {
    VkShaderModuleCreateInfo create_info = {
            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .codeSize = info.spirvCodeSize * sizeof(u32),
            .pCode = info.spirvCode,
    };
    VK_CHECK(vkCreateShaderModule(device, &create_info, VK_CALLBACKS, &shader));
    VK_DEBUG_NAME(device, VK_OBJECT_TYPE_SHADER_MODULE, shader, info.name);
}

VkShader::~VkShader() {
    if (shader) {
        vkDestroyShaderModule(device, shader, VK_CALLBACKS);
        shader = nullptr;
    }
}

void VkShader::update(const VkShaderInfo& newInfo) {
    this->~VkShader();
    new (this) VkShader(device, newInfo);

    for (int i = 0 ; i < info.binding_layouts_count ; i++) {
        auto binding_layout = info.binding_layouts[i];
        if (binding_layout) {
            binding_layout->update(binding_layout->info);
        }
    }

    VkPipe::onShaderUpdated(this);
    VkComputePipe::onShaderUpdated(this);
}
