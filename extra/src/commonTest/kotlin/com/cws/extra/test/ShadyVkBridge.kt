package com.cws.extra.test

import com.cws.extra.memory.ExtraBridge

@ExtraBridge("ShadyVk")
interface ShadyVkBridge {

    // --------------------------------------------------
    // Callbacks
    // --------------------------------------------------

    fun LogBridge_callback(callback: (level: Int, tag: String, msg: String, exceptionMsg: String) -> Unit)
    fun ResultBridge_callback(callback: (result: Int) -> Unit)
    fun removeCallbacks()

    // --------------------------------------------------
    // VkContext
    // --------------------------------------------------

    fun VkContext_create(surface: Any?, info: RenderContextInfo): Long

    fun VkContext_destroy(context: Long)

    fun VkContext_setInfo(
        context: Long,
        info: RenderContextInfo
    )

    fun VkContext_wait(context: Long)

    fun VkContext_resize(
        context: Long,
        width: Int,
        height: Int
    )

    fun VkContext_setSurface(
        context: Long,
        surface: Any?,
    )

    fun VkContext_getRenderTarget(
        context: Long
    ): Long

    fun VkContext_getPrimaryCommandBuffer(
        context: Long,
        frame: Int
    ): Long
    fun VkContext_getSecondaryCommandBuffer(
        context: Long
    ): Long

    fun VkContext_beginFrame(
        context: Long,
        frame: Int
    )

    fun VkContext_endFrame(
        context: Long,
        frame: Int
    )

    // --------------------------------------------------
    // VkShader
    // --------------------------------------------------

    fun VkShader_create(
        context: Long,
        info: ShaderInfo
    ): Long

    fun VkShader_destroy(
        shader: Long
    )

    fun VkShader_setInfo(
        shader: Long,
        info: ShaderInfo
    )

    // --------------------------------------------------
    // VkBindingLayout
    // --------------------------------------------------

    fun VkBindingLayout_create(
        context: Long,
        info: BindingInfo
    ): Long

    fun VkBindingLayout_destroy(
        layout: Long
    )

    fun VkBindingLayout_setInfo(
        layout: Long,
        info: BindingInfo
    )

    // --------------------------------------------------
    // VkRenderTarget
    // --------------------------------------------------

    fun VkRenderTarget_create(
        context: Long,
        info: RenderTargetInfo
    ): Long

    fun VkRenderTarget_destroy(
        target: Long
    )

    fun VkRenderTarget_setInfo(
        target: Long,
        info: RenderTargetInfo
    )

    fun VkRenderTarget_resize(
        target: Long,
        width: Int,
        height: Int
    )

    // --------------------------------------------------
    // VkBufferResource
    // --------------------------------------------------

    fun VkBufferResource_create(
        context: Long,
        info: BufferInfo
    ): Long

    fun VkBufferResource_destroy(
        buffer: Long
    )

    fun VkBufferResource_setInfo(
        buffer: Long,
        info: BufferInfo
    )

    fun VkBufferResource_map(
        buffer: Long,
        frame: Int
    ): Long

    fun VkBufferResource_unmap(
        buffer: Long
    )

    // --------------------------------------------------
    // VkSamplerResource
    // --------------------------------------------------

    fun VkSamplerResource_create(
        context: Long,
        info: SamplerInfo
    ): Long

    fun VkSamplerResource_destroy(
        sampler: Long
    )

    fun VkSamplerResource_setInfo(
        sampler: Long,
        info: SamplerInfo
    )

    // --------------------------------------------------
    // VkTextureResource
    // --------------------------------------------------

    fun VkTextureResource_create(
        context: Long,
        info: TextureInfo
    ): Long

    fun VkTextureResource_destroy(
        texture: Long
    )

    fun VkTextureResource_setInfo(
        texture: Long,
        info: TextureInfo
    )

    fun VkTextureResource_map(
        texture: Long,
        frame: Int
    ): Long

    fun VkTextureResource_unmap(
        texture: Long
    )

    // --------------------------------------------------
    // VkPipe
    // --------------------------------------------------

    fun VkPipe_create(
        context: Long,
        info: RenderPipelineInfo
    ): Long

    fun VkPipe_destroy(
        pipe: Long
    )

    fun VkPipe_setInfo(
        pipe: Long,
        info: RenderPipelineInfo
    )

    // --------------------------------------------------
    // VkPipe
    // --------------------------------------------------

    fun VkComputePipe_create(
        context: Long,
        info: ComputePipelineInfo
    ): Long

    fun VkComputePipe_destroy(
        pipe: Long
    )

    fun VkComputePipe_setInfo(
        pipe: Long,
        info: ComputePipelineInfo
    )

    // --------------------------------------------------
    // VkCommandBufferResource
    // --------------------------------------------------

    fun VkCommandBufferResource_reset(
        cmd: Long
    )

    fun VkCommandBufferResource_begin(
        cmd: Long
    )

    fun VkCommandBufferResource_end(
        cmd: Long
    )

    fun VkCommandBufferResource_beginRenderPass(
        cmd: Long,
        renderTarget: Long,
        colorAttachmentIndex: Int
    )

    fun VkCommandBufferResource_endRenderPass(
        cmd: Long
    )

    fun VkCommandBufferResource_setPipe(
        cmd: Long,
        pipe: Long,
        frame: Int,
    )

    fun VkCommandBufferResource_setComputePipe(
        cmd: Long,
        pipe: Long,
        frame: Int,
    )

    fun VkCommandBufferResource_setViewport(
        cmd: Long,
        x: Float,
        y: Float,
        width: Float,
        height: Float,
        minDepth: Float,
        maxDepth: Float
    )

    fun VkCommandBufferResource_setScissor(
        cmd: Long,
        x: Int,
        y: Int,
        w: Int,
        h: Int
    )

    fun VkCommandBufferResource_addSecondaryBuffer(
        cmd: Long,
        secondaryBuffer: Long
    )

    fun VkCommandBufferResource_draw(
        cmd: Long,
        vertices: Int,
        vertexOffset: Int,
        instances: Int,
        instanceOffset: Int
    )

    fun VkCommandBufferResource_drawIndexed(
        cmd: Long,
        vertices: Int,
        vertexOffset: Int,
        indices: Int,
        indexOffset: Int,
        instances: Int,
        instanceOffset: Int
    )

    fun VkCommandBufferResource_drawIndexedIndirect(
        cmd: Long,
        indirectBuffer: Long,
        offset: Int,
        drawCount: Int
    )

    fun VkCommandBufferResource_copyBufferToBuffer(
        cmd: Long,
        src: Long,
        dst: Long,
        srcOffset: Int,
        dstOffset: Int,
        size: Int
    )

    fun VkCommandBufferResource_copyBufferToImage(
        cmd: Long,
        src: Long,
        dst: Long,
        dstMipLevel: Int,
        dstWidth: Int,
        dstHeight: Int,
        dstDepth: Int
    )

    fun VkCommandBufferResource_copyImageToImage(
        cmd: Long,
        src: Long,
        dst: Long,
        srcX: Int,
        srcY: Int,
        srcZ: Int,
        dstX: Int,
        dstY: Int,
        dstZ: Int,
        width: Int,
        height: Int,
        depth: Int
    )

    fun VkCommandBufferResource_dispatch(
        cmd: Long,
        groupsX: Int,
        groupsY: Int,
        groupsZ: Int,
    )

    fun VkCommandBufferResource_pipelineBarrier(
        cmd: Long,
        srcStages: Int,
        dstStages: Int,
        srcAccessFlags: Int,
        dstAccessFlags: Int,
    )
}