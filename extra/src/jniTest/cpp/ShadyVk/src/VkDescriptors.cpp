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
#include "VkDescriptors.hpp"
#include "VkContext.hpp"

#include <unordered_set>

void VkDescriptors::New(VkContext* context) {
    VkDescriptors::context = context;
}

void VkDescriptors::Delete() {
    for (auto& poolFrames : pools) {
        for (const auto& pool : poolFrames.second) {
            vkDestroyDescriptorPool(context->device, pool, VK_CALLBACKS);
        }
    }
    pools.clear();
    sets.clear();
}

void VkDescriptors::newPool(VkBindingLayout* layout) {
    std::lock_guard lock(mutex);

    auto frameCount = context->info.frameCount;
    auto& poolsVector = pools[layout];

    if (!poolsVector.empty()) {
        return;
    }

    poolsVector.resize(frameCount);
    for (int i = 0 ; i < frameCount ; i++) {
        poolsVector[i] = createPool(layout, i);
    }
}

void VkDescriptors::deletePool(VkBindingLayout* layout) {
    std::lock_guard lock(mutex);

    const auto& poolsVector = pools[layout];
    if (!poolsVector.empty()) {
        for (int i = 0 ; i < poolsVector.size() ; i++) {
            vkDestroyDescriptorPool(context->device, poolsVector[i], VK_CALLBACKS);
        }
        pools.erase(layout);
    }
}

void VkDescriptors::newSet(VkBindingLayout* layout) {
    std::lock_guard lock(mutex);

    auto frameCount = context->info.frameCount;
    auto& setsVector = sets[layout];

    if (setsVector.size() == frameCount) {
        return;
    }

    if (pools[layout].empty()) {
        newPool(layout);
    }

    setsVector.resize(frameCount);
    for (int i = 0 ; i < frameCount ; i++) {
        setsVector[i] = createSet(layout, i);
    }
}

void VkDescriptors::deleteSet(VkBindingLayout* layout) {
    std::lock_guard lock(mutex);

    const auto& poolsVector = pools[layout];
    const auto& setsVector = sets[layout];
    if (!poolsVector.empty() && !setsVector.empty()) {
        for (int i = 0 ; i < setsVector.size() ; i++) {
            VK_CHECK(vkFreeDescriptorSets(context->device, poolsVector[i], 1, &setsVector[i]));
        }
        sets.erase(layout);
    }
}

VkDescriptorPool VkDescriptors::getPool(VkBindingLayout *layout, int frame) {
    return pools[layout][frame];
}

VkDescriptorSet VkDescriptors::getSet(VkBindingLayout *layout, int frame) {
    return sets[layout][frame];
}

VkDescriptorPool VkDescriptors::createPool(VkBindingLayout* layout, int frame) {
    std::unordered_map<VkDescriptorType, uint32_t> descriptorCountsPerType;
    for (int i = 0 ; i < layout->info.bindingsCount ; i++) {
        VkDescriptorType type = (VkDescriptorType) layout->info.bindings[i].type;
        descriptorCountsPerType[type] += 1;
    }

    std::vector<VkDescriptorPoolSize> pool_sizes(descriptorCountsPerType.size());
    for (int i = 0 ; i < descriptorCountsPerType.size() ; i++) {
        const auto& [type, descriptorCount] = *descriptorCountsPerType.begin(i);
        pool_sizes[i] = {
            .type = type,
            .descriptorCount = descriptorCount,
        };
    }

    VkDescriptorPoolCreateInfo poolInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
        .maxSets = 1,
        .poolSizeCount = (uint32_t) pool_sizes.size(),
        .pPoolSizes = pool_sizes.data(),
    };

    VkDescriptorPool pool;
    VK_CHECK(vkCreateDescriptorPool(context->device, &poolInfo, VK_CALLBACKS, &pool));
    VK_DEBUG_NAME_FORMAT(context->device, VK_OBJECT_TYPE_DESCRIPTOR_POOL, layout, "VkDescriptorPool-" << layout->info.name);
    return pool;
}

VkDescriptorSet VkDescriptors::createSet(VkBindingLayout* layout, int frame) {
    VkDescriptorSetAllocateInfo allocInfo = {
        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
        .descriptorPool = pools[layout][frame],
        .descriptorSetCount = 1,
        .pSetLayouts = &layout->layout,
    };

    VkDescriptorSet set;
    VK_CHECK(vkAllocateDescriptorSets(context->device, &allocInfo, &set));
    VK_DEBUG_NAME_FORMAT(context->device, VK_OBJECT_TYPE_DESCRIPTOR_SET, layout, "VkDescriptorSet-" << layout->info.name);
    return set;
}
