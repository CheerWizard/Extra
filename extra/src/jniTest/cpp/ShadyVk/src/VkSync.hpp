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
#include "VkCommon.hpp"

struct VkContext;

struct VkFenceResource {
    VkDevice device = nullptr;
    VkFence fence = nullptr;

    VkFenceResource(VkDevice device, const char* name, bool signaled);
    ~VkFenceResource();

    void wait(u64 timeout = UINT64_MAX);
    void reset();
};

struct VkSemaphoreResource {
    VkDevice device = nullptr;
    VkSemaphore semaphore = nullptr;

    VkSemaphoreResource(VkDevice device, const char* name);
    ~VkSemaphoreResource();
};

#endif // SYNC_HPP