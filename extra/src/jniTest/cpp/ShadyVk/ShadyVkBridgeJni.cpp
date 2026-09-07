// Generated from Kotlin Extra library

#include "ShadyVkBridge.h"
#include "ExtraJni.h"

// -------------- ShadyVkBridge JNI -----------------

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_LogBridge_callback(JNIEnv* env, jobject thiz, jobject callbackByteBuffer, jbyteArray callbackByteArray)
{
    ShadyVkBridge_LogBridge_callback(
        JniDecode<VkFunction4>(callbackByteBuffer, callbackByteArray)
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_ResultBridge_callback(JNIEnv* env, jobject thiz, jobject callbackByteBuffer, jbyteArray callbackByteArray)
{
    ShadyVkBridge_ResultBridge_callback(
        JniDecode<VkFunction1>(callbackByteBuffer, callbackByteArray)
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_removeCallbacks(JNIEnv* env, jobject thiz)
{
    ShadyVkBridge_removeCallbacks(    );
}

extern "C" JNIEXPORT jlong Java_com_cws_extra_test_ShadyVkBridge_jni_VkContext_create(JNIEnv* env, jobject thiz, jobject surfaceByteBuffer, jbyteArray surfaceByteArray, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    return ShadyVkBridge_VkContext_create(
        JniDecode<VkAny>(surfaceByteBuffer, surfaceByteArray),

        JniDecode<VkRenderContextInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkContext_destroy(JNIEnv* env, jobject thiz, jlong context)
{
    ShadyVkBridge_VkContext_destroy(
        context
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkContext_setInfo(JNIEnv* env, jobject thiz, jlong context, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    ShadyVkBridge_VkContext_setInfo(
        context,

        JniDecode<VkRenderContextInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkContext_wait(JNIEnv* env, jobject thiz, jlong context)
{
    ShadyVkBridge_VkContext_wait(
        context
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkContext_resize(JNIEnv* env, jobject thiz, jlong context, jint width, jint height)
{
    ShadyVkBridge_VkContext_resize(
        context,

        width,

        height
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkContext_setSurface(JNIEnv* env, jobject thiz, jlong context, jobject surfaceByteBuffer, jbyteArray surfaceByteArray)
{
    ShadyVkBridge_VkContext_setSurface(
        context,

        JniDecode<VkAny>(surfaceByteBuffer, surfaceByteArray)
    );
}

extern "C" JNIEXPORT jlong Java_com_cws_extra_test_ShadyVkBridge_jni_VkContext_getRenderTarget(JNIEnv* env, jobject thiz, jlong context)
{
    return ShadyVkBridge_VkContext_getRenderTarget(
        context
    );
}

extern "C" JNIEXPORT jlong Java_com_cws_extra_test_ShadyVkBridge_jni_VkContext_getPrimaryCommandBuffer(JNIEnv* env, jobject thiz, jlong context, jint frame)
{
    return ShadyVkBridge_VkContext_getPrimaryCommandBuffer(
        context,

        frame
    );
}

extern "C" JNIEXPORT jlong Java_com_cws_extra_test_ShadyVkBridge_jni_VkContext_getSecondaryCommandBuffer(JNIEnv* env, jobject thiz, jlong context)
{
    return ShadyVkBridge_VkContext_getSecondaryCommandBuffer(
        context
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkContext_beginFrame(JNIEnv* env, jobject thiz, jlong context, jint frame)
{
    ShadyVkBridge_VkContext_beginFrame(
        context,

        frame
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkContext_endFrame(JNIEnv* env, jobject thiz, jlong context, jint frame)
{
    ShadyVkBridge_VkContext_endFrame(
        context,

        frame
    );
}

extern "C" JNIEXPORT jlong Java_com_cws_extra_test_ShadyVkBridge_jni_VkShader_create(JNIEnv* env, jobject thiz, jlong context, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    return ShadyVkBridge_VkShader_create(
        context,

        JniDecode<VkShaderInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkShader_destroy(JNIEnv* env, jobject thiz, jlong shader)
{
    ShadyVkBridge_VkShader_destroy(
        shader
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkShader_setInfo(JNIEnv* env, jobject thiz, jlong shader, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    ShadyVkBridge_VkShader_setInfo(
        shader,

        JniDecode<VkShaderInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT jlong Java_com_cws_extra_test_ShadyVkBridge_jni_VkBindingLayout_create(JNIEnv* env, jobject thiz, jlong context, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    return ShadyVkBridge_VkBindingLayout_create(
        context,

        JniDecode<VkBindingInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkBindingLayout_destroy(JNIEnv* env, jobject thiz, jlong layout)
{
    ShadyVkBridge_VkBindingLayout_destroy(
        layout
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkBindingLayout_setInfo(JNIEnv* env, jobject thiz, jlong layout, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    ShadyVkBridge_VkBindingLayout_setInfo(
        layout,

        JniDecode<VkBindingInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT jlong Java_com_cws_extra_test_ShadyVkBridge_jni_VkRenderTarget_create(JNIEnv* env, jobject thiz, jlong context, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    return ShadyVkBridge_VkRenderTarget_create(
        context,

        JniDecode<VkRenderTargetInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkRenderTarget_destroy(JNIEnv* env, jobject thiz, jlong target)
{
    ShadyVkBridge_VkRenderTarget_destroy(
        target
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkRenderTarget_setInfo(JNIEnv* env, jobject thiz, jlong target, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    ShadyVkBridge_VkRenderTarget_setInfo(
        target,

        JniDecode<VkRenderTargetInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkRenderTarget_resize(JNIEnv* env, jobject thiz, jlong target, jint width, jint height)
{
    ShadyVkBridge_VkRenderTarget_resize(
        target,

        width,

        height
    );
}

extern "C" JNIEXPORT jlong Java_com_cws_extra_test_ShadyVkBridge_jni_VkBufferResource_create(JNIEnv* env, jobject thiz, jlong context, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    return ShadyVkBridge_VkBufferResource_create(
        context,

        JniDecode<VkBufferInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkBufferResource_destroy(JNIEnv* env, jobject thiz, jlong buffer)
{
    ShadyVkBridge_VkBufferResource_destroy(
        buffer
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkBufferResource_setInfo(JNIEnv* env, jobject thiz, jlong buffer, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    ShadyVkBridge_VkBufferResource_setInfo(
        buffer,

        JniDecode<VkBufferInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT jlong Java_com_cws_extra_test_ShadyVkBridge_jni_VkBufferResource_map(JNIEnv* env, jobject thiz, jlong buffer, jint frame)
{
    return ShadyVkBridge_VkBufferResource_map(
        buffer,

        frame
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkBufferResource_unmap(JNIEnv* env, jobject thiz, jlong buffer)
{
    ShadyVkBridge_VkBufferResource_unmap(
        buffer
    );
}

extern "C" JNIEXPORT jlong Java_com_cws_extra_test_ShadyVkBridge_jni_VkSamplerResource_create(JNIEnv* env, jobject thiz, jlong context, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    return ShadyVkBridge_VkSamplerResource_create(
        context,

        JniDecode<VkSamplerInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkSamplerResource_destroy(JNIEnv* env, jobject thiz, jlong sampler)
{
    ShadyVkBridge_VkSamplerResource_destroy(
        sampler
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkSamplerResource_setInfo(JNIEnv* env, jobject thiz, jlong sampler, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    ShadyVkBridge_VkSamplerResource_setInfo(
        sampler,

        JniDecode<VkSamplerInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT jlong Java_com_cws_extra_test_ShadyVkBridge_jni_VkTextureResource_create(JNIEnv* env, jobject thiz, jlong context, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    return ShadyVkBridge_VkTextureResource_create(
        context,

        JniDecode<VkTextureInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkTextureResource_destroy(JNIEnv* env, jobject thiz, jlong texture)
{
    ShadyVkBridge_VkTextureResource_destroy(
        texture
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkTextureResource_setInfo(JNIEnv* env, jobject thiz, jlong texture, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    ShadyVkBridge_VkTextureResource_setInfo(
        texture,

        JniDecode<VkTextureInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT jlong Java_com_cws_extra_test_ShadyVkBridge_jni_VkTextureResource_map(JNIEnv* env, jobject thiz, jlong texture, jint frame)
{
    return ShadyVkBridge_VkTextureResource_map(
        texture,

        frame
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkTextureResource_unmap(JNIEnv* env, jobject thiz, jlong texture)
{
    ShadyVkBridge_VkTextureResource_unmap(
        texture
    );
}

extern "C" JNIEXPORT jlong Java_com_cws_extra_test_ShadyVkBridge_jni_VkPipe_create(JNIEnv* env, jobject thiz, jlong context, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    return ShadyVkBridge_VkPipe_create(
        context,

        JniDecode<VkRenderPipelineInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkPipe_destroy(JNIEnv* env, jobject thiz, jlong pipe)
{
    ShadyVkBridge_VkPipe_destroy(
        pipe
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkPipe_setInfo(JNIEnv* env, jobject thiz, jlong pipe, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    ShadyVkBridge_VkPipe_setInfo(
        pipe,

        JniDecode<VkRenderPipelineInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT jlong Java_com_cws_extra_test_ShadyVkBridge_jni_VkComputePipe_create(JNIEnv* env, jobject thiz, jlong context, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    return ShadyVkBridge_VkComputePipe_create(
        context,

        JniDecode<VkComputePipelineInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkComputePipe_destroy(JNIEnv* env, jobject thiz, jlong pipe)
{
    ShadyVkBridge_VkComputePipe_destroy(
        pipe
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkComputePipe_setInfo(JNIEnv* env, jobject thiz, jlong pipe, jobject infoByteBuffer, jbyteArray infoByteArray)
{
    ShadyVkBridge_VkComputePipe_setInfo(
        pipe,

        JniDecode<VkComputePipelineInfo>(infoByteBuffer, infoByteArray)
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_reset(JNIEnv* env, jobject thiz, jlong cmd)
{
    ShadyVkBridge_VkCommandBufferResource_reset(
        cmd
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_begin(JNIEnv* env, jobject thiz, jlong cmd)
{
    ShadyVkBridge_VkCommandBufferResource_begin(
        cmd
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_end(JNIEnv* env, jobject thiz, jlong cmd)
{
    ShadyVkBridge_VkCommandBufferResource_end(
        cmd
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_beginRenderPass(JNIEnv* env, jobject thiz, jlong cmd, jlong renderTarget, jint colorAttachmentIndex)
{
    ShadyVkBridge_VkCommandBufferResource_beginRenderPass(
        cmd,

        renderTarget,

        colorAttachmentIndex
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_endRenderPass(JNIEnv* env, jobject thiz, jlong cmd)
{
    ShadyVkBridge_VkCommandBufferResource_endRenderPass(
        cmd
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_setPipe(JNIEnv* env, jobject thiz, jlong cmd, jlong pipe, jint frame)
{
    ShadyVkBridge_VkCommandBufferResource_setPipe(
        cmd,

        pipe,

        frame
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_setComputePipe(JNIEnv* env, jobject thiz, jlong cmd, jlong pipe, jint frame)
{
    ShadyVkBridge_VkCommandBufferResource_setComputePipe(
        cmd,

        pipe,

        frame
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_setViewport(JNIEnv* env, jobject thiz, jlong cmd, jfloat x, jfloat y, jfloat width, jfloat height, jfloat minDepth, jfloat maxDepth)
{
    ShadyVkBridge_VkCommandBufferResource_setViewport(
        cmd,

        x,

        y,

        width,

        height,

        minDepth,

        maxDepth
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_setScissor(JNIEnv* env, jobject thiz, jlong cmd, jint x, jint y, jint w, jint h)
{
    ShadyVkBridge_VkCommandBufferResource_setScissor(
        cmd,

        x,

        y,

        w,

        h
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_addSecondaryBuffer(JNIEnv* env, jobject thiz, jlong cmd, jlong secondaryBuffer)
{
    ShadyVkBridge_VkCommandBufferResource_addSecondaryBuffer(
        cmd,

        secondaryBuffer
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_draw(JNIEnv* env, jobject thiz, jlong cmd, jint vertices, jint vertexOffset, jint instances, jint instanceOffset)
{
    ShadyVkBridge_VkCommandBufferResource_draw(
        cmd,

        vertices,

        vertexOffset,

        instances,

        instanceOffset
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_drawIndexed(JNIEnv* env, jobject thiz, jlong cmd, jint vertices, jint vertexOffset, jint indices, jint indexOffset, jint instances, jint instanceOffset)
{
    ShadyVkBridge_VkCommandBufferResource_drawIndexed(
        cmd,

        vertices,

        vertexOffset,

        indices,

        indexOffset,

        instances,

        instanceOffset
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_drawIndexedIndirect(JNIEnv* env, jobject thiz, jlong cmd, jlong indirectBuffer, jint offset, jint drawCount)
{
    ShadyVkBridge_VkCommandBufferResource_drawIndexedIndirect(
        cmd,

        indirectBuffer,

        offset,

        drawCount
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_copyBufferToBuffer(JNIEnv* env, jobject thiz, jlong cmd, jlong src, jlong dst, jint srcOffset, jint dstOffset, jint size)
{
    ShadyVkBridge_VkCommandBufferResource_copyBufferToBuffer(
        cmd,

        src,

        dst,

        srcOffset,

        dstOffset,

        size
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_copyBufferToImage(JNIEnv* env, jobject thiz, jlong cmd, jlong src, jlong dst, jint dstMipLevel, jint dstWidth, jint dstHeight, jint dstDepth)
{
    ShadyVkBridge_VkCommandBufferResource_copyBufferToImage(
        cmd,

        src,

        dst,

        dstMipLevel,

        dstWidth,

        dstHeight,

        dstDepth
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_copyImageToImage(JNIEnv* env, jobject thiz, jlong cmd, jlong src, jlong dst, jint srcX, jint srcY, jint srcZ, jint dstX, jint dstY, jint dstZ, jint width, jint height, jint depth)
{
    ShadyVkBridge_VkCommandBufferResource_copyImageToImage(
        cmd,

        src,

        dst,

        srcX,

        srcY,

        srcZ,

        dstX,

        dstY,

        dstZ,

        width,

        height,

        depth
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_dispatch(JNIEnv* env, jobject thiz, jlong cmd, jint groupsX, jint groupsY, jint groupsZ)
{
    ShadyVkBridge_VkCommandBufferResource_dispatch(
        cmd,

        groupsX,

        groupsY,

        groupsZ
    );
}

extern "C" JNIEXPORT void Java_com_cws_extra_test_ShadyVkBridge_jni_VkCommandBufferResource_pipelineBarrier(JNIEnv* env, jobject thiz, jlong cmd, jint srcStages, jint dstStages, jint srcAccessFlags, jint dstAccessFlags)
{
    ShadyVkBridge_VkCommandBufferResource_pipelineBarrier(
        cmd,

        srcStages,

        dstStages,

        srcAccessFlags,

        dstAccessFlags
    );
}
