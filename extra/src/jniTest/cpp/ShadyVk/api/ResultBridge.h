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
#include <volk.h>

typedef void (*ResultBridgeFn) (VkResult result);

#ifdef __cplusplus
extern "C" {
#endif

    void ResultBridge_init(ResultBridgeFn callback);
    void ResultBridge_send(VkResult result);

#ifdef __cplusplus
}
#endif

#endif //RESULT_BRIDGE_H
