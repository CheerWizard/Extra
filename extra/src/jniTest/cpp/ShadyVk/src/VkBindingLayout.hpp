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

#include <vector>

struct VkBindingLayout {
    VkDevice device = nullptr;
    VkDescriptorSetLayout layout;
    VkDescriptorSet set = VK_NULL_HANDLE;
    u32 setIndex = 0;
    VkBindingInfo info;
    std::vector<u32> dynamicOffsets;

    VkBindingLayout(VkDevice device, const VkBindingInfo& info);
    ~VkBindingLayout();

    void update(const VkBindingInfo& newInfo);
};

#endif //STC_BINDING_HPP