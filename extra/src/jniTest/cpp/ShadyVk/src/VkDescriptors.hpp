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
#include "VkBindingLayout.hpp"

struct VkDescriptors {

    static void New(VkContext* context);
    static void Delete();

    static void newPool(VkBindingLayout* layout);
    static void deletePool(VkBindingLayout* layout);

    static void newSet(VkBindingLayout* layout);
    static void deleteSet(VkBindingLayout* layout);

    static VkDescriptorPool getPool(VkBindingLayout* layout, int frame);
    static VkDescriptorSet getSet(VkBindingLayout* layout, int frame);

private:
    static VkDescriptorPool createPool(VkBindingLayout* layout, int frame);
    static VkDescriptorSet createSet(VkBindingLayout* layout, int frame);

    inline static VkContext* context = nullptr;
    inline static std::mutex mutex;
    inline static std::unordered_map<VkBindingLayout*, std::vector<VkDescriptorPool>> pools;
    inline static std::unordered_map<VkBindingLayout*, std::vector<VkDescriptorSet>> sets;
};

#endif //DESCRIPTORPOOLS_HPP