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
#include "VkDeviceQueue.hpp"
#include "VkSurface.hpp"
#include "VkCommandBufferResource.hpp"

struct VkContext {
    VkInstance instance = nullptr;
    VkContextInfo info;

    VkDebugUtilsMessengerEXT debug_utils = nullptr;
    std::vector<VkExtensionProperties> extensions;
    std::vector<VkLayerProperties> layers;

    VkPhysicalDevice physical_device = nullptr;
    VkPhysicalDeviceProperties properties = {};

    std::vector<VkExtensionProperties> deviceExtensions;
    std::vector<VkLayerProperties> deviceLayers;
    VkDevice device = nullptr;

    std::vector<VkQueueFamilyProperties> queueFamilies;
    VkQueueFamilyIndices queue_family_indices;
    VkDeviceQueue* queue = nullptr;

    VkSurface* surface = nullptr;

    VkContext(void* native_window, const VkContextInfo& info);
    ~VkContext();

    void beginFrame(u32 frame);
    void endFrame(u32 frame);
    void wait();
    void resize(u32 width, u32 height);
    void setSurface(void* surface);
    VkCommandBufferResource* getPrimaryCommandBuffer(u32 frame);
    VkCommandBufferResource* getSecondaryCommandBuffer();

private:
    bool checkExtensions(const char** extension, u32 count);
    bool checkLayers(const char** extension, u32 count);

    bool checkExtension(const char* extension);
    bool checkLayer(const char* extension);

    void findDevice();
    void initDevice(VkPhysicalDevice physicalDevice);
    bool checkDeviceExtensions(const char** extensions, u32 count);
    bool checkDeviceLayers(const char** layers, u32 count);
    bool checkDeviceExtension(const char* extension);
    bool checkDeviceLayer(const char* layer);

    VkSurfaceKHR findSurface(void* native_window);

    VkDeviceQueue* getQueue();

    static constexpr auto TAG = "VkContext";

    std::mutex queueMutex;
    std::mutex commandBufferMutex;
    std::unordered_map<std::thread::id, VkDeviceQueue*> queues;
    std::unordered_map<std::thread::id, VkCommandBufferResource*> secondaryCommandBuffers;
    std::vector<VkSemaphoreResource*> imageSemaphores;
    std::vector<VkSemaphoreResource*> renderFinishedSemaphores;
    std::vector<VkFenceResource*> fences;
    std::vector<VkCommandBufferResource*> primaryCommandBuffers;
};

#endif //VK_CONTEXT_HPP