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
#include "VkCommon.hpp"

#define PTR_OFFSET(type_size) (void*)((char*)mapped + frame * type_size + offset * type_size)
#define PTR_OFFSET_T(T) PTR_OFFSET(sizeof(T))

struct VkBufferResource {
    VkContext* context = nullptr;
    VkBuffer buffer = nullptr;
    VmaAllocation allocation = {};
    VkBufferInfo info;
    void* mapped = nullptr;
    u32 frameStride = 0;

    VkBufferResource(VkContext* context, const VkBufferInfo& info);
    ~VkBufferResource();

    void* map(u32 frame);
    void unmap();

    void resize(size_t size);

    void updateBinding(u32 frame);

private:
    static constexpr auto TAG = "VkBufferResource";
};

#endif //VK_BUFFER_HPP