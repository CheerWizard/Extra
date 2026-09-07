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
#include <unordered_map>

#include "../api/Vk.h"

struct VkPipe {
    VkDevice device = nullptr;
    VkPipeline pipeline = nullptr;
    VkPipelineLayout pipelineLayout = nullptr;
    VkPipeInfo info;

    VkPipe(VkDevice device, const VkPipeInfo& info);
    ~VkPipe();

    void update(const VkPipeInfo& newInfo);

    static void onShaderUpdated(VkShader* shader);

private:
    static constexpr auto TAG = "VkPipe";
    static std::unordered_map<VkShader*, VkPipe*> shadersWithPipes;
};

struct VkComputePipe {
    VkDevice device = nullptr;
    VkPipeline pipeline = nullptr;
    VkPipelineLayout pipelineLayout = nullptr;
    VkComputePipeInfo info;

    VkComputePipe(VkDevice device, const VkComputePipeInfo& info);
    ~VkComputePipe();

    void update(const VkComputePipeInfo& newInfo);

    static void onShaderUpdated(VkShader* shader);

private:
    static constexpr auto TAG = "VkComputePipe";
    static std::unordered_map<VkShader*, VkComputePipe*> shadersWithPipes;
};

#endif //PIPELINE_HPP