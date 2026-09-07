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
package com.cws.extra.test

import com.cws.extra.memory.ExtraBridgeEnum

@ExtraBridgeEnum
expect enum class AttributeFormat {
    FLOAT, FLOAT2, FLOAT3, FLOAT4;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class AttributeType {
    ATTRIBUTE_TYPE_PRIMITIVE,
    ATTRIBUTE_TYPE_VEC2,
    ATTRIBUTE_TYPE_VEC3,
    ATTRIBUTE_TYPE_VEC4,
    ATTRIBUTE_TYPE_MAT2,
    ATTRIBUTE_TYPE_MAT3,
    ATTRIBUTE_TYPE_MAT4;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class IndexSize {
    UNSIGNED_16,
    UNSIGNED_32;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class BindingType {
    UNIFORM_BUFFER,
    UNIFORM_BUFFER_DYNAMIC,
    STORAGE_BUFFER,
    STORAGE_BUFFER_DYNAMIC,
    TEXTURE,
    SAMPLER;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class BlendOp {
    ADD,
    SUBTRACT,
    REVERSE_SUBTRACT,
    MIN,
    MAX;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class BlendFactor {
    ZERO,
    ONE,
    SRC_COLOR,
    ONE_MINUS_SRC_COLOR,
    DST_COLOR,
    ONE_MINUS_DST_COLOR,
    SRC_ALPHA,
    ONE_MINUS_SRC_ALPHA,
    DST_ALPHA,
    ONE_MINUS_DST_ALPHA;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class BufferUsage {
    MAP_READ,
    MAP_WRITE,
    COPY_SRC,
    COPY_DST,
    UNIFORM_TEXEL,
    STORAGE_TEXEL,
    UNIFORM_BUFFER,
    STORAGE_BUFFER,
    INDEX_BUFFER,
    VERTEX_BUFFER,
    INDIRECT_BUFFER;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class TextureUsage {
    COPY_SRC,
    COPY_DST,
    TEXTURE_BINDING,
    STORAGE_BINDING,
    RENDER_ATTACHMENT;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class MemoryType {
    HOST,
    DEVICE_LOCAL;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class PrimitiveTopology {
    POINT_LIST,
    LINE_LIST,
    LINE_STRIP,
    TRIANGLE_LIST,
    TRIANGLE_STRIP,
    TRIANGLE_FAN,
    LINE_LIST_WITH_ADJACENCY,
    LINE_STRIP_WITH_ADJACENCY,
    TRIANGLE_LIST_WITH_ADJACENCY,
    TRIANGLE_STRIP_WITH_ADJACENCY,
    PATCH_LIST,
    MAX_ENUM;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class PolygonMode {
    FILL,
    LINE,
    POINT;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class CullMode {
    NONE,
    FRONT,
    BACK,
    FRONT_AND_BACK;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class FrontFace {
    COUNTER_CLOCKWISE,
    CLOCKWISE;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class ShaderStage {
    VERTEX,
    FRAGMENT,
    COMPUTE,
    MESH,
    RAY_TRACING;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class TextureType {
    TEXTURE2D,
    TEXTURE3D,
    TEXTURE_CUBE,
    TEXTURE_ARRAY;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class TextureFormat {
    FORMAT_R8,
    FORMAT_RG8,
    FORMAT_RGB8,
    FORMAT_RGBA8,
    FORMAT_BGRA,
    FORMAT_R16,
    FORMAT_RG16,
    FORMAT_RGB16,
    FORMAT_RGBA16,
    FORMAT_R32,
    FORMAT_RG32,
    FORMAT_RGB32,
    FORMAT_RGBA32,
    FORMAT_DEPTH16,
    FORMAT_DEPTH24,
    FORMAT_DEPTH32;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class SamplerFilter {
    LINEAR,
    NEAREST;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class SamplerMode {
    REPEAT,
    MIRRORED_REPEAT,
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class SamplerMipMapMode {
    NONE,
    LINEAR,
    NEAREST;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class CompareOp {
    ALWAYS,
    NEVER,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,
    EQUAL,
    NOT_EQUAL;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class StencilOp {
    KEEP,
    ZERO,
    REPLACE,
    INCREMENT_AND_CLAMP,
    DECREMENT_AND_CLAMP,
    INVERT,
    INCREMENT_AND_WRAP,
    DECREMENT_AND_WRAP;

    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class BorderColor {
    FLOAT_TRANSPARENT_BLACK,
    INT_TRANSPARENT_BLACK,
    FLOAT_OPAQUE_BLACK,
    INT_OPAQUE_BLACK,
    FLOAT_OPAQUE_WHITE,
    INT_OPAQUE_WHITE;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class PipelineStage {
    TOP_OF_PIPE,
    DRAW_INDIRECT,
    VERTEX_INPUT,
    VERTEX_SHADER,
    GEOMETRY_SHADER,
    FRAGMENT_SHADER,
    EARLY_FRAGMENT_TEST,
    LATE_FRAGMENT_TEST,
    COLOR_ATTACHMENT_OUTPUT,
    COMPUTE_SHADER,
    TRANSFER,
    BOTTOM_OF_PIPE,
    HOST,
    ALL_GRAPHICS,
    ALL_COMMANDS,
    NONE;
    val rawValue: Int
}

@ExtraBridgeEnum
expect enum class AccessFlag {
    INDIRECT_COMMAND_READ,
    INDEX_READ,
    VERTEX_ATTRIBUTE_READ,
    UNIFORM_READ,
    INPUT_ATTACHMENT_READ,
    SHADER_READ,
    SHADER_WRITE,
    COLOR_ATTACHMENT_READ,
    COLOR_ATTACHMENT_WRITE,
    DEPTH_STENCIL_ATTACHMENT_READ,
    DEPTH_STENCIL_ATTACHMENT_WRITE,
    TRANSFER_READ,
    TRANSFER_WRITE,
    HOST_READ,
    HOST_WRITE,
    MEMORY_READ,
    MEMORY_WRITE,
    NONE;
    val rawValue: Int
}