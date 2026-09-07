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
#pragma once

#include "VkTypes.h"

// -------------- ShadyVkBridge -----------------

inline void ShadyVkBridge_LogBridge_callback(const VkFunction4& callback)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_ResultBridge_callback(const VkFunction1& callback)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_removeCallbacks()
{
    // TODO: not implemented!
}

inline int64_t ShadyVkBridge_VkContext_create(const VkAny& surface, const VkRenderContextInfo& info)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkContext_destroy(int64_t context)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkContext_setInfo(int64_t context, const VkRenderContextInfo& info)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkContext_wait(int64_t context)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkContext_resize(int64_t context, int32_t width, int32_t height)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkContext_setSurface(int64_t context, const VkAny& surface)
{
    // TODO: not implemented!
}

inline int64_t ShadyVkBridge_VkContext_getRenderTarget(int64_t context)
{
    // TODO: not implemented!
}

inline int64_t ShadyVkBridge_VkContext_getPrimaryCommandBuffer(int64_t context, int32_t frame)
{
    // TODO: not implemented!
}

inline int64_t ShadyVkBridge_VkContext_getSecondaryCommandBuffer(int64_t context)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkContext_beginFrame(int64_t context, int32_t frame)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkContext_endFrame(int64_t context, int32_t frame)
{
    // TODO: not implemented!
}

inline int64_t ShadyVkBridge_VkShader_create(int64_t context, const VkShaderInfo& info)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkShader_destroy(int64_t shader)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkShader_setInfo(int64_t shader, const VkShaderInfo& info)
{
    // TODO: not implemented!
}

inline int64_t ShadyVkBridge_VkBindingLayout_create(int64_t context, const VkBindingInfo& info)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkBindingLayout_destroy(int64_t layout)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkBindingLayout_setInfo(int64_t layout, const VkBindingInfo& info)
{
    // TODO: not implemented!
}

inline int64_t ShadyVkBridge_VkRenderTarget_create(int64_t context, const VkRenderTargetInfo& info)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkRenderTarget_destroy(int64_t target)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkRenderTarget_setInfo(int64_t target, const VkRenderTargetInfo& info)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkRenderTarget_resize(int64_t target, int32_t width, int32_t height)
{
    // TODO: not implemented!
}

inline int64_t ShadyVkBridge_VkBufferResource_create(int64_t context, const VkBufferInfo& info)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkBufferResource_destroy(int64_t buffer)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkBufferResource_setInfo(int64_t buffer, const VkBufferInfo& info)
{
    // TODO: not implemented!
}

inline int64_t ShadyVkBridge_VkBufferResource_map(int64_t buffer, int32_t frame)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkBufferResource_unmap(int64_t buffer)
{
    // TODO: not implemented!
}

inline int64_t ShadyVkBridge_VkSamplerResource_create(int64_t context, const VkSamplerInfo& info)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkSamplerResource_destroy(int64_t sampler)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkSamplerResource_setInfo(int64_t sampler, const VkSamplerInfo& info)
{
    // TODO: not implemented!
}

inline int64_t ShadyVkBridge_VkTextureResource_create(int64_t context, const VkTextureInfo& info)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkTextureResource_destroy(int64_t texture)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkTextureResource_setInfo(int64_t texture, const VkTextureInfo& info)
{
    // TODO: not implemented!
}

inline int64_t ShadyVkBridge_VkTextureResource_map(int64_t texture, int32_t frame)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkTextureResource_unmap(int64_t texture)
{
    // TODO: not implemented!
}

inline int64_t ShadyVkBridge_VkPipe_create(int64_t context, const VkRenderPipelineInfo& info)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkPipe_destroy(int64_t pipe)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkPipe_setInfo(int64_t pipe, const VkRenderPipelineInfo& info)
{
    // TODO: not implemented!
}

inline int64_t ShadyVkBridge_VkComputePipe_create(int64_t context, const VkComputePipelineInfo& info)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkComputePipe_destroy(int64_t pipe)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkComputePipe_setInfo(int64_t pipe, const VkComputePipelineInfo& info)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_reset(int64_t cmd)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_begin(int64_t cmd)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_end(int64_t cmd)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_beginRenderPass(int64_t cmd, int64_t renderTarget, int32_t colorAttachmentIndex)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_endRenderPass(int64_t cmd)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_setPipe(int64_t cmd, int64_t pipe, int32_t frame)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_setComputePipe(int64_t cmd, int64_t pipe, int32_t frame)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_setViewport(int64_t cmd, float x, float y, float width, float height, float minDepth, float maxDepth)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_setScissor(int64_t cmd, int32_t x, int32_t y, int32_t w, int32_t h)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_addSecondaryBuffer(int64_t cmd, int64_t secondaryBuffer)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_draw(int64_t cmd, int32_t vertices, int32_t vertexOffset, int32_t instances, int32_t instanceOffset)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_drawIndexed(int64_t cmd, int32_t vertices, int32_t vertexOffset, int32_t indices, int32_t indexOffset, int32_t instances, int32_t instanceOffset)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_drawIndexedIndirect(int64_t cmd, int64_t indirectBuffer, int32_t offset, int32_t drawCount)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_copyBufferToBuffer(int64_t cmd, int64_t src, int64_t dst, int32_t srcOffset, int32_t dstOffset, int32_t size)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_copyBufferToImage(int64_t cmd, int64_t src, int64_t dst, int32_t dstMipLevel, int32_t dstWidth, int32_t dstHeight, int32_t dstDepth)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_copyImageToImage(int64_t cmd, int64_t src, int64_t dst, int32_t srcX, int32_t srcY, int32_t srcZ, int32_t dstX, int32_t dstY, int32_t dstZ, int32_t width, int32_t height, int32_t depth)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_dispatch(int64_t cmd, int32_t groupsX, int32_t groupsY, int32_t groupsZ)
{
    // TODO: not implemented!
}

inline void ShadyVkBridge_VkCommandBufferResource_pipelineBarrier(int64_t cmd, int32_t srcStages, int32_t dstStages, int32_t srcAccessFlags, int32_t dstAccessFlags)
{
    // TODO: not implemented!
}
