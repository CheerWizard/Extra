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
#include "../api/Vk.h"

#include <jni.h>

#include "../api/LogBridge.h"
#include "../api/ResultBridge.h"

#include "../core/logger.hpp"

#ifdef ANDROID
#include <android/native_window_jni.h>
#include <vulkan/vulkan_android.h>
#endif

static JavaVM* vm = nullptr;

// LogBridge globals
static jobject log_bridge_callback = nullptr;
static jclass log_bridge_class = nullptr;
static jmethodID log_bridge_method = nullptr;

// ResultBridge globals
static jobject result_bridge_callback = nullptr;
static jclass result_bridge_class = nullptr;
static jmethodID result_bridge_method = nullptr;

void LogBridge_callback(int level, const char* tag, const char* message, const char* exceptionMessage);
void ResultBridge_callback(VkResult result);

extern "C"
JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_LogBridge_setCallback(
    JNIEnv* env, jobject /*thiz*/,
    jobject callback
) {
    LogBridge_init(LogBridge_callback);
    env->GetJavaVM(&vm);
    if (log_bridge_callback) {
        env->DeleteGlobalRef(log_bridge_callback);
    }
    log_bridge_callback = env->NewGlobalRef(callback);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_LogBridge_removeCallback(
        JNIEnv* env, jobject /*thiz*/,
        jobject callback
) {
    LogBridge_init(nullptr);
    env->GetJavaVM(&vm);
    if (log_bridge_callback) {
        env->DeleteGlobalRef(log_bridge_callback);
    }
    log_bridge_callback = nullptr;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_ResultBridge_setCallback(
    JNIEnv* env, jobject /*thiz*/,
    jobject callback
) {
    ResultBridge_init(ResultBridge_callback);
    env->GetJavaVM(&vm);
    if (result_bridge_callback) {
        env->DeleteGlobalRef(result_bridge_callback);
    }
    result_bridge_callback = env->NewGlobalRef(callback);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_ResultBridge_removeCallback(
        JNIEnv* env, jobject /*thiz*/,
        jobject callback
) {
    ResultBridge_init(nullptr);
    env->GetJavaVM(&vm);
    if (result_bridge_callback) {
        env->DeleteGlobalRef(result_bridge_callback);
    }
    result_bridge_callback = nullptr;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_removeCallbacks(
        JNIEnv* env, jobject /*thiz*/
) {
    vm = nullptr;
    log_bridge_callback = nullptr;
    result_bridge_callback = nullptr;
}

void LogBridge_callback(int level, const char* tag, const char* message, const char* exceptionMessage) {
    if (!vm || !log_bridge_callback) return;

    JNIEnv* env = nullptr;
    bool detach = false;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        vm->AttachCurrentThread(&env, nullptr);
        detach = true;
    }

    jstring jtag = env->NewStringUTF(tag);
    jstring jmessage = env->NewStringUTF(message);
    jstring jexception = nullptr;
    if (exceptionMessage) {
        jexception = env->NewStringUTF(exceptionMessage);
    }

    if (log_bridge_class == nullptr) {
        log_bridge_class = env->GetObjectClass(log_bridge_callback);
        log_bridge_method = env->GetMethodID(log_bridge_class, "invoke", "(Ljava/lang/Object;)Ljava/lang/Object;");
    }

    env->CallObjectMethod(log_bridge_callback, log_bridge_method, level, jtag, jmessage, jexception);

    env->DeleteLocalRef(jtag);
    env->DeleteLocalRef(jmessage);
    if (jexception) {
        env->DeleteLocalRef(jexception);
    }

    if (detach) {
        vm->DetachCurrentThread();
    }
}

void ResultBridge_callback(VkResult result) {
    if (!vm || !result_bridge_callback) return;

    JNIEnv* env = nullptr;
    bool detach = false;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        vm->AttachCurrentThread(&env, nullptr);
        detach = true;
    }

    if (result_bridge_class == nullptr) {
        result_bridge_class = env->GetObjectClass(result_bridge_callback);
        result_bridge_method = env->GetMethodID(result_bridge_class, "invoke", "(Ljava/lang/Object;)Ljava/lang/Object;");
    }

    env->CallVoidMethod(result_bridge_callback, result_bridge_method, result);

    if (detach) {
        vm->DetachCurrentThread();
    }
}

JNIEXPORT jlong JNICALL
Java_com_cws_kanvas_vk_Vk_VkContext_create(
        JNIEnv* env,
        jclass,
        jobject surface,
        jobject infoBuffer) {

    void* nativeWindow = nullptr;

#ifdef ANDROID
    if (surface) {
        nativeWindow = ANativeWindow_fromSurface(env, surface);
    } else {
        LOG_ERROR("VK.jni", "Failed to obtain ANativeWindow, surface = null");
    }
#endif

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) {
        return 0;
    }

    auto* info = reinterpret_cast<VkContextInfo*>(ptr);
    VkContext* ctx = VkContext_create(nativeWindow, info);
    return reinterpret_cast<jlong>(ctx);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkContext_destroy(
        JNIEnv*,
        jclass,
        jlong context) {

    auto* ctx = reinterpret_cast<VkContext*>(context);
    VkContext_destroy(ctx);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkContext_setInfo(
        JNIEnv* env,
        jclass,
        jlong context,
        jobject infoBuffer) {

    auto* ctx = reinterpret_cast<VkContext*>(context);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return;

    auto* info = reinterpret_cast<VkContextInfo*>(ptr);

    VkContext_setInfo(ctx, info);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkContext_wait(
        JNIEnv*,
        jclass,
        jlong context) {

    auto* ctx = reinterpret_cast<VkContext*>(context);
    VkContext_wait(ctx);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkContext_resize(
        JNIEnv*,
        jclass,
        jlong context,
        jint width,
        jint height) {

    auto* ctx = reinterpret_cast<VkContext*>(context);
    VkContext_resize(ctx, width, height);
}

JNIEXPORT jlong JNICALL
Java_com_cws_kanvas_vk_Vk_VkContext_getRenderTarget(
        JNIEnv*,
        jclass,
        jlong context) {

    auto* ctx = reinterpret_cast<VkContext*>(context);
    return reinterpret_cast<jlong>(VkContext_getRenderTarget(ctx));
}

JNIEXPORT jlong JNICALL
Java_com_cws_kanvas_vk_Vk_VkContext_getPrimaryCommandBuffer(
        JNIEnv*,
        jclass,
        jlong context,
        jint frame) {

    auto* ctx = reinterpret_cast<VkContext*>(context);
    return reinterpret_cast<jlong>(
        VkContext_getPrimaryCommandBuffer(ctx, frame));
}

JNIEXPORT jlong JNICALL
Java_com_cws_kanvas_vk_Vk_VkContext_getSecondaryCommandBuffer(
        JNIEnv*,
        jclass,
        jlong context) {

    auto* ctx = reinterpret_cast<VkContext*>(context);
    return reinterpret_cast<jlong>(
        VkContext_getSecondaryCommandBuffer(ctx));
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkContext_beginFrame(
        JNIEnv*,
        jclass,
        jlong context,
        jint frame) {

    auto* ctx = reinterpret_cast<VkContext*>(context);
    VkContext_beginFrame(ctx, frame);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkContext_endFrame(
        JNIEnv*,
        jclass,
        jlong context,
        jint frame) {

    auto* ctx = reinterpret_cast<VkContext*>(context);
    VkContext_endFrame(ctx, frame);
}

// --------------------------------------------------
// VkShader
// --------------------------------------------------

JNIEXPORT jlong JNICALL
Java_com_cws_kanvas_vk_Vk_VkShader_create(
        JNIEnv* env,
        jclass,
        jlong context,
        jobject infoBuffer) {

    auto* ctx = reinterpret_cast<VkContext*>(context);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return 0;

    auto* info = reinterpret_cast<VkShaderInfo*>(ptr);

    return reinterpret_cast<jlong>(
        VkShader_create(ctx, info));
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkShader_destroy(
        JNIEnv*,
        jclass,
        jlong shader) {

    auto* s = reinterpret_cast<VkShader*>(shader);
    VkShader_destroy(s);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkShader_setInfo(
        JNIEnv* env,
        jclass,
        jlong shader,
        jobject infoBuffer) {

    auto* s = reinterpret_cast<VkShader*>(shader);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return;

    auto* info = reinterpret_cast<VkShaderInfo*>(ptr);

    VkShader_setInfo(s, info);
}

// --------------------------------------------------
// VkBindingLayout
// --------------------------------------------------

JNIEXPORT jlong JNICALL
Java_com_cws_kanvas_vk_Vk_VkBindingLayout_create(
        JNIEnv* env,
        jclass,
        jlong context,
        jobject infoBuffer) {

    auto* ctx = reinterpret_cast<VkContext*>(context);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return 0;

    auto* info = reinterpret_cast<VkBindingInfo*>(ptr);

    return reinterpret_cast<jlong>(
        VkBindingLayout_create(ctx, info));
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkBindingLayout_destroy(
        JNIEnv*,
        jclass,
        jlong layout) {

    auto* l = reinterpret_cast<VkBindingLayout*>(layout);
    VkBindingLayout_destroy(l);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkBindingLayout_setInfo(
        JNIEnv* env,
        jclass,
        jlong layout,
        jobject infoBuffer) {

    auto* l = reinterpret_cast<VkBindingLayout*>(layout);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return;

    auto* info = reinterpret_cast<VkBindingInfo*>(ptr);

    VkBindingLayout_setInfo(l, info);
}

// --------------------------------------------------
// VkRenderTarget
// --------------------------------------------------

JNIEXPORT jlong JNICALL
Java_com_cws_kanvas_vk_Vk_VkRenderTarget_create(
        JNIEnv* env,
        jclass,
        jlong context,
        jobject infoBuffer) {

    auto* ctx = reinterpret_cast<VkContext*>(context);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return 0;

    auto* info = reinterpret_cast<VkRenderTargetInfo*>(ptr);

    return reinterpret_cast<jlong>(
        VkRenderTarget_create(ctx, info));
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkRenderTarget_destroy(
        JNIEnv*,
        jclass,
        jlong target) {

    auto* t = reinterpret_cast<VkRenderTarget*>(target);
    VkRenderTarget_destroy(t);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkRenderTarget_setInfo(
        JNIEnv* env,
        jclass,
        jlong target,
        jobject infoBuffer) {

    auto* t = reinterpret_cast<VkRenderTarget*>(target);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return;

    auto* info = reinterpret_cast<VkRenderTargetInfo*>(ptr);

    VkRenderTarget_setInfo(t, info);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkRenderTarget_resize(
        JNIEnv*,
        jclass,
        jlong target,
        jint width,
        jint height) {

    auto* t = reinterpret_cast<VkRenderTarget*>(target);
    VkRenderTarget_resize(t, width, height);
}

// --------------------------------------------------
// VkBufferResource
// --------------------------------------------------

JNIEXPORT jlong JNICALL
Java_com_cws_kanvas_vk_Vk_VkBufferResource_create(
        JNIEnv* env,
        jclass,
        jlong context,
        jobject infoBuffer) {

    auto* ctx = reinterpret_cast<VkContext*>(context);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return 0;

    auto* info = reinterpret_cast<VkBufferInfo*>(ptr);

    return reinterpret_cast<jlong>(
        VkBufferResource_create(ctx, info));
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkBufferResource_destroy(
        JNIEnv*,
        jclass,
        jlong buffer) {

    auto* b = reinterpret_cast<VkBufferResource*>(buffer);
    VkBufferResource_destroy(b);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkBufferResource_setInfo(
        JNIEnv* env,
        jclass,
        jlong buffer,
        jobject infoBuffer) {

    auto* b = reinterpret_cast<VkBufferResource*>(buffer);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return;

    auto* info = reinterpret_cast<VkBufferInfo*>(ptr);

    VkBufferResource_setInfo(b, info);
}

JNIEXPORT jlong JNICALL
Java_com_cws_kanvas_vk_Vk_VkBufferResource_map(
        JNIEnv*,
        jclass,
        jlong buffer,
        jint frame) {

    auto* b = reinterpret_cast<VkBufferResource*>(buffer);
    return reinterpret_cast<jlong>(
        VkBufferResource_map(b, frame));
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkBufferResource_unmap(
        JNIEnv*,
        jclass,
        jlong buffer) {

    auto* b = reinterpret_cast<VkBufferResource*>(buffer);
    VkBufferResource_unmap(b);
}

// --------------------------------------------------
// VkSamplerResource
// --------------------------------------------------

JNIEXPORT jlong JNICALL
Java_com_cws_kanvas_vk_Vk_VkSamplerResource_create(
        JNIEnv* env,
        jclass,
        jlong context,
        jobject infoBuffer) {

    auto* ctx = reinterpret_cast<VkContext*>(context);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return 0;

    auto* info = reinterpret_cast<VkSamplerInfo*>(ptr);

    return reinterpret_cast<jlong>(
        VkSamplerResource_create(ctx, info));
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkSamplerResource_destroy(
        JNIEnv*,
        jclass,
        jlong sampler) {

    auto* s = reinterpret_cast<VkSamplerResource*>(sampler);
    VkSamplerResource_destroy(s);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkSamplerResource_setInfo(
        JNIEnv* env,
        jclass,
        jlong sampler,
        jobject infoBuffer) {

    auto* s = reinterpret_cast<VkSamplerResource*>(sampler);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return;

    auto* info = reinterpret_cast<VkSamplerInfo*>(ptr);

    VkSamplerResource_setInfo(s, info);
}

// --------------------------------------------------
// VkTextureResource
// --------------------------------------------------

JNIEXPORT jlong JNICALL
Java_com_cws_kanvas_vk_Vk_VkTextureResource_create(
        JNIEnv* env,
        jclass,
        jlong context,
        jobject infoBuffer) {

    auto* ctx = reinterpret_cast<VkContext*>(context);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return 0;

    auto* info = reinterpret_cast<VkTextureInfo*>(ptr);

    return reinterpret_cast<jlong>(
        VkTextureResource_create(ctx, info));
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkTextureResource_destroy(
        JNIEnv*,
        jclass,
        jlong tex) {

    auto* t = reinterpret_cast<VkTextureResource*>(tex);
    VkTextureResource_destroy(t);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkTextureResource_setInfo(
        JNIEnv* env,
        jclass,
        jlong tex,
        jobject infoBuffer) {

    auto* t = reinterpret_cast<VkTextureResource*>(tex);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return;

    auto* info = reinterpret_cast<VkTextureInfo*>(ptr);

    VkTextureResource_setInfo(t, info);
}


JNIEXPORT jlong JNICALL
Java_com_cws_kanvas_vk_Vk_VkTextureResource_map(
        JNIEnv*,
        jclass,
        jlong tex,
        jint frame) {

    auto* t = reinterpret_cast<VkTextureResource*>(tex);
    return reinterpret_cast<jlong>(
        VkTextureResource_map(t, frame));
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkTextureResource_unmap(
        JNIEnv*,
        jclass,
        jlong tex) {

    auto* t = reinterpret_cast<VkTextureResource*>(tex);
    VkTextureResource_unmap(t);
}

// --------------------------------------------------
// VkPipe
// --------------------------------------------------

JNIEXPORT jlong JNICALL
Java_com_cws_kanvas_vk_Vk_VkPipe_create(
        JNIEnv* env,
        jclass,
        jlong context,
        jobject infoBuffer) {

    auto* ctx = reinterpret_cast<VkContext*>(context);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return 0;

    auto* info = reinterpret_cast<VkPipeInfo*>(ptr);

    return reinterpret_cast<jlong>(VkPipe_create(ctx, info));
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkPipe_destroy(
        JNIEnv*,
        jclass,
        jlong pipe) {

    auto* p = reinterpret_cast<VkPipe*>(pipe);
    VkPipe_destroy(p);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkPipe_setInfo(
        JNIEnv* env,
        jclass,
        jlong pipe,
        jobject infoBuffer) {

    auto* p = reinterpret_cast<VkPipe*>(pipe);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return;

    auto* info = reinterpret_cast<VkPipeInfo*>(ptr);

    VkPipe_setInfo(p, info);
}

// --------------------------------------------------
// VkComputePipe
// --------------------------------------------------

JNIEXPORT jlong JNICALL
Java_com_cws_kanvas_vk_Vk_VkComputePipe_create(
        JNIEnv* env,
        jclass,
        jlong context,
        jobject infoBuffer) {

    auto* ctx = reinterpret_cast<VkContext*>(context);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return 0;

    auto* info = reinterpret_cast<VkComputePipeInfo*>(ptr);

    return reinterpret_cast<jlong>(VkComputePipe_create(ctx, info));
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkComputePipe_destroy(
        JNIEnv*,
        jclass,
        jlong pipe) {

    auto* p = reinterpret_cast<VkComputePipe*>(pipe);
    VkComputePipe_destroy(p);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkComputePipe_setInfo(
        JNIEnv* env,
        jclass,
        jlong pipe,
        jobject infoBuffer) {

    auto* p = reinterpret_cast<VkComputePipe*>(pipe);

    void* ptr = env->GetDirectBufferAddress(infoBuffer);
    if (!ptr) return;

    auto* info = reinterpret_cast<VkComputePipeInfo*>(ptr);

    VkComputePipe_setInfo(p, info);
}

// --------------------------------------------------
// VkCommandBufferResource
// --------------------------------------------------

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_reset(
        JNIEnv*,
        jclass,
        jlong cmd) {

    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);
    VkCommandBufferResource_reset(c);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_begin(
        JNIEnv*,
        jclass,
        jlong cmd) {

    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);
    VkCommandBufferResource_begin(c);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_end(
        JNIEnv*,
        jclass,
        jlong cmd) {

    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);
    VkCommandBufferResource_end(c);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_beginRenderPass(
        JNIEnv*,
        jclass,
        jlong cmd,
        jlong renderTarget,
        jint colorAttachmentIndex) {

    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);
    auto* rt = reinterpret_cast<VkRenderTarget*>(renderTarget);

    VkCommandBufferResource_beginRenderPass(c, rt, colorAttachmentIndex);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_endRenderPass(
        JNIEnv*,
        jclass,
        jlong cmd) {

    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);
    VkCommandBufferResource_endRenderPass(c);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_setPipe(
        JNIEnv*,
        jclass,
        jlong cmd,
        jlong pipe,
        jint frame) {

    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);
    auto* p = reinterpret_cast<VkPipe*>(pipe);

    VkCommandBufferResource_setPipe(c, p, frame);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_setComputePipe(
        JNIEnv*,
        jclass,
        jlong cmd,
        jlong pipe,
        jint frame) {

    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);
    auto* p = reinterpret_cast<VkComputePipe*>(pipe);

    VkCommandBufferResource_setComputePipe(c, p, frame);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_setViewport(
        JNIEnv*,
        jclass,
        jlong cmd,
        jfloat x,
        jfloat y,
        jfloat width,
        jfloat height,
        jfloat minDepth,
        jfloat maxDepth) {

    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);

    VkCommandBufferResource_setViewport(
        c, x, y, width, height, minDepth, maxDepth);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_setScissor(
        JNIEnv*,
        jclass,
        jlong cmd,
        jint x,
        jint y,
        jint w,
        jint h) {

    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);
    VkCommandBufferResource_setScissor(c, x, y, w, h);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_addSecondaryBuffer(
        JNIEnv*,
        jclass,
        jlong commandBuffer,
        jlong secondaryBuffer) {

    auto* cmd = reinterpret_cast<VkCommandBufferResource*>(commandBuffer);
    auto* secondary = reinterpret_cast<VkCommandBufferResource*>(secondaryBuffer);
    VkCommandBufferResource_addSecondaryBuffer(cmd, secondary);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_addSecondaryBuffers(
        JNIEnv* env,
        jclass,
        jlong commandBuffer,
        jobject secondaryBuffers,
        jlong secondaryBuffersCount) {

    auto* cmd = reinterpret_cast<VkCommandBufferResource*>(commandBuffer);
    auto* secondaryCommands = reinterpret_cast<VkCommandBufferResource**>(env->GetDirectBufferAddress(secondaryBuffers));
    VkCommandBufferResource_addSecondaryBuffers(cmd, secondaryCommands, static_cast<size_t>(secondaryBuffersCount));
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_draw(
        JNIEnv*,
        jclass,
        jlong cmd,
        jint vertices,
        jint vertexOffset,
        jint instances,
        jint instanceOffset) {

    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);

    VkCommandBufferResource_draw(
        c, vertices, vertexOffset, instances, instanceOffset);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_drawIndexed(
        JNIEnv*,
        jclass,
        jlong cmd,
        jint vertices,
        jint vertexOffset,
        jint indices,
        jint indexOffset,
        jint instances,
        jint instanceOffset) {

    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);

    VkCommandBufferResource_drawIndexed(
        c, vertices, vertexOffset, indices,
        indexOffset, instances, instanceOffset);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_drawIndexedIndirect(
        JNIEnv*,
        jclass,
        jlong cmd,
        jlong indirectBuffer,
        jlong offset,
        jint drawCount) {

    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);
    auto* b = reinterpret_cast<VkBufferResource*>(indirectBuffer);

    VkCommandBufferResource_drawIndexedIndirect(
        c, b, offset, drawCount);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_copyBufferToBuffer(
        JNIEnv*,
        jclass,
        jlong cmd,
        jlong src,
        jlong dst,
        jlong srcOffset,
        jlong dstOffset,
        jlong size) {

    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);
    auto* s = reinterpret_cast<VkBufferResource*>(src);
    auto* d = reinterpret_cast<VkBufferResource*>(dst);

    VkCommandBufferResource_copyBufferToBuffer(
        c, s, d, srcOffset, dstOffset, size);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_copyBufferToImage(
        JNIEnv*,
        jclass,
        jlong cmd,
        jlong src,
        jlong dst,
        jint mip,
        jint w,
        jint h,
        jint dpth) {

    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);
    auto* s = reinterpret_cast<VkBufferResource*>(src);
    auto* t = reinterpret_cast<VkTextureResource*>(dst);

    VkCommandBufferResource_copyBufferToImage(
        c, s, t, mip, w, h, dpth);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_copyImageToImage(
        JNIEnv*,
        jclass,
        jlong cmd,
        jlong src,
        jlong dst,
        jint sx,
        jint sy,
        jint sz,
        jint dx,
        jint dy,
        jint dz,
        jint w,
        jint h,
        jint dpth) {

    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);
    auto* s = reinterpret_cast<VkTextureResource*>(src);
    auto* d = reinterpret_cast<VkTextureResource*>(dst);

    VkCommandBufferResource_copyImageToImage(
        c, s, d,
        sx, sy, sz,
        dx, dy, dz,
        w, h, dpth);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_dispatch(
        JNIEnv*,
        jclass,
        jlong cmd,
        jint groupsX,
        jint groupsY,
        jint groupsZ
) {
    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);
    VkCommandBufferResource_dispatch(c, groupsX, groupsY, groupsZ);
}

JNIEXPORT void JNICALL
Java_com_cws_kanvas_vk_Vk_VkCommandBufferResource_pipelineBarrier(
        JNIEnv*,
        jclass,
        jlong cmd,
        jint srcStages,
        jint dstStages,
        jint srcAccessFlags,
        jint dstAccessFlags
) {
    auto* c = reinterpret_cast<VkCommandBufferResource*>(cmd);
    VkCommandBufferResource_pipelineBarrier(c, srcStages, dstStages, srcAccessFlags, dstAccessFlags);
}
