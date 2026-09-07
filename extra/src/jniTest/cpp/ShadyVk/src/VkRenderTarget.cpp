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
#include "VkRenderTarget.hpp"

#include <vector>

#include "VkContext.hpp"
#include "VkTextureResource.hpp"

VkRenderTarget* VkRenderTarget_create(VkContext* context, VkRenderTargetInfo* info) {
    return new VkRenderTarget(context, *info);
}

void VkRenderTarget_destroy(VkRenderTarget* render_target) {
    delete render_target;
}

void VkRenderTarget_setInfo(VkRenderTarget* render_target, VkRenderTargetInfo* info) {
    render_target->info = *info;
}

void VkRenderTarget_resize(VkRenderTarget* render_target, u32 width, u32 height) {
    render_target->resize(width, height);
}

VkRenderTarget::VkRenderTarget(VkContext* context, const VkRenderTargetInfo &info)
: context(context), info(info) {
    u32 frameCount = context->info.frameCount;
    u32 colorAttachmentsCount = info.colorAttachmentsCount;

    std::vector<VkAttachmentDescription> vk_color_attachments(colorAttachmentsCount);
    std::vector<VkAttachmentReference> vk_color_references(colorAttachmentsCount);

    for (u32 i = 0 ; i < colorAttachmentsCount ; i++) {
        auto& vk_color_attachment = vk_color_attachments[i];
        auto& vk_color_reference = vk_color_references[i];
        const auto& color_attachment = info.colorAttachments[i];

        vk_color_attachment.format = color_attachment.texture->info.format;
        vk_color_attachment.samples = static_cast<VkSampleCountFlagBits>(color_attachment.texture->info.samples);
        // TODO expose more params
        vk_color_attachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        vk_color_attachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        vk_color_attachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        vk_color_attachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        vk_color_attachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        vk_color_attachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        vk_color_reference.attachment = i;
        vk_color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }

    VkSubpassDescription subpass = {
            .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
            .colorAttachmentCount = colorAttachmentsCount,
            .pColorAttachments = vk_color_references.data(),
    };

    VkRenderPassCreateInfo renderPassCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
            .attachmentCount = colorAttachmentsCount,
            .pAttachments = vk_color_attachments.data(),
            .subpassCount = 1,
            .pSubpasses = &subpass,
    };

    VK_CHECK(vkCreateRenderPass(context->device, &renderPassCreateInfo, VK_CALLBACKS, &render_pass));
    VK_DEBUG_NAME(context->device, VK_OBJECT_TYPE_RENDER_PASS, render_pass, info.name);

    for (int i = 0 ; i < frameCount ; i++) {
        std::vector<VkImageView> vk_image_views(colorAttachmentsCount);
        for (int j = 0 ; j < colorAttachmentsCount ; j++) {
            vk_image_views.emplace_back(info.colorAttachments[j].texture->views[i]);
        }

        VkFramebufferCreateInfo framebufferCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .renderPass = render_pass,
            .attachmentCount = colorAttachmentsCount,
            .pAttachments = vk_image_views.data(),
            .width = info.width,
            .height = info.height,
            .layers = info.depth,
        };

        VK_CHECK(vkCreateFramebuffer(context->device, &framebufferCreateInfo, VK_CALLBACKS, &framebuffers[i]));
        VK_DEBUG_NAME(context->device, VK_OBJECT_TYPE_FRAMEBUFFER, framebuffers[i], info.name);
    }
}

VkRenderTarget::~VkRenderTarget() {
    info.colorAttachments = nullptr;
    info.colorAttachmentsCount = 0;
    info.depthAttachment = nullptr;
    info.stencilAttachment = nullptr;

    for (int i = 0 ; i < framebuffers.size() ; i++) {
        vkDestroyFramebuffer(context->device, framebuffers[i], VK_CALLBACKS);
    }
    framebuffers.clear();

    if (render_pass) {
        vkDestroyRenderPass(context->device, render_pass, VK_CALLBACKS);
    }
}

void VkRenderTarget::resize(u32 width, u32 height) {
    info.width = width;
    info.height = height;

    for (int i = 0 ; i < info.colorAttachmentsCount ; i++) {
        info.colorAttachments[i].texture->resize(width, height);
    }

    if (info.depthAttachment) {
        info.depthAttachment->texture->resize(width, height);
    }

    if (info.stencilAttachment) {
        info.stencilAttachment->texture->resize(width, height);
    }

    this->~VkRenderTarget();
    new (this) VkRenderTarget(context, info);
}