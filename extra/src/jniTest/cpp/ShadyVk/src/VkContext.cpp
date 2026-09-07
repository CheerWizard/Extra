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
#include "VkContext.hpp"
#include "VkCheck.hpp"
#include "VkCommandBufferResource.hpp"
#include "VkDescriptors.hpp"
#include "VulkanAllocator.hpp"

#include "../core/logger.hpp"

#ifdef ANDROID

#include <vulkan/vulkan_android.h>

#define SURFACE_EXTENSION_NAME VK_KHR_ANDROID_SURFACE_EXTENSION_NAME

#elif IOS

#include <vulkan/vulkan_ios.h>
#include <QuartzCore/CAMetalLayer.h>

#define SURFACE_EXTENSION_NAME VK_MVK_IOS_SURFACE_EXTENSION_NAME

#elif LINUX

#include <vulkan/vulkan_xlib.h>

#define SURFACE_EXTENSION_NAME VK_KHR_XLIB_SURFACE_EXTENSION_NAME

#elif WINDOWS

#include <vulkan/vulkan_win32.h>

#define SURFACE_EXTENSION_NAME VK_KHR_WIN32_SURFACE_EXTENSION_NAME

#elif MACOS

#include <vulkan/vulkan_macos.h>

#define SURFACE_EXTENSION_NAME VK_MVK_MACOS_SURFACE_EXTENSION_NAME

#endif

VkContext* VkContext_create(void* native_window, VkContextInfo* info) {
    return new VkContext(native_window, *info);
}

void VkContext_destroy(VkContext* context) {
    delete context;
}

void VkContext_setInfo(VkContext* context, VkContextInfo* info) {
    context->info = *info;
}

void VkContext_wait(VkContext* context) {
    context->wait();
}

void VkContext_resize(VkContext* context, u32 width, u32 height) {
    context->resize(width, height);
}

void VkContext_setSurface(VkContext* context, void* surface) {
    context->setSurface(surface);
}

VkRenderTarget* VkContext_getRenderTarget(VkContext* context) {
    return context->surface->render_target;
}

VkCommandBufferResource* VkContext_getPrimaryCommandBuffer(VkContext* context, u32 frame) {
    return context->getPrimaryCommandBuffer(frame);
}

VkCommandBufferResource* VkContext_getSecondaryCommandBuffer(VkContext* context) {
    return context->getSecondaryCommandBuffer();
}

void VkContext_beginFrame(VkContext* context, u32 frame) {
    context->beginFrame(frame);
}

void VkContext_endFrame(VkContext* context, u32 frame) {
    context->endFrame(frame);
}

#ifdef DEBUG

static VKAPI_ATTR VkBool32 VKAPI_CALL onDebugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* callbackData,
        void* userData
) {
    switch (messageSeverity) {
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
            LOG_WARNING("VkDebugger", "type=%d message=%s", messageType, callbackData->pMessage);
            break;
        case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
            LOG_WARNING("VkDebugger", "type=%d message=%s", messageType, callbackData->pMessage);
            break;
        default: break;
    }
    return VK_FALSE;
}

#endif

VkContext::VkContext(void* native_window, const VkContextInfo& info) : info(info) {
    VkApplicationInfo appInfo { VK_STRUCTURE_TYPE_APPLICATION_INFO };
    appInfo.pApplicationName = info.application_name;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = info.engine_name;
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo createInfo { VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
    createInfo.pApplicationInfo = &appInfo;

    std::vector<const char*> extension_names;

    if (native_window) {
        extension_names.emplace_back(VK_KHR_SURFACE_EXTENSION_NAME);
        extension_names.emplace_back(SURFACE_EXTENSION_NAME);
    }

#if defined(DEBUG)
    extension_names.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    extension_names.emplace_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
#endif

    createInfo.enabledExtensionCount = static_cast<uint32_t>(extension_names.size());
    createInfo.ppEnabledExtensionNames = extension_names.data();

    uint32_t count = 0;

    vkEnumerateInstanceLayerProperties(&count, nullptr);
    layers.resize(count);
    vkEnumerateInstanceLayerProperties(&count, layers.data());

    vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
    extension_names.resize(count);
    vkEnumerateInstanceExtensionProperties(nullptr, &count, extensions.data());

#ifdef DEBUG
        std::array validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        if (checkLayers(validationLayers.data(), validationLayers.size())) {
            createInfo.enabledLayerCount = static_cast<u32>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            LOG_WARNING(TAG, "Validation layers are not found!");
        }

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {
            .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
            .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
            .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
            .pfnUserCallback = onDebugCallback,
            .pUserData = nullptr,
        };

        VK_CHECK(vkCreateDebugUtilsMessengerEXT(instance, &debugCreateInfo, VK_CALLBACKS, &debug_utils));

        createInfo.pNext = &debugCreateInfo;

#endif

    volkInitialize();

    VK_CHECK(vkCreateInstance(&createInfo, VK_CALLBACKS, &instance));

    volkLoadInstance(instance);

    findDevice();

    surface = new VkSurface(this, findSurface(native_window), info.width, info.height);

    imageSemaphores.resize(info.frameCount);
    renderFinishedSemaphores.resize(info.frameCount);
    fences.resize(info.frameCount);
    primaryCommandBuffers.resize(info.frameCount);

    queue = getQueue();

    char debugName[16];

    for (int i = 0 ; i < info.frameCount ; i++) {
        sprintf(debugName, "%d", i);

        delete imageSemaphores[i];
        imageSemaphores[i] = new VkSemaphoreResource(device, debugName);

        delete renderFinishedSemaphores[i];
        renderFinishedSemaphores[i] = new VkSemaphoreResource(device, debugName);

        delete fences[i];
        fences[i] = new VkFenceResource(device, debugName, false);

        delete primaryCommandBuffers[i];
        primaryCommandBuffers[i] = new VkCommandBufferResource(*queue, debugName, true);
    }

    VkDescriptors::New(this);
}

VkContext::~VkContext() {
    // let GPU finish using resources
    wait();

    for (int i = 0 ; i < info.frameCount ; i++) {
        delete imageSemaphores[i];
        delete renderFinishedSemaphores[i];
        delete fences[i];
        delete primaryCommandBuffers[i];
    }
    imageSemaphores.clear();
    renderFinishedSemaphores.clear();
    fences.clear();
    primaryCommandBuffers.clear();

    for (auto& commandBuffer : secondaryCommandBuffers) {
        delete commandBuffer.second;
    }
    secondaryCommandBuffers.clear();

    VkDescriptors::Delete();

    delete surface;

    if (device) {
        vkDestroyDevice(device, VK_CALLBACKS);
        device = nullptr;
    }

    if (debug_utils) {
        vkDestroyDebugUtilsMessengerEXT(instance, debug_utils, VK_CALLBACKS);
        debug_utils = nullptr;
    }

    if (instance) {
        vkDestroyInstance(instance, VK_CALLBACKS);
        instance = nullptr;
    }

    VulkanAllocator::getInstance().Delete();
}

void VkContext::findDevice() {
    u32 count = 0;
    vkEnumeratePhysicalDevices(instance, &count, nullptr);

    ASSERT(count > 0, TAG, "Failed to find any GPU card");

    std::vector<VkPhysicalDevice> physical_devices(count);
    vkEnumeratePhysicalDevices(instance, &count, physical_devices.data());

    std::vector<VkQueueFamilyProperties> queue_families;

    // find a single device that supports graphics
    for (int i = 0 ; i < count ; i++) {
        auto physicalDevice = physical_devices[i];

        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, nullptr);
        queue_families.resize(count);
        vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, queue_families.data());

        for (u32 j = 0 ; j < count ; j++) {
            auto queueFlags = queue_families[j].queueFlags;
            if (queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                initDevice(physicalDevice);
                break;
            }
        }
    }

    ASSERT(device, TAG, "Failed to find suitable GPU with graphics queue!");

    volkLoadDevice(device);
}

bool VkContext::checkExtensions(const char **extensions, u32 count) {
    for (int i = 0 ; i < count ; i++) {
        if (checkExtension(extensions[i])) {
            return true;
        }
    }
    return false;
}

bool VkContext::checkLayers(const char **layers, u32 count) {
    for (int i = 0 ; i < count ; i++) {
        if (checkLayer(layers[i])) {
            return true;
        }
    }
    return false;
}

bool VkContext::checkExtension(const char *extension) {
    for (const auto& entry : extensions) {
        if (strcmp(extension, entry.extensionName) == 0) {
            return true;
        }
    }
    return false;
}

bool VkContext::checkLayer(const char *layer) {
    for (const auto& entry : layers) {
        if (strcmp(layer, entry.layerName) == 0) {
            return true;
        }
    }
    return false;
}

void VkContext::initDevice(VkPhysicalDevice physicalDevice) {
    u32 count = 0;

    vkEnumerateDeviceLayerProperties(physicalDevice, &count, nullptr);
    layers.resize(count);
    vkEnumerateDeviceLayerProperties(physicalDevice, &count, layers.data());

    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &count, nullptr);
    extensions.resize(count);
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &count, extensions.data());

    vkGetPhysicalDeviceProperties(physicalDevice, &properties);

    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, nullptr);
    queueFamilies.resize(count);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &count, queueFamilies.data());

    for (u32 i = 0 ; i < count ; i++) {
        auto queueFlags = queueFamilies[i].queueFlags;
        if (queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            queue_family_indices.graphics = i;
            queue_family_indices.present = i;
        } else if (queueFlags & VK_QUEUE_COMPUTE_BIT) {
            queue_family_indices.compute = i;
        } else if (queueFlags & VK_QUEUE_TRANSFER_BIT) {
            queue_family_indices.transfer = i;
        }
    }

    float queuePriority = 1.0f;

    VkDeviceQueueCreateInfo queueCreateInfo {
            .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
            .queueFamilyIndex = queue_family_indices.graphics,
            .queueCount = 1,
            .pQueuePriorities = &queuePriority,
    };

    VkDeviceCreateInfo createInfo {
            .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
            .pNext = nullptr,
            .queueCreateInfoCount = 1,
            .pQueueCreateInfos = &queueCreateInfo,
    };

    std::array extensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    };

    ASSERT(
            checkDeviceExtensions(extensions.data(), extensions.size()),
            TAG, "Failed to find required extensions for device"
    );

    createInfo.enabledExtensionCount = extensions.size();
    createInfo.ppEnabledExtensionNames = extensions.data();

    VK_CHECK(vkCreateDevice(physicalDevice, &createInfo, VK_CALLBACKS, &device));

    VulkanAllocator::getInstance().New(instance, physicalDevice, device);
}

bool VkContext::checkDeviceExtensions(const char **extensions, u32 count) {
    for (int i = 0 ; i < count ; i++) {
        if (checkDeviceExtension(extensions[i])) {
            return true;
        }
    }
    return false;
}

bool VkContext::checkDeviceLayers(const char **layers, u32 count) {
    for (int i = 0 ; i < count ; i++) {
        if (checkDeviceLayer(layers[i])) {
            return true;
        }
    }
    return false;
}

bool VkContext::checkDeviceExtension(const char *extension) {
    for (const auto& entry : extensions) {
        if (strcmp(extension, entry.extensionName) == 0) {
            return true;
        }
    }
    return false;
}

bool VkContext::checkDeviceLayer(const char *layer) {
    for (const auto& entry : layers) {
        if (strcmp(layer, entry.layerName) == 0) {
            return true;
        }
    }
    return false;
}

VkDeviceQueue* VkContext::getQueue() {
    // TODO: need to consider how to store it
    u32 family_index = queue_family_indices.graphics;

    std::lock_guard lock(queueMutex);

    auto thread_id = std::this_thread::get_id();

    if (queues[thread_id]) {
        return queues[thread_id];
    }

    std::ostringstream oss;
    oss << thread_id;
    auto debugName = oss.str();
    VkDeviceQueue* queue = new VkDeviceQueue(device, debugName.c_str(), family_index);
    queues[thread_id] = queue;
    return queue;
}

VkCommandBufferResource* VkContext::getPrimaryCommandBuffer(u32 frame) {
    return primaryCommandBuffers[frame];
}

VkCommandBufferResource* VkContext::getSecondaryCommandBuffer() {
    std::lock_guard lock(commandBufferMutex);

    auto thread_id = std::this_thread::get_id();

    if (secondaryCommandBuffers[thread_id]) {
        return secondaryCommandBuffers[thread_id];
    }

    std::ostringstream oss;
    oss << thread_id;
    auto debugName = oss.str();
    VkCommandBufferResource* commandBuffer = new VkCommandBufferResource(*getQueue(), debugName.c_str(), false);
    secondaryCommandBuffers[thread_id] = commandBuffer;
    return commandBuffer;
}

void VkContext::beginFrame(u32 frame) {
    const auto& fence = fences[frame];
    const auto& imageSemaphore = imageSemaphores[frame];
    const auto& commandBuffer = primaryCommandBuffers[frame];

    // wait for frame
    fence->wait();
    if (!surface->getImage(*imageSemaphore)) {
        // we can't proceed rendering without image to present
        return;
    }
    fence->reset();

    // begin main command
    commandBuffer->reset();
    commandBuffer->begin();
}

void VkContext::endFrame(u32 frame) {
    const auto& commandBuffer = primaryCommandBuffers[frame];
    const auto& imageSemaphore = imageSemaphores[frame];

    commandBuffer->end();
    commandBuffer->submit(imageSemaphore, renderFinishedSemaphores[frame], fences[frame]);
    bool presented = commandBuffer->present(surface, imageSemaphore);
    if (!presented || surface->needsRecreation) {
        surface->recreateSwapChain();
    }
}

void VkContext::wait() {
    if (device) {
        vkDeviceWaitIdle(device);
    }
}

void VkContext::resize(u32 width, u32 height) {
    surface->resize(width, height);
}

void VkContext::setSurface(void* surface) {
    this->surface->updateSurface(findSurface(surface));
}

#ifdef ANDROID

VkSurfaceKHR VkContext::findSurface(void* native_window) {
    VkAndroidSurfaceCreateInfoKHR createInfo {
            .sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR,
            .window = (ANativeWindow*) native_window,
    };
    VkSurfaceKHR surface;
    VK_CHECK(vkCreateAndroidSurfaceKHR(instance, &createInfo, VK_CALLBACKS, &surface));
    VK_DEBUG_NAME(device, VK_OBJECT_TYPE_SURFACE_KHR, surface, "VkSurface-Android");
    return surface;
}

#elif IOS

VkSurfaceKHR VkContext::findSurface(void* native_window) {
    VkMetalSurfaceCreateInfoEXT createInfo {
            .sType = VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT,
            .pLayer = (CAMetalLayer*) native_window,
    };
    VkSurfaceKHR surface;
    auto vkCreateMetalSurfaceEXT = (PFN_vkCreateMetalSurfaceEXT)(vkGetInstanceProcAddr(instance, "vkCreateMetalSurfaceEXT"));
    VK_CHECK(vkCreateMetalSurfaceEXT(instance, &createInfo, VK_CALLBACKS, &surface));
    VK_DEBUG_NAME(device, VK_OBJECT_TYPE_SURFACE_KHR, surface, "VkSurface-iOS");
    return surface;
}

#else

VkSurfaceKHR VkContext::findSurface(void* native_window) {
    // no-op
    return nullptr;
}

#endif
