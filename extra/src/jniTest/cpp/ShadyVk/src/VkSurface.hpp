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
#include "VkSync.hpp"
#include "VkRenderTarget.hpp"

struct VkContext;

struct VkSurface {
    VkContext* context = nullptr;
    VkSurfaceKHR surface = nullptr;
    VkSurfaceCapabilitiesKHR capabilities = {};
    VkSurfaceFormatKHR surface_format;
    std::vector<VkImage> images;
    u32 currentImageIndex = 0;
    u32 width = 0;
    u32 height = 0;
    VkPresentModeKHR present_mode;
    VkSwapchainKHR swapchain = nullptr;
    VkRenderTarget* render_target = nullptr;
    bool needsRecreation = false;

    VkSurface(VkContext* context, VkSurfaceKHR surface, u32 width, u32 height);
    ~VkSurface();

    void resize(int width, int height);
    void updateSurface(VkSurfaceKHR surface);
    bool getImage(const VkSemaphoreResource& semaphore);
    void recreateSwapChain();

private:
    void initSurface(VkSurfaceKHR surface);

    VkSwapchainKHR initSwapChain(u32 width, u32 height) const;
    void releaseSwapChain();

    void initImages(u32 width, u32 height);
    void releaseImages();

    static constexpr auto TAG = "VkSurface";
};

#endif //SURFACE_HPP