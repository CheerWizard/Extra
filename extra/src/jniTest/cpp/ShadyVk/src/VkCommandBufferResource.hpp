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
#include "VkSurface.hpp"

struct VkCommandBufferResource {
    VkCommandBuffer command_buffer = nullptr;
    VkDeviceQueue& device_queue;

    VkCommandBufferResource(VkDeviceQueue& device_queue, const char* name, bool isPrimary);
    ~VkCommandBufferResource();

    void reset() const;
    void begin() const;
    void end();

    void beginRenderPass(VkRenderTarget* render_target, u32 surfaceImageIndex);
    void endRenderPass() const;

    void setPipe(VkPipe* pipe, u32 frame) const;
    void setComputePipe(VkComputePipe* pipe, u32 frame) const;
    void setPipeline(VkPipelineBindPoint pipeline_bind_point, VkPipeline pipeline) const;
    void setVertexBuffer(VkBufferResource* buffer, u32 frame) const;
    void setIndexBuffer(VkBufferResource* buffer, u32 frame) const;
    void setDescriptorSet(
        VkPipelineBindPoint pipeline_bind_point,
        VkPipelineLayout pipeline_layout,
        VkBindingLayout* binding_layout,
        u32 frame
    ) const;

    void setViewport(float x, float y, float width, float height, float minDepth, float maxDepth) const;
    void setScissor(int x, int y, u32 w, u32 h) const;

    void draw(u32 vertices, u32 vertexOffset, u32 instances, u32 instanceOffset) const;
    void drawIndexed(u32 vertices, u32 vertexOffset, u32 indices, u32 indexOffset, u32 instances, u32 instanceOffset) const;
    void drawIndexedIndirect(VkBufferResource* indirectBuffer, size_t offset, u32 drawCount) const;

    void addSecondaryBuffer(VkCommandBufferResource* secondaryBuffer) const;
    void addSecondaryBuffers(VkCommandBufferResource** secondaryBuffers, size_t secondaryBuffersCount) const;
    void submit(VkSemaphoreResource* waitSemaphore, VkSemaphoreResource* signalSemaphore, VkFenceResource* fence) const;

    bool present(VkSurface* surface, VkSemaphoreResource* waitSemaphore) const;

    void copyBufferToBuffer(VkBufferResource* srcBuffer, VkBufferResource* dstBuffer, size_t srcOffset, size_t dstOffset, size_t size) const;
    void copyBufferToImage(VkBufferResource* srcBuffer, VkTextureResource* dstImage, u32 dstMipLevel, u32 dstWidth, u32 dstHeight, u32 dstDepth) const;
    void copyImageToImage(
        VkTextureResource* srcImage,
        VkTextureResource* dstImage,
        int srcX, int srcY, int srcZ,
        int dstX, int dstY, int dstZ,
        u32 width, u32 height, u32 depth
    ) const;

    void dispatch(u32 groupsX, u32 groupsY, u32 groupsZ) const;
    void pipelineBarrier(u32 srcStages, u32 dstStages, u32 srcAccessFlags, u32 dstAccessFlags) const;

private:
    void setShader(VkPipelineBindPoint pipeline_bind_point, VkPipelineLayout pipeline_layout, VkShader* shader, u32 frame) const;

    static constexpr auto TAG = "VkCommandBufferResource";
};

#endif //COMMAND_BUFFER_HPP