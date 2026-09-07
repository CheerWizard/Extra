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
#include "vulkan_video_codec_vp9std.h"

#define VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_VERSION_1_0_0 VK_MAKE_VIDEO_STD_VERSION(1, 0, 0)

#define VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_SPEC_VERSION VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_API_VERSION_1_0_0
#define VK_STD_VULKAN_VIDEO_CODEC_VP9_DECODE_EXTENSION_NAME "VK_STD_vulkan_video_codec_vp9_decode"
typedef struct StdVideoDecodeVP9PictureInfoFlags {
    uint32_t    error_resilient_mode : 1;
    uint32_t    intra_only : 1;
    uint32_t    allow_high_precision_mv : 1;
    uint32_t    refresh_frame_context : 1;
    uint32_t    frame_parallel_decoding_mode : 1;
    uint32_t    segmentation_enabled : 1;
    uint32_t    show_frame : 1;
    uint32_t    UsePrevFrameMvs : 1;
    uint32_t    reserved : 24;
} StdVideoDecodeVP9PictureInfoFlags;

typedef struct StdVideoDecodeVP9PictureInfo {
    StdVideoDecodeVP9PictureInfoFlags    flags;
    StdVideoVP9Profile                   profile;
    StdVideoVP9FrameType                 frame_type;
    uint8_t                              frame_context_idx;
    uint8_t                              reset_frame_context;
    uint8_t                              refresh_frame_flags;
    uint8_t                              ref_frame_sign_bias_mask;
    StdVideoVP9InterpolationFilter       interpolation_filter;
    uint8_t                              base_q_idx;
    int8_t                               delta_q_y_dc;
    int8_t                               delta_q_uv_dc;
    int8_t                               delta_q_uv_ac;
    uint8_t                              tile_cols_log2;
    uint8_t                              tile_rows_log2;
    uint16_t                             reserved1[3];
    const StdVideoVP9ColorConfig*        pColorConfig;
    const StdVideoVP9LoopFilter*         pLoopFilter;
    const StdVideoVP9Segmentation*       pSegmentation;
} StdVideoDecodeVP9PictureInfo;


#ifdef __cplusplus
}
#endif

#endif
