// Generated from Kotlin Extra library

package com.cws.extra.test

import com.cws.print.JniLibrary
import com.cws.extra.memory.NativeBuffer
import java.nio.ByteBuffer
import kotlin.Function4
import kotlin.encode
import kotlin.Function1
import kotlin.encode
import kotlin.Any
import kotlin.encode
import com.cws.extra.test.RenderContextInfo
import com.cws.extra.test.encode
import com.cws.extra.test.ShaderInfo
import com.cws.extra.test.encode
import com.cws.extra.test.BindingInfo
import com.cws.extra.test.encode
import com.cws.extra.test.RenderTargetInfo
import com.cws.extra.test.encode
import com.cws.extra.test.BufferInfo
import com.cws.extra.test.encode
import com.cws.extra.test.SamplerInfo
import com.cws.extra.test.encode
import com.cws.extra.test.TextureInfo
import com.cws.extra.test.encode
import com.cws.extra.test.RenderPipelineInfo
import com.cws.extra.test.encode
import com.cws.extra.test.ComputePipelineInfo
import com.cws.extra.test.encode

object ShadyVkBridgeJni : ShadyVkBridge {

    init {
        JniLibrary.load("ShadyVk")
    }

    override fun LogBridge_callback(
        callback: Function4,
    ) : kotlin.Unit {
        val callbackNativeBuffer = callback.encode()
        jni_LogBridge_callback(callbackNativeBuffer.directBuffer, callbackNativeBuffer.byteArray)
    }

    external fun jni_LogBridge_callback(
        callbackByteBuffer: ByteBuffer?, callbackByteArray: ByteArray?

    ) : kotlin.Unit

    override fun ResultBridge_callback(
        callback: Function1,
    ) : kotlin.Unit {
        val callbackNativeBuffer = callback.encode()
        jni_ResultBridge_callback(callbackNativeBuffer.directBuffer, callbackNativeBuffer.byteArray)
    }

    external fun jni_ResultBridge_callback(
        callbackByteBuffer: ByteBuffer?, callbackByteArray: ByteArray?

    ) : kotlin.Unit

    override fun removeCallbacks(
    ) : kotlin.Unit {
        jni_removeCallbacks()
    }

    external fun jni_removeCallbacks(

    ) : kotlin.Unit

    override fun VkContext_create(
        surface: Any,
        info: RenderContextInfo,
    ) : kotlin.Long {
        val surfaceNativeBuffer = surface.encode()
        val infoNativeBuffer = info.encode()
        return jni_VkContext_create(surfaceNativeBuffer.directBuffer, surfaceNativeBuffer.byteArray, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkContext_create(
        surfaceByteBuffer: ByteBuffer?, surfaceByteArray: ByteArray?, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Long

    override fun VkContext_destroy(
        context: Long,
    ) : kotlin.Unit {
        jni_VkContext_destroy(context)
    }

    external fun jni_VkContext_destroy(
        context: Long

    ) : kotlin.Unit

    override fun VkContext_setInfo(
        context: Long,
        info: RenderContextInfo,
    ) : kotlin.Unit {
        val infoNativeBuffer = info.encode()
        jni_VkContext_setInfo(context, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkContext_setInfo(
        context: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Unit

    override fun VkContext_wait(
        context: Long,
    ) : kotlin.Unit {
        jni_VkContext_wait(context)
    }

    external fun jni_VkContext_wait(
        context: Long

    ) : kotlin.Unit

    override fun VkContext_resize(
        context: Long,
        width: Int,
        height: Int,
    ) : kotlin.Unit {
        jni_VkContext_resize(context, width, height)
    }

    external fun jni_VkContext_resize(
        context: Long, 
        width: Int, 
        height: Int

    ) : kotlin.Unit

    override fun VkContext_setSurface(
        context: Long,
        surface: Any,
    ) : kotlin.Unit {
        val surfaceNativeBuffer = surface.encode()
        jni_VkContext_setSurface(context, surfaceNativeBuffer.directBuffer, surfaceNativeBuffer.byteArray)
    }

    external fun jni_VkContext_setSurface(
        context: Long, 
        surfaceByteBuffer: ByteBuffer?, surfaceByteArray: ByteArray?

    ) : kotlin.Unit

    override fun VkContext_getRenderTarget(
        context: Long,
    ) : kotlin.Long {
        return jni_VkContext_getRenderTarget(context)
    }

    external fun jni_VkContext_getRenderTarget(
        context: Long

    ) : kotlin.Long

    override fun VkContext_getPrimaryCommandBuffer(
        context: Long,
        frame: Int,
    ) : kotlin.Long {
        return jni_VkContext_getPrimaryCommandBuffer(context, frame)
    }

    external fun jni_VkContext_getPrimaryCommandBuffer(
        context: Long, 
        frame: Int

    ) : kotlin.Long

    override fun VkContext_getSecondaryCommandBuffer(
        context: Long,
    ) : kotlin.Long {
        return jni_VkContext_getSecondaryCommandBuffer(context)
    }

    external fun jni_VkContext_getSecondaryCommandBuffer(
        context: Long

    ) : kotlin.Long

    override fun VkContext_beginFrame(
        context: Long,
        frame: Int,
    ) : kotlin.Unit {
        jni_VkContext_beginFrame(context, frame)
    }

    external fun jni_VkContext_beginFrame(
        context: Long, 
        frame: Int

    ) : kotlin.Unit

    override fun VkContext_endFrame(
        context: Long,
        frame: Int,
    ) : kotlin.Unit {
        jni_VkContext_endFrame(context, frame)
    }

    external fun jni_VkContext_endFrame(
        context: Long, 
        frame: Int

    ) : kotlin.Unit

    override fun VkShader_create(
        context: Long,
        info: ShaderInfo,
    ) : kotlin.Long {
        val infoNativeBuffer = info.encode()
        return jni_VkShader_create(context, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkShader_create(
        context: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Long

    override fun VkShader_destroy(
        shader: Long,
    ) : kotlin.Unit {
        jni_VkShader_destroy(shader)
    }

    external fun jni_VkShader_destroy(
        shader: Long

    ) : kotlin.Unit

    override fun VkShader_setInfo(
        shader: Long,
        info: ShaderInfo,
    ) : kotlin.Unit {
        val infoNativeBuffer = info.encode()
        jni_VkShader_setInfo(shader, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkShader_setInfo(
        shader: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Unit

    override fun VkBindingLayout_create(
        context: Long,
        info: BindingInfo,
    ) : kotlin.Long {
        val infoNativeBuffer = info.encode()
        return jni_VkBindingLayout_create(context, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkBindingLayout_create(
        context: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Long

    override fun VkBindingLayout_destroy(
        layout: Long,
    ) : kotlin.Unit {
        jni_VkBindingLayout_destroy(layout)
    }

    external fun jni_VkBindingLayout_destroy(
        layout: Long

    ) : kotlin.Unit

    override fun VkBindingLayout_setInfo(
        layout: Long,
        info: BindingInfo,
    ) : kotlin.Unit {
        val infoNativeBuffer = info.encode()
        jni_VkBindingLayout_setInfo(layout, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkBindingLayout_setInfo(
        layout: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Unit

    override fun VkRenderTarget_create(
        context: Long,
        info: RenderTargetInfo,
    ) : kotlin.Long {
        val infoNativeBuffer = info.encode()
        return jni_VkRenderTarget_create(context, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkRenderTarget_create(
        context: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Long

    override fun VkRenderTarget_destroy(
        target: Long,
    ) : kotlin.Unit {
        jni_VkRenderTarget_destroy(target)
    }

    external fun jni_VkRenderTarget_destroy(
        target: Long

    ) : kotlin.Unit

    override fun VkRenderTarget_setInfo(
        target: Long,
        info: RenderTargetInfo,
    ) : kotlin.Unit {
        val infoNativeBuffer = info.encode()
        jni_VkRenderTarget_setInfo(target, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkRenderTarget_setInfo(
        target: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Unit

    override fun VkRenderTarget_resize(
        target: Long,
        width: Int,
        height: Int,
    ) : kotlin.Unit {
        jni_VkRenderTarget_resize(target, width, height)
    }

    external fun jni_VkRenderTarget_resize(
        target: Long, 
        width: Int, 
        height: Int

    ) : kotlin.Unit

    override fun VkBufferResource_create(
        context: Long,
        info: BufferInfo,
    ) : kotlin.Long {
        val infoNativeBuffer = info.encode()
        return jni_VkBufferResource_create(context, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkBufferResource_create(
        context: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Long

    override fun VkBufferResource_destroy(
        buffer: Long,
    ) : kotlin.Unit {
        jni_VkBufferResource_destroy(buffer)
    }

    external fun jni_VkBufferResource_destroy(
        buffer: Long

    ) : kotlin.Unit

    override fun VkBufferResource_setInfo(
        buffer: Long,
        info: BufferInfo,
    ) : kotlin.Unit {
        val infoNativeBuffer = info.encode()
        jni_VkBufferResource_setInfo(buffer, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkBufferResource_setInfo(
        buffer: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Unit

    override fun VkBufferResource_map(
        buffer: Long,
        frame: Int,
    ) : kotlin.Long {
        return jni_VkBufferResource_map(buffer, frame)
    }

    external fun jni_VkBufferResource_map(
        buffer: Long, 
        frame: Int

    ) : kotlin.Long

    override fun VkBufferResource_unmap(
        buffer: Long,
    ) : kotlin.Unit {
        jni_VkBufferResource_unmap(buffer)
    }

    external fun jni_VkBufferResource_unmap(
        buffer: Long

    ) : kotlin.Unit

    override fun VkSamplerResource_create(
        context: Long,
        info: SamplerInfo,
    ) : kotlin.Long {
        val infoNativeBuffer = info.encode()
        return jni_VkSamplerResource_create(context, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkSamplerResource_create(
        context: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Long

    override fun VkSamplerResource_destroy(
        sampler: Long,
    ) : kotlin.Unit {
        jni_VkSamplerResource_destroy(sampler)
    }

    external fun jni_VkSamplerResource_destroy(
        sampler: Long

    ) : kotlin.Unit

    override fun VkSamplerResource_setInfo(
        sampler: Long,
        info: SamplerInfo,
    ) : kotlin.Unit {
        val infoNativeBuffer = info.encode()
        jni_VkSamplerResource_setInfo(sampler, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkSamplerResource_setInfo(
        sampler: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Unit

    override fun VkTextureResource_create(
        context: Long,
        info: TextureInfo,
    ) : kotlin.Long {
        val infoNativeBuffer = info.encode()
        return jni_VkTextureResource_create(context, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkTextureResource_create(
        context: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Long

    override fun VkTextureResource_destroy(
        texture: Long,
    ) : kotlin.Unit {
        jni_VkTextureResource_destroy(texture)
    }

    external fun jni_VkTextureResource_destroy(
        texture: Long

    ) : kotlin.Unit

    override fun VkTextureResource_setInfo(
        texture: Long,
        info: TextureInfo,
    ) : kotlin.Unit {
        val infoNativeBuffer = info.encode()
        jni_VkTextureResource_setInfo(texture, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkTextureResource_setInfo(
        texture: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Unit

    override fun VkTextureResource_map(
        texture: Long,
        frame: Int,
    ) : kotlin.Long {
        return jni_VkTextureResource_map(texture, frame)
    }

    external fun jni_VkTextureResource_map(
        texture: Long, 
        frame: Int

    ) : kotlin.Long

    override fun VkTextureResource_unmap(
        texture: Long,
    ) : kotlin.Unit {
        jni_VkTextureResource_unmap(texture)
    }

    external fun jni_VkTextureResource_unmap(
        texture: Long

    ) : kotlin.Unit

    override fun VkPipe_create(
        context: Long,
        info: RenderPipelineInfo,
    ) : kotlin.Long {
        val infoNativeBuffer = info.encode()
        return jni_VkPipe_create(context, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkPipe_create(
        context: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Long

    override fun VkPipe_destroy(
        pipe: Long,
    ) : kotlin.Unit {
        jni_VkPipe_destroy(pipe)
    }

    external fun jni_VkPipe_destroy(
        pipe: Long

    ) : kotlin.Unit

    override fun VkPipe_setInfo(
        pipe: Long,
        info: RenderPipelineInfo,
    ) : kotlin.Unit {
        val infoNativeBuffer = info.encode()
        jni_VkPipe_setInfo(pipe, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkPipe_setInfo(
        pipe: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Unit

    override fun VkComputePipe_create(
        context: Long,
        info: ComputePipelineInfo,
    ) : kotlin.Long {
        val infoNativeBuffer = info.encode()
        return jni_VkComputePipe_create(context, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkComputePipe_create(
        context: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Long

    override fun VkComputePipe_destroy(
        pipe: Long,
    ) : kotlin.Unit {
        jni_VkComputePipe_destroy(pipe)
    }

    external fun jni_VkComputePipe_destroy(
        pipe: Long

    ) : kotlin.Unit

    override fun VkComputePipe_setInfo(
        pipe: Long,
        info: ComputePipelineInfo,
    ) : kotlin.Unit {
        val infoNativeBuffer = info.encode()
        jni_VkComputePipe_setInfo(pipe, infoNativeBuffer.directBuffer, infoNativeBuffer.byteArray)
    }

    external fun jni_VkComputePipe_setInfo(
        pipe: Long, 
        infoByteBuffer: ByteBuffer?, infoByteArray: ByteArray?

    ) : kotlin.Unit

    override fun VkCommandBufferResource_reset(
        cmd: Long,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_reset(cmd)
    }

    external fun jni_VkCommandBufferResource_reset(
        cmd: Long

    ) : kotlin.Unit

    override fun VkCommandBufferResource_begin(
        cmd: Long,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_begin(cmd)
    }

    external fun jni_VkCommandBufferResource_begin(
        cmd: Long

    ) : kotlin.Unit

    override fun VkCommandBufferResource_end(
        cmd: Long,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_end(cmd)
    }

    external fun jni_VkCommandBufferResource_end(
        cmd: Long

    ) : kotlin.Unit

    override fun VkCommandBufferResource_beginRenderPass(
        cmd: Long,
        renderTarget: Long,
        colorAttachmentIndex: Int,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_beginRenderPass(cmd, renderTarget, colorAttachmentIndex)
    }

    external fun jni_VkCommandBufferResource_beginRenderPass(
        cmd: Long, 
        renderTarget: Long, 
        colorAttachmentIndex: Int

    ) : kotlin.Unit

    override fun VkCommandBufferResource_endRenderPass(
        cmd: Long,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_endRenderPass(cmd)
    }

    external fun jni_VkCommandBufferResource_endRenderPass(
        cmd: Long

    ) : kotlin.Unit

    override fun VkCommandBufferResource_setPipe(
        cmd: Long,
        pipe: Long,
        frame: Int,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_setPipe(cmd, pipe, frame)
    }

    external fun jni_VkCommandBufferResource_setPipe(
        cmd: Long, 
        pipe: Long, 
        frame: Int

    ) : kotlin.Unit

    override fun VkCommandBufferResource_setComputePipe(
        cmd: Long,
        pipe: Long,
        frame: Int,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_setComputePipe(cmd, pipe, frame)
    }

    external fun jni_VkCommandBufferResource_setComputePipe(
        cmd: Long, 
        pipe: Long, 
        frame: Int

    ) : kotlin.Unit

    override fun VkCommandBufferResource_setViewport(
        cmd: Long,
        x: Float,
        y: Float,
        width: Float,
        height: Float,
        minDepth: Float,
        maxDepth: Float,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_setViewport(cmd, x, y, width, height, minDepth, maxDepth)
    }

    external fun jni_VkCommandBufferResource_setViewport(
        cmd: Long, 
        x: Float, 
        y: Float, 
        width: Float, 
        height: Float, 
        minDepth: Float, 
        maxDepth: Float

    ) : kotlin.Unit

    override fun VkCommandBufferResource_setScissor(
        cmd: Long,
        x: Int,
        y: Int,
        w: Int,
        h: Int,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_setScissor(cmd, x, y, w, h)
    }

    external fun jni_VkCommandBufferResource_setScissor(
        cmd: Long, 
        x: Int, 
        y: Int, 
        w: Int, 
        h: Int

    ) : kotlin.Unit

    override fun VkCommandBufferResource_addSecondaryBuffer(
        cmd: Long,
        secondaryBuffer: Long,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_addSecondaryBuffer(cmd, secondaryBuffer)
    }

    external fun jni_VkCommandBufferResource_addSecondaryBuffer(
        cmd: Long, 
        secondaryBuffer: Long

    ) : kotlin.Unit

    override fun VkCommandBufferResource_draw(
        cmd: Long,
        vertices: Int,
        vertexOffset: Int,
        instances: Int,
        instanceOffset: Int,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_draw(cmd, vertices, vertexOffset, instances, instanceOffset)
    }

    external fun jni_VkCommandBufferResource_draw(
        cmd: Long, 
        vertices: Int, 
        vertexOffset: Int, 
        instances: Int, 
        instanceOffset: Int

    ) : kotlin.Unit

    override fun VkCommandBufferResource_drawIndexed(
        cmd: Long,
        vertices: Int,
        vertexOffset: Int,
        indices: Int,
        indexOffset: Int,
        instances: Int,
        instanceOffset: Int,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_drawIndexed(cmd, vertices, vertexOffset, indices, indexOffset, instances, instanceOffset)
    }

    external fun jni_VkCommandBufferResource_drawIndexed(
        cmd: Long, 
        vertices: Int, 
        vertexOffset: Int, 
        indices: Int, 
        indexOffset: Int, 
        instances: Int, 
        instanceOffset: Int

    ) : kotlin.Unit

    override fun VkCommandBufferResource_drawIndexedIndirect(
        cmd: Long,
        indirectBuffer: Long,
        offset: Int,
        drawCount: Int,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_drawIndexedIndirect(cmd, indirectBuffer, offset, drawCount)
    }

    external fun jni_VkCommandBufferResource_drawIndexedIndirect(
        cmd: Long, 
        indirectBuffer: Long, 
        offset: Int, 
        drawCount: Int

    ) : kotlin.Unit

    override fun VkCommandBufferResource_copyBufferToBuffer(
        cmd: Long,
        src: Long,
        dst: Long,
        srcOffset: Int,
        dstOffset: Int,
        size: Int,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_copyBufferToBuffer(cmd, src, dst, srcOffset, dstOffset, size)
    }

    external fun jni_VkCommandBufferResource_copyBufferToBuffer(
        cmd: Long, 
        src: Long, 
        dst: Long, 
        srcOffset: Int, 
        dstOffset: Int, 
        size: Int

    ) : kotlin.Unit

    override fun VkCommandBufferResource_copyBufferToImage(
        cmd: Long,
        src: Long,
        dst: Long,
        dstMipLevel: Int,
        dstWidth: Int,
        dstHeight: Int,
        dstDepth: Int,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_copyBufferToImage(cmd, src, dst, dstMipLevel, dstWidth, dstHeight, dstDepth)
    }

    external fun jni_VkCommandBufferResource_copyBufferToImage(
        cmd: Long, 
        src: Long, 
        dst: Long, 
        dstMipLevel: Int, 
        dstWidth: Int, 
        dstHeight: Int, 
        dstDepth: Int

    ) : kotlin.Unit

    override fun VkCommandBufferResource_copyImageToImage(
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
        depth: Int,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_copyImageToImage(cmd, src, dst, srcX, srcY, srcZ, dstX, dstY, dstZ, width, height, depth)
    }

    external fun jni_VkCommandBufferResource_copyImageToImage(
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

    ) : kotlin.Unit

    override fun VkCommandBufferResource_dispatch(
        cmd: Long,
        groupsX: Int,
        groupsY: Int,
        groupsZ: Int,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_dispatch(cmd, groupsX, groupsY, groupsZ)
    }

    external fun jni_VkCommandBufferResource_dispatch(
        cmd: Long, 
        groupsX: Int, 
        groupsY: Int, 
        groupsZ: Int

    ) : kotlin.Unit

    override fun VkCommandBufferResource_pipelineBarrier(
        cmd: Long,
        srcStages: Int,
        dstStages: Int,
        srcAccessFlags: Int,
        dstAccessFlags: Int,
    ) : kotlin.Unit {
        jni_VkCommandBufferResource_pipelineBarrier(cmd, srcStages, dstStages, srcAccessFlags, dstAccessFlags)
    }

    external fun jni_VkCommandBufferResource_pipelineBarrier(
        cmd: Long, 
        srcStages: Int, 
        dstStages: Int, 
        srcAccessFlags: Int, 
        dstAccessFlags: Int

    ) : kotlin.Unit

}
