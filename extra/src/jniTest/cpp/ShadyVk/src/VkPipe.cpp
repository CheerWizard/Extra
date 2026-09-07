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
#include "VkPipe.hpp"

#include <vector>

#include "VkBindingLayout.hpp"
#include "VkContext.hpp"
#include "VkRenderTarget.hpp"
#include "VkShader.hpp"

VkPipe* VkPipe_create(VkContext* context, VkPipeInfo* info) {
    return new VkPipe(context->device, *info);
}

void VkPipe_destroy(VkPipe* pipe) {
    delete pipe;
}

void VkPipe_setInfo(VkPipe* pipe, VkPipeInfo* info) {
    pipe->update(*info);
}

std::unordered_map<VkShader*, VkPipe*> VkPipe::shadersWithPipes = {};

VkPipe::VkPipe(VkDevice device, const VkPipelineInfo &info)
: device(device), info(info) {
    uint32_t stride = 0;
    std::vector<VkVertexInputAttributeDescription> vk_attributes(info.vertexAttributesCount);

    for (int i = 0 ; i < info.vertexAttributesCount; i++) {
        const auto& attribute = info.vertexAttributes[i];
        auto& vk_attribute = vk_attributes[i];

        uint32_t size = static_cast<uint32_t>(attribute.type) * sizeof(float);

        vk_attribute.binding = info.vertexBufferSlot;
        vk_attribute.location = attribute.location;
        vk_attribute.format = (VkFormat) attribute.format;
        vk_attribute.offset = stride;

        stride += size;
    }

    VkVertexInputBindingDescription bindingDescription = {
        .binding = info.vertexBufferSlot,
        .stride = stride,
    };

    if (info.instanced == VK_TRUE) {
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
    } else {
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
    }

    VkPipelineVertexInputStateCreateInfo vertexInputInfo {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
        .vertexBindingDescriptionCount = 1,
        .pVertexBindingDescriptions = &bindingDescription,
        .vertexAttributeDescriptionCount = static_cast<uint32_t>(vk_attributes.size()),
        .pVertexAttributeDescriptions = vk_attributes.data(),
    };

    VkPipelineVertexInputStateCreateInfo* pVertexInputInfo = nullptr;
    if (!vk_attributes.empty()) {
        pVertexInputInfo = &vertexInputInfo;
    }

    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {
        VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO
    };
    inputAssembly.topology = (VkPrimitiveTopology) info.primitiveTopology;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    std::vector<VkPipelineShaderStageCreateInfo> shaderStages;
    std::vector<VkDescriptorSetLayout> descriptor_set_layouts;

    if (info.vertexShader) {
        shaderStages.emplace_back(VkPipelineShaderStageCreateInfo {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_VERTEX_BIT,
            .module = info.vertexShader->shader,
            .pName = info.vertexShader->info.entryPoint,
        });
        if (info.vertexShader->info.binding_layouts_count > 0) {
            for (int i = 0 ; i < info.vertexShader->info.binding_layouts_count ; i++) {
                descriptor_set_layouts.emplace_back(info.vertexShader->info.binding_layouts[i]->layout);
            }
        }
    }

    if (info.fragmentShader) {
        shaderStages.emplace_back(VkPipelineShaderStageCreateInfo {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
            .module = info.fragmentShader->shader,
            .pName = info.fragmentShader->info.entryPoint,
        });
        if (info.fragmentShader->info.binding_layouts_count > 0) {
            for (int i = 0 ; i < info.fragmentShader->info.binding_layouts_count ; i++) {
                descriptor_set_layouts.emplace_back(info.fragmentShader->info.binding_layouts[i]->layout);
            }
        }
    }

    if (info.geometryShader) {
        shaderStages.emplace_back(VkPipelineShaderStageCreateInfo {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
            .stage = VK_SHADER_STAGE_GEOMETRY_BIT,
            .module = info.geometryShader->shader,
            .pName = info.geometryShader->info.entryPoint,
        });
        if (info.geometryShader->info.binding_layouts_count > 0) {
            for (int i = 0 ; i < info.geometryShader->info.binding_layouts_count ; i++) {
                descriptor_set_layouts.emplace_back(info.geometryShader->info.binding_layouts[i]->layout);
            }
        }
    }

    std::array dynamicStates = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR,
        VK_DYNAMIC_STATE_CULL_MODE,
        VK_DYNAMIC_STATE_FRONT_FACE,
        VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY,
    };

    VkPipelineDynamicStateCreateInfo dynamicState = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount = dynamicStates.size(),
        .pDynamicStates = dynamicStates.data(),
    };

    VkViewport viewport = {
        .x = info.viewportX,
        .y = info.viewportY,
        .width = info.viewportWidth,
        .height = info.viewportHeight,
        .minDepth = info.viewportMinDepth,
        .maxDepth = info.viewportMaxDepth,
    };

    VkRect2D scissor = {
        .offset = { info.scissorX, info.scissorY },
        .extent = { info.scissorWidth, info.scissorHeight },
    };

    VkPipelineViewportStateCreateInfo viewportState = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .pViewports = &viewport,
        .scissorCount = 1,
        .pScissors = &scissor,
    };

    VkPipelineRasterizationStateCreateInfo rasterizer = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .depthClampEnable = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode = (VkPolygonMode) info.polygonMode,
        .cullMode = (VkCullModeFlags) info.cullMode,
        .frontFace = (VkFrontFace) info.frontFace,
        .depthBiasEnable = VK_FALSE,
        .depthBiasConstantFactor = 0.0f,
        .depthBiasClamp = 0.0f,
        .depthBiasSlopeFactor = 0.0f,
        .lineWidth = info.lineWidth,
    };

    VkPipelineMultisampleStateCreateInfo multisampling = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .rasterizationSamples = (VkSampleCountFlagBits) info.sampleCount,
        .sampleShadingEnable = VK_FALSE,
        .minSampleShading = 1.0f,
        .pSampleMask = nullptr,
        .alphaToCoverageEnable = VK_FALSE,
        .alphaToOneEnable = VK_FALSE,
    };

    VkPipelineDepthStencilStateCreateInfo depthStencil = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .depthTestEnable = VK_TRUE,
        .depthWriteEnable = VK_TRUE,
        .depthCompareOp = VK_COMPARE_OP_LESS,
        .stencilTestEnable = VK_FALSE,
    };

    ASSERT(info.renderTarget != nullptr && info.renderTarget->info.colorAttachmentsCount > 0, TAG, "Assertion failed. Render target must be set for VkPipe!")

    size_t colorAttachmentsCount = info.renderTarget->info.colorAttachmentsCount;
    std::vector<VkPipelineColorBlendAttachmentState> colorAttachments(colorAttachmentsCount);

    for (int i = 0 ; i < colorAttachmentsCount ; i++) {
        const auto colorAttachment = info.renderTarget->info.colorAttachments[i];
        colorAttachments[i] = {
            .blendEnable = colorAttachment.blend.enable,
            .srcColorBlendFactor = colorAttachment.blend.srcFactorColor,
            .dstColorBlendFactor = colorAttachment.blend.dstFactorColor,
            .colorBlendOp = colorAttachment.blend.blendOpColor,
            .srcAlphaBlendFactor = colorAttachment.blend.srcFactorAlpha,
            .dstAlphaBlendFactor = colorAttachment.blend.dstFactorAlpha,
            .alphaBlendOp = colorAttachment.blend.blendOpAlpha,
            .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
        };
    }

    VkPipelineColorBlendStateCreateInfo colorBlending = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .logicOpEnable = VK_FALSE,
        .logicOp = VK_LOGIC_OP_COPY,
        .attachmentCount = static_cast<u32>(colorAttachments.size()),
        .pAttachments = colorAttachments.data(),
        .blendConstants = { 0.0f, 0.0f, 0.0f, 0.0f },
    };

    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        .setLayoutCount = static_cast<u32>(descriptor_set_layouts.size()),
        .pSetLayouts = descriptor_set_layouts.data(),
        .pushConstantRangeCount = 0,
        .pPushConstantRanges = nullptr,
    };

    VK_CHECK(vkCreatePipelineLayout(device, &pipelineLayoutInfo, VK_CALLBACKS, &pipelineLayout));
    VK_DEBUG_NAME(device, VK_OBJECT_TYPE_PIPELINE_LAYOUT, pipelineLayout, info.name);

    VkGraphicsPipelineCreateInfo pipelineInfo = {
        .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
        .stageCount = static_cast<uint32_t>(shaderStages.size()),
        .pStages = shaderStages.data(),
        .pVertexInputState = pVertexInputInfo,
        .pInputAssemblyState = &inputAssembly,
        .pViewportState = &viewportState,
        .pRasterizationState = &rasterizer,
        .pMultisampleState = &multisampling,
        .pDepthStencilState = &depthStencil,
        .pColorBlendState = &colorBlending,
        .pDynamicState = &dynamicState,
        .layout = pipelineLayout,
        .renderPass = info.renderTarget->render_pass,
        .subpass = 0,
        .basePipelineHandle = VK_NULL_HANDLE,
        .basePipelineIndex = -1,
    };

    VK_CHECK(vkCreateGraphicsPipelines(device, nullptr, 1, &pipelineInfo, VK_CALLBACKS, &pipeline));
    VK_DEBUG_NAME(device, VK_OBJECT_TYPE_PIPELINE, pipeline, info.name);

    shadersWithPipes[info.vertexShader] = this;
    shadersWithPipes[info.fragmentShader] = this;
    shadersWithPipes[info.geometryShader] = this;
}

VkPipe::~VkPipe() {
    if (pipeline) {
        vkDestroyPipeline(device, pipeline, VK_CALLBACKS);
        pipeline = nullptr;
    }
}

void VkPipe::update(const VkPipeInfo &newInfo) {
    this->~VkPipe();
    new (this) VkPipe(device, newInfo);
}

void VkPipe::onShaderUpdated(VkShader* shader) {
    auto pipe = shadersWithPipes[shader];
    if (pipe) {
        switch (shader->info.stage) {
            case VK_SHADER_STAGE_VERTEX_BIT:
                pipe->info.vertexShader = shader;
                break;
            case VK_SHADER_STAGE_FRAGMENT_BIT:
                pipe->info.fragmentShader = shader;
                break;
            case VK_SHADER_STAGE_GEOMETRY_BIT:
                pipe->info.geometryShader = shader;
                break;
            default: return;
        }
        pipe->update(pipe->info);
    }
}

VkComputePipe* VkComputePipe_create(VkContext* context, VkComputePipeInfo* info) {
    return new VkComputePipe(context->device, *info);
}

void VkComputePipe_destroy(VkComputePipe* pipe) {
    delete pipe;
}

void VkComputePipe_setInfo(VkComputePipe* pipe, VkComputePipeInfo* info) {
    pipe->update(*info);
}

std::unordered_map<VkShader*, VkComputePipe*> VkComputePipe::shadersWithPipes = {};

VkComputePipe::VkComputePipe(VkDevice device, const VkComputePipeInfo &info)
: device(device), info(info) {
    std::vector<VkDescriptorSetLayout> descriptor_set_layouts;

    VkPipelineShaderStageCreateInfo shader_stage_create_info = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
    };

    if (info.computeShader) {
        shader_stage_create_info.stage = VK_SHADER_STAGE_COMPUTE_BIT;
        shader_stage_create_info.module = info.computeShader->shader;
        shader_stage_create_info.pName = info.computeShader->info.entryPoint;
        if (info.computeShader->info.binding_layouts_count > 0) {
            for (int i = 0 ; i < info.computeShader->info.binding_layouts_count ; i++) {
                descriptor_set_layouts.emplace_back(info.computeShader->info.binding_layouts[i]->layout);
            }
        }
    }

    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
            .setLayoutCount = static_cast<u32>(descriptor_set_layouts.size()),
            .pSetLayouts = descriptor_set_layouts.data(),
            .pushConstantRangeCount = 0,
            .pPushConstantRanges = nullptr,
    };

    VK_CHECK(vkCreatePipelineLayout(device, &pipelineLayoutInfo, VK_CALLBACKS, &pipelineLayout));
    VK_DEBUG_NAME(device, VK_OBJECT_TYPE_PIPELINE_LAYOUT, pipelineLayout, info.name);

    VkComputePipelineCreateInfo pipelineInfo = {
            .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
            .stage = shader_stage_create_info,
            .layout = pipelineLayout,
            .basePipelineHandle = VK_NULL_HANDLE,
            .basePipelineIndex = -1,
    };

    VK_CHECK(vkCreateComputePipelines(device, nullptr, 1, &pipelineInfo, VK_CALLBACKS, &pipeline));
    VK_DEBUG_NAME(device, VK_OBJECT_TYPE_PIPELINE, pipeline, info.name);

    shadersWithPipes[info.computeShader] = this;
}

VkComputePipe::~VkComputePipe() {
    if (pipeline) {
        vkDestroyPipeline(device, pipeline, VK_CALLBACKS);
        pipeline = nullptr;
    }
}

void VkComputePipe::update(const VkComputePipeInfo &newInfo) {
    this->~VkComputePipe();
    new (this) VkComputePipe(device, newInfo);
}

void VkComputePipe::onShaderUpdated(VkShader* shader) {
    auto pipe = shadersWithPipes[shader];
    pipe->info.computeShader = shader;
    pipe->update(pipe->info);
}
