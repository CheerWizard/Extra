// Generated from Kotlin Extra library

#pragma once

#include "ExtraTypes.h"

// -------------- Forward declarations -----------------

enum class VkAttributeFormat : int32_t;
enum class VkAttributeType : int32_t;
enum class VkIndexSize : int32_t;
enum class VkBindingType : int32_t;
enum class VkBlendOp : int32_t;
enum class VkBlendFactor : int32_t;
enum class VkBufferUsage : int32_t;
enum class VkTextureUsage : int32_t;
enum class VkMemoryType : int32_t;
enum class VkPrimitiveTopology : int32_t;
enum class VkPolygonMode : int32_t;
enum class VkCullMode : int32_t;
enum class VkFrontFace : int32_t;
enum class VkShaderStage : int32_t;
enum class VkTextureType : int32_t;
enum class VkTextureFormat : int32_t;
enum class VkSamplerFilter : int32_t;
enum class VkSamplerMode : int32_t;
enum class VkSamplerMipMapMode : int32_t;
enum class VkCompareOp : int32_t;
enum class VkStencilOp : int32_t;
enum class VkBorderColor : int32_t;
enum class VkPipelineStage : int32_t;
enum class VkAccessFlag : int32_t;
enum class VkEndian : int32_t;
enum class VkMemoryBoundary : int32_t;
enum class VkMemoryLayout : int32_t;
enum class VkSpirvTarget : int32_t;
enum class VkTestEnumOrdinal : int32_t;
enum class VkTestEnumRaw : float;
enum class VkHeroClass : int32_t;

struct VkRenderContextInfo;
struct VkSwapchainInfo;
struct VkBufferInfo;
struct VkVertexBufferInfo;
struct VkIndexBufferInfo;
struct VkSamplerInfo;
struct VkTextureInfo;
struct VkBlendState;
struct VkAttribute;
struct VkBinding;
struct VkBindingInfo;
struct VkShaderInfo;
struct VkStencilState;
struct VkRenderPipelineInfo;
struct VkComputePipelineInfo;
struct VkColorAttachment;
struct VkDepthAttachment;
struct VkStencilAttachment;
struct VkRenderTargetInfo;
struct VkBindingLayoutHandle;
struct VkBufferHandle;
struct VkRenderContextHandle;
struct VkSurfaceHandle;
struct VkRenderPipelineHandle;
struct VkComputePipelineHandle;
struct VkRenderTargetHandle;
struct VkSamplerHandle;
struct VkTextureHandle;
struct VkShaderHandle;
struct VkCommandBufferHandle;
struct VkUIntList;
struct VkByteList;
struct VkUByteList;
struct VkCharList;
struct VkShortList;
struct VkDoubleList;
struct VkFloatList;
struct VkIntList;
struct VkBooleanList;
struct VkUShortList;
struct VkULongList;
struct VkLongList;
struct VkEntityPool;
struct VkScene;
struct VkComponentPool;
struct VkInt2;
struct VkUInt4;
struct VkFloat4;
struct VkInt3;
struct VkInt4;
struct VkUInt2;
struct VkFloat3;
struct VkFloat2;
struct VkQuaternion;
struct VkUInt3;
struct VkMat4;
struct VkMat2;
struct VkMat3;
struct VkTestData;
struct VkNestedData;
struct VkMovement;
struct VkCamera;
struct VkVelocity;
struct VkRenderable;
struct VkHealth;
struct VkDamage;
struct VkCollision;

// -------------- ExtraEnum -----------------

enum class VkAttributeFormat : int32_t
{
    FLOAT = 0,
    FLOAT2 = 1,
    FLOAT3 = 2,
    FLOAT4 = 3,
};

enum class VkAttributeType : int32_t
{
    ATTRIBUTE_TYPE_PRIMITIVE = 0,
    ATTRIBUTE_TYPE_VEC2 = 1,
    ATTRIBUTE_TYPE_VEC3 = 2,
    ATTRIBUTE_TYPE_VEC4 = 3,
    ATTRIBUTE_TYPE_MAT2 = 4,
    ATTRIBUTE_TYPE_MAT3 = 5,
    ATTRIBUTE_TYPE_MAT4 = 6,
};

enum class VkIndexSize : int32_t
{
    UNSIGNED_16 = 0,
    UNSIGNED_32 = 1,
};

enum class VkBindingType : int32_t
{
    UNIFORM_BUFFER = 0,
    UNIFORM_BUFFER_DYNAMIC = 1,
    STORAGE_BUFFER = 2,
    STORAGE_BUFFER_DYNAMIC = 3,
    TEXTURE = 4,
    SAMPLER = 5,
};

enum class VkBlendOp : int32_t
{
    ADD = 0,
    SUBTRACT = 1,
    REVERSE_SUBTRACT = 2,
    MIN = 3,
    MAX = 4,
};

enum class VkBlendFactor : int32_t
{
    ZERO = 0,
    ONE = 1,
    SRC_COLOR = 2,
    ONE_MINUS_SRC_COLOR = 3,
    DST_COLOR = 4,
    ONE_MINUS_DST_COLOR = 5,
    SRC_ALPHA = 6,
    ONE_MINUS_SRC_ALPHA = 7,
    DST_ALPHA = 8,
    ONE_MINUS_DST_ALPHA = 9,
};

enum class VkBufferUsage : int32_t
{
    MAP_READ = 0,
    MAP_WRITE = 1,
    COPY_SRC = 2,
    COPY_DST = 3,
    UNIFORM_TEXEL = 4,
    STORAGE_TEXEL = 5,
    UNIFORM_BUFFER = 6,
    STORAGE_BUFFER = 7,
    INDEX_BUFFER = 8,
    VERTEX_BUFFER = 9,
    INDIRECT_BUFFER = 10,
};

enum class VkTextureUsage : int32_t
{
    COPY_SRC = 0,
    COPY_DST = 1,
    TEXTURE_BINDING = 2,
    STORAGE_BINDING = 3,
    RENDER_ATTACHMENT = 4,
};

enum class VkMemoryType : int32_t
{
    HOST = 0,
    DEVICE_LOCAL = 1,
};

enum class VkPrimitiveTopology : int32_t
{
    POINT_LIST = 0,
    LINE_LIST = 1,
    LINE_STRIP = 2,
    TRIANGLE_LIST = 3,
    TRIANGLE_STRIP = 4,
    TRIANGLE_FAN = 5,
    LINE_LIST_WITH_ADJACENCY = 6,
    LINE_STRIP_WITH_ADJACENCY = 7,
    TRIANGLE_LIST_WITH_ADJACENCY = 8,
    TRIANGLE_STRIP_WITH_ADJACENCY = 9,
    PATCH_LIST = 10,
    MAX_ENUM = 11,
};

enum class VkPolygonMode : int32_t
{
    FILL = 0,
    LINE = 1,
    POINT = 2,
};

enum class VkCullMode : int32_t
{
    NONE = 0,
    FRONT = 1,
    BACK = 2,
    FRONT_AND_BACK = 3,
};

enum class VkFrontFace : int32_t
{
    COUNTER_CLOCKWISE = 0,
    CLOCKWISE = 1,
};

enum class VkShaderStage : int32_t
{
    VERTEX = 0,
    FRAGMENT = 1,
    COMPUTE = 2,
    MESH = 3,
    RAY_TRACING = 4,
};

enum class VkTextureType : int32_t
{
    TEXTURE2D = 0,
    TEXTURE3D = 1,
    TEXTURE_CUBE = 2,
    TEXTURE_ARRAY = 3,
};

enum class VkTextureFormat : int32_t
{
    FORMAT_R8 = 0,
    FORMAT_RG8 = 1,
    FORMAT_RGB8 = 2,
    FORMAT_RGBA8 = 3,
    FORMAT_BGRA = 4,
    FORMAT_R16 = 5,
    FORMAT_RG16 = 6,
    FORMAT_RGB16 = 7,
    FORMAT_RGBA16 = 8,
    FORMAT_R32 = 9,
    FORMAT_RG32 = 10,
    FORMAT_RGB32 = 11,
    FORMAT_RGBA32 = 12,
    FORMAT_DEPTH16 = 13,
    FORMAT_DEPTH24 = 14,
    FORMAT_DEPTH32 = 15,
};

enum class VkSamplerFilter : int32_t
{
    LINEAR = 0,
    NEAREST = 1,
};

enum class VkSamplerMode : int32_t
{
    REPEAT = 0,
    MIRRORED_REPEAT = 1,
    CLAMP_TO_EDGE = 2,
    CLAMP_TO_BORDER = 3,
};

enum class VkSamplerMipMapMode : int32_t
{
    NONE = 0,
    LINEAR = 1,
    NEAREST = 2,
};

enum class VkCompareOp : int32_t
{
    ALWAYS = 0,
    NEVER = 1,
    LESS = 2,
    LESS_EQUAL = 3,
    GREATER = 4,
    GREATER_EQUAL = 5,
    EQUAL = 6,
    NOT_EQUAL = 7,
};

enum class VkStencilOp : int32_t
{
    KEEP = 0,
    ZERO = 1,
    REPLACE = 2,
    INCREMENT_AND_CLAMP = 3,
    DECREMENT_AND_CLAMP = 4,
    INVERT = 5,
    INCREMENT_AND_WRAP = 6,
    DECREMENT_AND_WRAP = 7,
};

enum class VkBorderColor : int32_t
{
    FLOAT_TRANSPARENT_BLACK = 0,
    INT_TRANSPARENT_BLACK = 1,
    FLOAT_OPAQUE_BLACK = 2,
    INT_OPAQUE_BLACK = 3,
    FLOAT_OPAQUE_WHITE = 4,
    INT_OPAQUE_WHITE = 5,
};

enum class VkPipelineStage : int32_t
{
    TOP_OF_PIPE = 0,
    DRAW_INDIRECT = 1,
    VERTEX_INPUT = 2,
    VERTEX_SHADER = 3,
    GEOMETRY_SHADER = 4,
    FRAGMENT_SHADER = 5,
    EARLY_FRAGMENT_TEST = 6,
    LATE_FRAGMENT_TEST = 7,
    COLOR_ATTACHMENT_OUTPUT = 8,
    COMPUTE_SHADER = 9,
    TRANSFER = 10,
    BOTTOM_OF_PIPE = 11,
    HOST = 12,
    ALL_GRAPHICS = 13,
    ALL_COMMANDS = 14,
    NONE = 15,
};

enum class VkAccessFlag : int32_t
{
    INDIRECT_COMMAND_READ = 0,
    INDEX_READ = 1,
    VERTEX_ATTRIBUTE_READ = 2,
    UNIFORM_READ = 3,
    INPUT_ATTACHMENT_READ = 4,
    SHADER_READ = 5,
    SHADER_WRITE = 6,
    COLOR_ATTACHMENT_READ = 7,
    COLOR_ATTACHMENT_WRITE = 8,
    DEPTH_STENCIL_ATTACHMENT_READ = 9,
    DEPTH_STENCIL_ATTACHMENT_WRITE = 10,
    TRANSFER_READ = 11,
    TRANSFER_WRITE = 12,
    HOST_READ = 13,
    HOST_WRITE = 14,
    MEMORY_READ = 15,
    MEMORY_WRITE = 16,
    NONE = 17,
};

enum class VkEndian : int32_t
{
    LITTLE = 0,
    BIG = 1,
};

enum class VkMemoryBoundary : int32_t
{
    KOTLIN_HEAP = 0,
    EXTERNAL = 1,
};

enum class VkMemoryLayout : int32_t
{
    KOTLIN = 0,
    STD140 = 1,
    STD430 = 2,
};

enum class VkSpirvTarget : int32_t
{
    OPENGL = 0,
    VULKAN = 1,
};

enum class VkTestEnumOrdinal : int32_t
{
    Ordinal_0 = 0,
    Ordinal_1 = 1,
    Ordinal_2 = 2,
    Ordinal_3 = 3,
    Ordinal_4 = 4,
    Ordinal_5 = 5,
};

enum class VkTestEnumRaw : float
{
    Raw_0 = 0,
    Raw_1 = 1,
    Raw_2 = 2,
    Raw_3 = 3,
    Raw_4 = 4,
    Raw_5 = 5,
};

enum class VkHeroClass : int32_t
{
    Warrior = 0,
    Mage = 1,
    Archer = 2,
};

// -------------- ExtraData -----------------

EXTRA_STRUCT VkSurfaceHandle
{
    int64_t address;

    static inline int32_t SizeOf(const VkSurfaceHandle& s)
    {
        return static_cast<int32_t>(sizeof(VkSurfaceHandle));
    }

    static inline VkSurfaceHandle Decode(const uint8_t* bytes)
    {
        VkSurfaceHandle s;
        std::memcpy(&s, bytes, sizeof(VkSurfaceHandle));
        return s;
    }

    static inline void Encode(const VkSurfaceHandle& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkSurfaceHandle));
    }
};

EXTRA_STRUCT VkFloat4
{
    float x;
    float y;
    float z;
    float w;

    static inline int32_t SizeOf(const VkFloat4& s)
    {
        return static_cast<int32_t>(sizeof(VkFloat4));
    }

    static inline VkFloat4 Decode(const uint8_t* bytes)
    {
        VkFloat4 s;
        std::memcpy(&s, bytes, sizeof(VkFloat4));
        return s;
    }

    static inline void Encode(const VkFloat4& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkFloat4));
    }
};

struct VkRenderContextInfo
{
    ExtraString applicationName;
    ExtraString engineName;
    ExtraString swapchainName;
    int32_t x;
    int32_t y;
    int32_t width;
    int32_t height;
    int32_t frameCount;
    bool isDebug;
    VkSurfaceHandle surface;
    VkFloat4 clearColor;
    bool enableDepth;
    bool enableStencil;
    int32_t frameBudgetBytes;

    static inline int32_t SizeOf(const VkRenderContextInfo& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t) + s.applicationName.length * sizeof(char);
        size += sizeof(int32_t) + s.engineName.length * sizeof(char);
        size += sizeof(int32_t) + s.swapchainName.length * sizeof(char);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(bool);
        size += sizeof(VkSurfaceHandle);
        size += sizeof(VkFloat4);
        size += sizeof(bool);
        size += sizeof(bool);
        size += sizeof(int32_t);
        return size;
    }

    static inline VkRenderContextInfo Decode(const uint8_t* bytes)
    {
        VkRenderContextInfo s;
        const uint8_t* p = bytes;
        s.applicationName = ExtraNextString(p);
        s.engineName = ExtraNextString(p);
        s.swapchainName = ExtraNextString(p);
        s.x = ExtraNextPrimitive<int32_t>(p);
        s.y = ExtraNextPrimitive<int32_t>(p);
        s.width = ExtraNextPrimitive<int32_t>(p);
        s.height = ExtraNextPrimitive<int32_t>(p);
        s.frameCount = ExtraNextPrimitive<int32_t>(p);
        s.isDebug = ExtraNextPrimitive<bool>(p);
        std::memcpy(&s.surface, p, sizeof(VkSurfaceHandle)); p += sizeof(VkSurfaceHandle);
        std::memcpy(&s.clearColor, p, sizeof(VkFloat4)); p += sizeof(VkFloat4);
        s.enableDepth = ExtraNextPrimitive<bool>(p);
        s.enableStencil = ExtraNextPrimitive<bool>(p);
        s.frameBudgetBytes = ExtraNextPrimitive<int32_t>(p);
        return s;
    }

    static inline void Encode(const VkRenderContextInfo& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushString(s.applicationName, p);
        ExtraPushString(s.engineName, p);
        ExtraPushString(s.swapchainName, p);
        ExtraPushPrimitive<int32_t>(s.x, p);
        ExtraPushPrimitive<int32_t>(s.y, p);
        ExtraPushPrimitive<int32_t>(s.width, p);
        ExtraPushPrimitive<int32_t>(s.height, p);
        ExtraPushPrimitive<int32_t>(s.frameCount, p);
        ExtraPushPrimitive<bool>(s.isDebug, p);
        std::memcpy(p, &s.surface, sizeof(VkSurfaceHandle)); p += sizeof(VkSurfaceHandle);
        std::memcpy(p, &s.clearColor, sizeof(VkFloat4)); p += sizeof(VkFloat4);
        ExtraPushPrimitive<bool>(s.enableDepth, p);
        ExtraPushPrimitive<bool>(s.enableStencil, p);
        ExtraPushPrimitive<int32_t>(s.frameBudgetBytes, p);
    }
};

EXTRA_STRUCT VkTextureHandle
{
    int64_t address;

    static inline int32_t SizeOf(const VkTextureHandle& s)
    {
        return static_cast<int32_t>(sizeof(VkTextureHandle));
    }

    static inline VkTextureHandle Decode(const uint8_t* bytes)
    {
        VkTextureHandle s;
        std::memcpy(&s, bytes, sizeof(VkTextureHandle));
        return s;
    }

    static inline void Encode(const VkTextureHandle& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkTextureHandle));
    }
};

EXTRA_STRUCT VkBlendState
{
    bool enable;
    VkBlendFactor srcFactorColor;
    VkBlendFactor dstFactorColor;
    VkBlendOp blendOpColor;
    VkBlendFactor srcFactorAlpha;
    VkBlendFactor dstFactorAlpha;
    VkBlendOp blendOpAlpha;

    static inline int32_t SizeOf(const VkBlendState& s)
    {
        return static_cast<int32_t>(sizeof(VkBlendState));
    }

    static inline VkBlendState Decode(const uint8_t* bytes)
    {
        VkBlendState s;
        std::memcpy(&s, bytes, sizeof(VkBlendState));
        return s;
    }

    static inline void Encode(const VkBlendState& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkBlendState));
    }
};

EXTRA_STRUCT VkColorAttachment
{
    VkTextureHandle texture;
    VkFloat4 clearColor;
    VkBlendState blendState;

    static inline int32_t SizeOf(const VkColorAttachment& s)
    {
        return static_cast<int32_t>(sizeof(VkColorAttachment));
    }

    static inline VkColorAttachment Decode(const uint8_t* bytes)
    {
        VkColorAttachment s;
        std::memcpy(&s, bytes, sizeof(VkColorAttachment));
        return s;
    }

    static inline void Encode(const VkColorAttachment& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkColorAttachment));
    }
};

struct VkTextureInfo
{
    ExtraString name;
    VkTextureType type;
    VkMemoryType memoryType;
    int32_t usages;
    int32_t width;
    int32_t height;
    int32_t depth;
    VkTextureFormat format;
    int32_t mips;
    int32_t baseMip;
    int32_t samples;
    bool isStatic;

    static inline int32_t SizeOf(const VkTextureInfo& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t) + s.name.length * sizeof(char);
        size += sizeof(VkTextureType);
        size += sizeof(VkMemoryType);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(VkTextureFormat);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(bool);
        return size;
    }

    static inline VkTextureInfo Decode(const uint8_t* bytes)
    {
        VkTextureInfo s;
        const uint8_t* p = bytes;
        s.name = ExtraNextString(p);
        std::memcpy(&s.type, p, sizeof(VkTextureType)); p += sizeof(VkTextureType);
        std::memcpy(&s.memoryType, p, sizeof(VkMemoryType)); p += sizeof(VkMemoryType);
        s.usages = ExtraNextPrimitive<int32_t>(p);
        s.width = ExtraNextPrimitive<int32_t>(p);
        s.height = ExtraNextPrimitive<int32_t>(p);
        s.depth = ExtraNextPrimitive<int32_t>(p);
        std::memcpy(&s.format, p, sizeof(VkTextureFormat)); p += sizeof(VkTextureFormat);
        s.mips = ExtraNextPrimitive<int32_t>(p);
        s.baseMip = ExtraNextPrimitive<int32_t>(p);
        s.samples = ExtraNextPrimitive<int32_t>(p);
        s.isStatic = ExtraNextPrimitive<bool>(p);
        return s;
    }

    static inline void Encode(const VkTextureInfo& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushString(s.name, p);
        std::memcpy(p, &s.type, sizeof(VkTextureType)); p += sizeof(VkTextureType);
        std::memcpy(p, &s.memoryType, sizeof(VkMemoryType)); p += sizeof(VkMemoryType);
        ExtraPushPrimitive<int32_t>(s.usages, p);
        ExtraPushPrimitive<int32_t>(s.width, p);
        ExtraPushPrimitive<int32_t>(s.height, p);
        ExtraPushPrimitive<int32_t>(s.depth, p);
        std::memcpy(p, &s.format, sizeof(VkTextureFormat)); p += sizeof(VkTextureFormat);
        ExtraPushPrimitive<int32_t>(s.mips, p);
        ExtraPushPrimitive<int32_t>(s.baseMip, p);
        ExtraPushPrimitive<int32_t>(s.samples, p);
        ExtraPushPrimitive<bool>(s.isStatic, p);
    }
};

struct VkSwapchainInfo
{
    ExtraString name;
    VkColorAttachment colorAttachment;
    VkTextureInfo depthTextureInfo;

    static inline int32_t SizeOf(const VkSwapchainInfo& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t) + s.name.length * sizeof(char);
        size += sizeof(VkColorAttachment);
        size += VkTextureInfo::SizeOf(s.depthTextureInfo);
        return size;
    }

    static inline VkSwapchainInfo Decode(const uint8_t* bytes)
    {
        VkSwapchainInfo s;
        const uint8_t* p = bytes;
        s.name = ExtraNextString(p);
        std::memcpy(&s.colorAttachment, p, sizeof(VkColorAttachment)); p += sizeof(VkColorAttachment);
        s.depthTextureInfo = VkTextureInfo::Decode(p); p += VkTextureInfo::SizeOf(s.depthTextureInfo);
        return s;
    }

    static inline void Encode(const VkSwapchainInfo& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushString(s.name, p);
        std::memcpy(p, &s.colorAttachment, sizeof(VkColorAttachment)); p += sizeof(VkColorAttachment);
        VkTextureInfo::Encode(s.depthTextureInfo, p); p += VkTextureInfo::SizeOf(s.depthTextureInfo);
    }
};

struct VkBufferInfo
{
    ExtraString name;
    int32_t slot;
    VkMemoryType memoryType;
    int32_t usages;
    int64_t size;
    bool isStatic;

    static inline int32_t SizeOf(const VkBufferInfo& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t) + s.name.length * sizeof(char);
        size += sizeof(int32_t);
        size += sizeof(VkMemoryType);
        size += sizeof(int32_t);
        size += sizeof(int64_t);
        size += sizeof(bool);
        return size;
    }

    static inline VkBufferInfo Decode(const uint8_t* bytes)
    {
        VkBufferInfo s;
        const uint8_t* p = bytes;
        s.name = ExtraNextString(p);
        s.slot = ExtraNextPrimitive<int32_t>(p);
        std::memcpy(&s.memoryType, p, sizeof(VkMemoryType)); p += sizeof(VkMemoryType);
        s.usages = ExtraNextPrimitive<int32_t>(p);
        s.size = ExtraNextPrimitive<int64_t>(p);
        s.isStatic = ExtraNextPrimitive<bool>(p);
        return s;
    }

    static inline void Encode(const VkBufferInfo& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushString(s.name, p);
        ExtraPushPrimitive<int32_t>(s.slot, p);
        std::memcpy(p, &s.memoryType, sizeof(VkMemoryType)); p += sizeof(VkMemoryType);
        ExtraPushPrimitive<int32_t>(s.usages, p);
        ExtraPushPrimitive<int64_t>(s.size, p);
        ExtraPushPrimitive<bool>(s.isStatic, p);
    }
};

EXTRA_STRUCT VkAttribute
{
    int32_t location;
    VkAttributeType type;
    VkAttributeFormat format;

    static inline int32_t SizeOf(const VkAttribute& s)
    {
        return static_cast<int32_t>(sizeof(VkAttribute));
    }

    static inline VkAttribute Decode(const uint8_t* bytes)
    {
        VkAttribute s;
        std::memcpy(&s, bytes, sizeof(VkAttribute));
        return s;
    }

    static inline void Encode(const VkAttribute& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkAttribute));
    }
};

struct VkVertexBufferInfo
{
    ExtraString name;
    ExtraList<VkAttribute> attributes;
    int32_t vertexCount;
    int32_t slot;

    static inline int32_t SizeOf(const VkVertexBufferInfo& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t) + s.name.length * sizeof(char);
        size += sizeof(int32_t);
        { const uint8_t* r = s.attributes.data; for (int32_t i = 0; i < s.attributes.count; i++) { auto before = r; r += sizeof(VkAttribute); size += static_cast<int32_t>(r - before); } }
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        return size;
    }

    static inline VkVertexBufferInfo Decode(const uint8_t* bytes)
    {
        VkVertexBufferInfo s;
        const uint8_t* p = bytes;
        s.name = ExtraNextString(p);
        s.attributes = ExtraNextList<VkAttribute>(p, [](const uint8_t*& p) { p += sizeof(VkAttribute); });
        s.vertexCount = ExtraNextPrimitive<int32_t>(p);
        s.slot = ExtraNextPrimitive<int32_t>(p);
        return s;
    }

    static inline void Encode(const VkVertexBufferInfo& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushString(s.name, p);
        ExtraPushList<VkAttribute>(s.attributes, p, [](const uint8_t*& r, uint8_t*& p) { { std::memcpy(p, r, sizeof(VkAttribute)); p += sizeof(VkAttribute); r += sizeof(VkAttribute); }; });
        ExtraPushPrimitive<int32_t>(s.vertexCount, p);
        ExtraPushPrimitive<int32_t>(s.slot, p);
    }
};

struct VkIndexBufferInfo
{
    ExtraString name;
    int32_t indexCount;
    VkIndexSize indexSize;

    static inline int32_t SizeOf(const VkIndexBufferInfo& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t) + s.name.length * sizeof(char);
        size += sizeof(int32_t);
        size += sizeof(VkIndexSize);
        return size;
    }

    static inline VkIndexBufferInfo Decode(const uint8_t* bytes)
    {
        VkIndexBufferInfo s;
        const uint8_t* p = bytes;
        s.name = ExtraNextString(p);
        s.indexCount = ExtraNextPrimitive<int32_t>(p);
        std::memcpy(&s.indexSize, p, sizeof(VkIndexSize)); p += sizeof(VkIndexSize);
        return s;
    }

    static inline void Encode(const VkIndexBufferInfo& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushString(s.name, p);
        ExtraPushPrimitive<int32_t>(s.indexCount, p);
        std::memcpy(p, &s.indexSize, sizeof(VkIndexSize)); p += sizeof(VkIndexSize);
    }
};

struct VkSamplerInfo
{
    ExtraString name;
    VkSamplerFilter magFilter;
    VkSamplerFilter minFilter;
    VkSamplerMode addressModeU;
    VkSamplerMode addressModeV;
    VkSamplerMode addressModeW;
    VkSamplerMipMapMode mipmapMode;
    bool enableAnisotropy;
    float maxAnisotropy;
    bool unnormalizedCoordinates;
    bool enableCompare;
    VkCompareOp compareOp;
    VkBorderColor borderColor;
    float mipLodBias;
    float minLod;
    float maxLod;

    static inline int32_t SizeOf(const VkSamplerInfo& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t) + s.name.length * sizeof(char);
        size += sizeof(VkSamplerFilter);
        size += sizeof(VkSamplerFilter);
        size += sizeof(VkSamplerMode);
        size += sizeof(VkSamplerMode);
        size += sizeof(VkSamplerMode);
        size += sizeof(VkSamplerMipMapMode);
        size += sizeof(bool);
        size += sizeof(float);
        size += sizeof(bool);
        size += sizeof(bool);
        size += sizeof(VkCompareOp);
        size += sizeof(VkBorderColor);
        size += sizeof(float);
        size += sizeof(float);
        size += sizeof(float);
        return size;
    }

    static inline VkSamplerInfo Decode(const uint8_t* bytes)
    {
        VkSamplerInfo s;
        const uint8_t* p = bytes;
        s.name = ExtraNextString(p);
        std::memcpy(&s.magFilter, p, sizeof(VkSamplerFilter)); p += sizeof(VkSamplerFilter);
        std::memcpy(&s.minFilter, p, sizeof(VkSamplerFilter)); p += sizeof(VkSamplerFilter);
        std::memcpy(&s.addressModeU, p, sizeof(VkSamplerMode)); p += sizeof(VkSamplerMode);
        std::memcpy(&s.addressModeV, p, sizeof(VkSamplerMode)); p += sizeof(VkSamplerMode);
        std::memcpy(&s.addressModeW, p, sizeof(VkSamplerMode)); p += sizeof(VkSamplerMode);
        std::memcpy(&s.mipmapMode, p, sizeof(VkSamplerMipMapMode)); p += sizeof(VkSamplerMipMapMode);
        s.enableAnisotropy = ExtraNextPrimitive<bool>(p);
        s.maxAnisotropy = ExtraNextPrimitive<float>(p);
        s.unnormalizedCoordinates = ExtraNextPrimitive<bool>(p);
        s.enableCompare = ExtraNextPrimitive<bool>(p);
        std::memcpy(&s.compareOp, p, sizeof(VkCompareOp)); p += sizeof(VkCompareOp);
        std::memcpy(&s.borderColor, p, sizeof(VkBorderColor)); p += sizeof(VkBorderColor);
        s.mipLodBias = ExtraNextPrimitive<float>(p);
        s.minLod = ExtraNextPrimitive<float>(p);
        s.maxLod = ExtraNextPrimitive<float>(p);
        return s;
    }

    static inline void Encode(const VkSamplerInfo& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushString(s.name, p);
        std::memcpy(p, &s.magFilter, sizeof(VkSamplerFilter)); p += sizeof(VkSamplerFilter);
        std::memcpy(p, &s.minFilter, sizeof(VkSamplerFilter)); p += sizeof(VkSamplerFilter);
        std::memcpy(p, &s.addressModeU, sizeof(VkSamplerMode)); p += sizeof(VkSamplerMode);
        std::memcpy(p, &s.addressModeV, sizeof(VkSamplerMode)); p += sizeof(VkSamplerMode);
        std::memcpy(p, &s.addressModeW, sizeof(VkSamplerMode)); p += sizeof(VkSamplerMode);
        std::memcpy(p, &s.mipmapMode, sizeof(VkSamplerMipMapMode)); p += sizeof(VkSamplerMipMapMode);
        ExtraPushPrimitive<bool>(s.enableAnisotropy, p);
        ExtraPushPrimitive<float>(s.maxAnisotropy, p);
        ExtraPushPrimitive<bool>(s.unnormalizedCoordinates, p);
        ExtraPushPrimitive<bool>(s.enableCompare, p);
        std::memcpy(p, &s.compareOp, sizeof(VkCompareOp)); p += sizeof(VkCompareOp);
        std::memcpy(p, &s.borderColor, sizeof(VkBorderColor)); p += sizeof(VkBorderColor);
        ExtraPushPrimitive<float>(s.mipLodBias, p);
        ExtraPushPrimitive<float>(s.minLod, p);
        ExtraPushPrimitive<float>(s.maxLod, p);
    }
};

EXTRA_STRUCT VkBinding
{
    VkBindingType type;
    int32_t shaderStages;
    int32_t set;
    int32_t binding;
    int32_t count;

    static inline int32_t SizeOf(const VkBinding& s)
    {
        return static_cast<int32_t>(sizeof(VkBinding));
    }

    static inline VkBinding Decode(const uint8_t* bytes)
    {
        VkBinding s;
        std::memcpy(&s, bytes, sizeof(VkBinding));
        return s;
    }

    static inline void Encode(const VkBinding& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkBinding));
    }
};

struct VkBindingInfo
{
    ExtraString name;
    ExtraList<VkBinding> bindings;

    static inline int32_t SizeOf(const VkBindingInfo& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t) + s.name.length * sizeof(char);
        size += sizeof(int32_t);
        { const uint8_t* r = s.bindings.data; for (int32_t i = 0; i < s.bindings.count; i++) { auto before = r; r += sizeof(VkBinding); size += static_cast<int32_t>(r - before); } }
        return size;
    }

    static inline VkBindingInfo Decode(const uint8_t* bytes)
    {
        VkBindingInfo s;
        const uint8_t* p = bytes;
        s.name = ExtraNextString(p);
        s.bindings = ExtraNextList<VkBinding>(p, [](const uint8_t*& p) { p += sizeof(VkBinding); });
        return s;
    }

    static inline void Encode(const VkBindingInfo& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushString(s.name, p);
        ExtraPushList<VkBinding>(s.bindings, p, [](const uint8_t*& r, uint8_t*& p) { { std::memcpy(p, r, sizeof(VkBinding)); p += sizeof(VkBinding); r += sizeof(VkBinding); }; });
    }
};

struct VkShaderInfo
{
    ExtraString name;
    ExtraString entryPoint;
    VkShaderStage stage;
    VkSpirvTarget spirvTarget;
    ExtraByteArray spirvCode;
    ExtraString textCode;

    static inline int32_t SizeOf(const VkShaderInfo& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t) + s.name.length * sizeof(char);
        size += sizeof(int32_t) + s.entryPoint.length * sizeof(char);
        size += sizeof(VkShaderStage);
        size += sizeof(VkSpirvTarget);
        size += sizeof(int32_t) + s.spirvCode.length * sizeof(uint8_t);
        size += sizeof(int32_t) + s.textCode.length * sizeof(char);
        return size;
    }

    static inline VkShaderInfo Decode(const uint8_t* bytes)
    {
        VkShaderInfo s;
        const uint8_t* p = bytes;
        s.name = ExtraNextString(p);
        s.entryPoint = ExtraNextString(p);
        std::memcpy(&s.stage, p, sizeof(VkShaderStage)); p += sizeof(VkShaderStage);
        std::memcpy(&s.spirvTarget, p, sizeof(VkSpirvTarget)); p += sizeof(VkSpirvTarget);
        s.spirvCode = ExtraNextArray<uint8_t>(p);
        s.textCode = ExtraNextString(p);
        return s;
    }

    static inline void Encode(const VkShaderInfo& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushString(s.name, p);
        ExtraPushString(s.entryPoint, p);
        std::memcpy(p, &s.stage, sizeof(VkShaderStage)); p += sizeof(VkShaderStage);
        std::memcpy(p, &s.spirvTarget, sizeof(VkSpirvTarget)); p += sizeof(VkSpirvTarget);
        ExtraPushArray<uint8_t>(s.spirvCode, p);
        ExtraPushString(s.textCode, p);
    }
};

EXTRA_STRUCT VkStencilState
{
    bool enabled;
    VkCompareOp compareOp;
    int32_t reference;
    int32_t compareMask;
    int32_t writeMask;
    VkStencilOp stencilFailOp;
    VkStencilOp depthFailOp;
    VkStencilOp passOp;

    static inline int32_t SizeOf(const VkStencilState& s)
    {
        return static_cast<int32_t>(sizeof(VkStencilState));
    }

    static inline VkStencilState Decode(const uint8_t* bytes)
    {
        VkStencilState s;
        std::memcpy(&s, bytes, sizeof(VkStencilState));
        return s;
    }

    static inline void Encode(const VkStencilState& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkStencilState));
    }
};

EXTRA_STRUCT VkBufferHandle
{
    int64_t address;

    static inline int32_t SizeOf(const VkBufferHandle& s)
    {
        return static_cast<int32_t>(sizeof(VkBufferHandle));
    }

    static inline VkBufferHandle Decode(const uint8_t* bytes)
    {
        VkBufferHandle s;
        std::memcpy(&s, bytes, sizeof(VkBufferHandle));
        return s;
    }

    static inline void Encode(const VkBufferHandle& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkBufferHandle));
    }
};

struct VkShaderHandle
{
    int64_t address;
    ExtraString name;

    static inline int32_t SizeOf(const VkShaderHandle& s)
    {
        int32_t size = 0;
        size += sizeof(int64_t);
        size += sizeof(int32_t) + s.name.length * sizeof(char);
        return size;
    }

    static inline VkShaderHandle Decode(const uint8_t* bytes)
    {
        VkShaderHandle s;
        const uint8_t* p = bytes;
        s.address = ExtraNextPrimitive<int64_t>(p);
        s.name = ExtraNextString(p);
        return s;
    }

    static inline void Encode(const VkShaderHandle& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushPrimitive<int64_t>(s.address, p);
        ExtraPushString(s.name, p);
    }
};

EXTRA_STRUCT VkRenderTargetHandle
{
    int64_t address;

    static inline int32_t SizeOf(const VkRenderTargetHandle& s)
    {
        return static_cast<int32_t>(sizeof(VkRenderTargetHandle));
    }

    static inline VkRenderTargetHandle Decode(const uint8_t* bytes)
    {
        VkRenderTargetHandle s;
        std::memcpy(&s, bytes, sizeof(VkRenderTargetHandle));
        return s;
    }

    static inline void Encode(const VkRenderTargetHandle& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkRenderTargetHandle));
    }
};

EXTRA_STRUCT VkBindingLayoutHandle
{
    int64_t address;

    static inline int32_t SizeOf(const VkBindingLayoutHandle& s)
    {
        return static_cast<int32_t>(sizeof(VkBindingLayoutHandle));
    }

    static inline VkBindingLayoutHandle Decode(const uint8_t* bytes)
    {
        VkBindingLayoutHandle s;
        std::memcpy(&s, bytes, sizeof(VkBindingLayoutHandle));
        return s;
    }

    static inline void Encode(const VkBindingLayoutHandle& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkBindingLayoutHandle));
    }
};

struct VkRenderPipelineInfo
{
    ExtraString name;
    bool instanced;
    VkPrimitiveTopology primitiveTopology;
    VkBufferHandle vertexBuffer;
    VkBufferHandle indexBuffer;
    VkShaderHandle vertexShader;
    VkShaderHandle fragmentShader;
    VkShaderHandle geometryShader;
    ExtraList<VkBindingLayoutHandle> bindingLayouts;
    float viewportX;
    float viewportY;
    float viewportWidth;
    float viewportHeight;
    float viewportMinDepth;
    float viewportMaxDepth;
    int32_t scissorX;
    int32_t scissorY;
    int32_t scissorWidth;
    int32_t scissorHeight;
    VkPolygonMode polygonMode;
    float lineWidth;
    VkCullMode cullMode;
    VkFrontFace frontFace;
    int32_t sampleCount;
    VkRenderTargetHandle renderTarget;
    VkStencilState stencilState;

    static inline int32_t SizeOf(const VkRenderPipelineInfo& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t) + s.name.length * sizeof(char);
        size += sizeof(bool);
        size += sizeof(VkPrimitiveTopology);
        size += sizeof(VkBufferHandle);
        size += sizeof(VkBufferHandle);
        size += VkShaderHandle::SizeOf(s.vertexShader);
        size += VkShaderHandle::SizeOf(s.fragmentShader);
        size += VkShaderHandle::SizeOf(s.geometryShader);
        size += sizeof(int32_t);
        { const uint8_t* r = s.bindingLayouts.data; for (int32_t i = 0; i < s.bindingLayouts.count; i++) { auto before = r; r += sizeof(VkBindingLayoutHandle); size += static_cast<int32_t>(r - before); } }
        size += sizeof(float);
        size += sizeof(float);
        size += sizeof(float);
        size += sizeof(float);
        size += sizeof(float);
        size += sizeof(float);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(VkPolygonMode);
        size += sizeof(float);
        size += sizeof(VkCullMode);
        size += sizeof(VkFrontFace);
        size += sizeof(int32_t);
        size += sizeof(VkRenderTargetHandle);
        size += sizeof(VkStencilState);
        return size;
    }

    static inline VkRenderPipelineInfo Decode(const uint8_t* bytes)
    {
        VkRenderPipelineInfo s;
        const uint8_t* p = bytes;
        s.name = ExtraNextString(p);
        s.instanced = ExtraNextPrimitive<bool>(p);
        std::memcpy(&s.primitiveTopology, p, sizeof(VkPrimitiveTopology)); p += sizeof(VkPrimitiveTopology);
        std::memcpy(&s.vertexBuffer, p, sizeof(VkBufferHandle)); p += sizeof(VkBufferHandle);
        std::memcpy(&s.indexBuffer, p, sizeof(VkBufferHandle)); p += sizeof(VkBufferHandle);
        s.vertexShader = VkShaderHandle::Decode(p); p += VkShaderHandle::SizeOf(s.vertexShader);
        s.fragmentShader = VkShaderHandle::Decode(p); p += VkShaderHandle::SizeOf(s.fragmentShader);
        s.geometryShader = VkShaderHandle::Decode(p); p += VkShaderHandle::SizeOf(s.geometryShader);
        s.bindingLayouts = ExtraNextList<VkBindingLayoutHandle>(p, [](const uint8_t*& p) { p += sizeof(VkBindingLayoutHandle); });
        s.viewportX = ExtraNextPrimitive<float>(p);
        s.viewportY = ExtraNextPrimitive<float>(p);
        s.viewportWidth = ExtraNextPrimitive<float>(p);
        s.viewportHeight = ExtraNextPrimitive<float>(p);
        s.viewportMinDepth = ExtraNextPrimitive<float>(p);
        s.viewportMaxDepth = ExtraNextPrimitive<float>(p);
        s.scissorX = ExtraNextPrimitive<int32_t>(p);
        s.scissorY = ExtraNextPrimitive<int32_t>(p);
        s.scissorWidth = ExtraNextPrimitive<int32_t>(p);
        s.scissorHeight = ExtraNextPrimitive<int32_t>(p);
        std::memcpy(&s.polygonMode, p, sizeof(VkPolygonMode)); p += sizeof(VkPolygonMode);
        s.lineWidth = ExtraNextPrimitive<float>(p);
        std::memcpy(&s.cullMode, p, sizeof(VkCullMode)); p += sizeof(VkCullMode);
        std::memcpy(&s.frontFace, p, sizeof(VkFrontFace)); p += sizeof(VkFrontFace);
        s.sampleCount = ExtraNextPrimitive<int32_t>(p);
        std::memcpy(&s.renderTarget, p, sizeof(VkRenderTargetHandle)); p += sizeof(VkRenderTargetHandle);
        std::memcpy(&s.stencilState, p, sizeof(VkStencilState)); p += sizeof(VkStencilState);
        return s;
    }

    static inline void Encode(const VkRenderPipelineInfo& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushString(s.name, p);
        ExtraPushPrimitive<bool>(s.instanced, p);
        std::memcpy(p, &s.primitiveTopology, sizeof(VkPrimitiveTopology)); p += sizeof(VkPrimitiveTopology);
        std::memcpy(p, &s.vertexBuffer, sizeof(VkBufferHandle)); p += sizeof(VkBufferHandle);
        std::memcpy(p, &s.indexBuffer, sizeof(VkBufferHandle)); p += sizeof(VkBufferHandle);
        VkShaderHandle::Encode(s.vertexShader, p); p += VkShaderHandle::SizeOf(s.vertexShader);
        VkShaderHandle::Encode(s.fragmentShader, p); p += VkShaderHandle::SizeOf(s.fragmentShader);
        VkShaderHandle::Encode(s.geometryShader, p); p += VkShaderHandle::SizeOf(s.geometryShader);
        ExtraPushList<VkBindingLayoutHandle>(s.bindingLayouts, p, [](const uint8_t*& r, uint8_t*& p) { { std::memcpy(p, r, sizeof(VkBindingLayoutHandle)); p += sizeof(VkBindingLayoutHandle); r += sizeof(VkBindingLayoutHandle); }; });
        ExtraPushPrimitive<float>(s.viewportX, p);
        ExtraPushPrimitive<float>(s.viewportY, p);
        ExtraPushPrimitive<float>(s.viewportWidth, p);
        ExtraPushPrimitive<float>(s.viewportHeight, p);
        ExtraPushPrimitive<float>(s.viewportMinDepth, p);
        ExtraPushPrimitive<float>(s.viewportMaxDepth, p);
        ExtraPushPrimitive<int32_t>(s.scissorX, p);
        ExtraPushPrimitive<int32_t>(s.scissorY, p);
        ExtraPushPrimitive<int32_t>(s.scissorWidth, p);
        ExtraPushPrimitive<int32_t>(s.scissorHeight, p);
        std::memcpy(p, &s.polygonMode, sizeof(VkPolygonMode)); p += sizeof(VkPolygonMode);
        ExtraPushPrimitive<float>(s.lineWidth, p);
        std::memcpy(p, &s.cullMode, sizeof(VkCullMode)); p += sizeof(VkCullMode);
        std::memcpy(p, &s.frontFace, sizeof(VkFrontFace)); p += sizeof(VkFrontFace);
        ExtraPushPrimitive<int32_t>(s.sampleCount, p);
        std::memcpy(p, &s.renderTarget, sizeof(VkRenderTargetHandle)); p += sizeof(VkRenderTargetHandle);
        std::memcpy(p, &s.stencilState, sizeof(VkStencilState)); p += sizeof(VkStencilState);
    }
};

struct VkComputePipelineInfo
{
    ExtraString name;
    VkShaderHandle computeShader;
    ExtraList<VkBindingLayoutHandle> bindingLayouts;

    static inline int32_t SizeOf(const VkComputePipelineInfo& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t) + s.name.length * sizeof(char);
        size += VkShaderHandle::SizeOf(s.computeShader);
        size += sizeof(int32_t);
        { const uint8_t* r = s.bindingLayouts.data; for (int32_t i = 0; i < s.bindingLayouts.count; i++) { auto before = r; r += sizeof(VkBindingLayoutHandle); size += static_cast<int32_t>(r - before); } }
        return size;
    }

    static inline VkComputePipelineInfo Decode(const uint8_t* bytes)
    {
        VkComputePipelineInfo s;
        const uint8_t* p = bytes;
        s.name = ExtraNextString(p);
        s.computeShader = VkShaderHandle::Decode(p); p += VkShaderHandle::SizeOf(s.computeShader);
        s.bindingLayouts = ExtraNextList<VkBindingLayoutHandle>(p, [](const uint8_t*& p) { p += sizeof(VkBindingLayoutHandle); });
        return s;
    }

    static inline void Encode(const VkComputePipelineInfo& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushString(s.name, p);
        VkShaderHandle::Encode(s.computeShader, p); p += VkShaderHandle::SizeOf(s.computeShader);
        ExtraPushList<VkBindingLayoutHandle>(s.bindingLayouts, p, [](const uint8_t*& r, uint8_t*& p) { { std::memcpy(p, r, sizeof(VkBindingLayoutHandle)); p += sizeof(VkBindingLayoutHandle); r += sizeof(VkBindingLayoutHandle); }; });
    }
};

EXTRA_STRUCT VkDepthAttachment
{
    VkTextureHandle texture;
    bool enabled;
    float depthClearValue;
    VkCompareOp depthCompareOp;
    bool depthReadOnly;
    bool depthWriteEnabled;

    static inline int32_t SizeOf(const VkDepthAttachment& s)
    {
        return static_cast<int32_t>(sizeof(VkDepthAttachment));
    }

    static inline VkDepthAttachment Decode(const uint8_t* bytes)
    {
        VkDepthAttachment s;
        std::memcpy(&s, bytes, sizeof(VkDepthAttachment));
        return s;
    }

    static inline void Encode(const VkDepthAttachment& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkDepthAttachment));
    }
};

EXTRA_STRUCT VkStencilAttachment
{
    VkTextureHandle texture;
    bool enabled;
    int32_t stencilClearValue;

    static inline int32_t SizeOf(const VkStencilAttachment& s)
    {
        return static_cast<int32_t>(sizeof(VkStencilAttachment));
    }

    static inline VkStencilAttachment Decode(const uint8_t* bytes)
    {
        VkStencilAttachment s;
        std::memcpy(&s, bytes, sizeof(VkStencilAttachment));
        return s;
    }

    static inline void Encode(const VkStencilAttachment& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkStencilAttachment));
    }
};

struct VkRenderTargetInfo
{
    ExtraString name;
    bool isSwapchain;
    int32_t x;
    int32_t y;
    int32_t width;
    int32_t height;
    int32_t depth;
    ExtraList<VkColorAttachment> colorAttachments;
    VkDepthAttachment depthAttachment;
    VkStencilAttachment stencilAttachment;

    static inline int32_t SizeOf(const VkRenderTargetInfo& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t) + s.name.length * sizeof(char);
        size += sizeof(bool);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        { const uint8_t* r = s.colorAttachments.data; for (int32_t i = 0; i < s.colorAttachments.count; i++) { auto before = r; r += sizeof(VkColorAttachment); size += static_cast<int32_t>(r - before); } }
        size += sizeof(VkDepthAttachment);
        size += sizeof(VkStencilAttachment);
        return size;
    }

    static inline VkRenderTargetInfo Decode(const uint8_t* bytes)
    {
        VkRenderTargetInfo s;
        const uint8_t* p = bytes;
        s.name = ExtraNextString(p);
        s.isSwapchain = ExtraNextPrimitive<bool>(p);
        s.x = ExtraNextPrimitive<int32_t>(p);
        s.y = ExtraNextPrimitive<int32_t>(p);
        s.width = ExtraNextPrimitive<int32_t>(p);
        s.height = ExtraNextPrimitive<int32_t>(p);
        s.depth = ExtraNextPrimitive<int32_t>(p);
        s.colorAttachments = ExtraNextList<VkColorAttachment>(p, [](const uint8_t*& p) { p += sizeof(VkColorAttachment); });
        std::memcpy(&s.depthAttachment, p, sizeof(VkDepthAttachment)); p += sizeof(VkDepthAttachment);
        std::memcpy(&s.stencilAttachment, p, sizeof(VkStencilAttachment)); p += sizeof(VkStencilAttachment);
        return s;
    }

    static inline void Encode(const VkRenderTargetInfo& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushString(s.name, p);
        ExtraPushPrimitive<bool>(s.isSwapchain, p);
        ExtraPushPrimitive<int32_t>(s.x, p);
        ExtraPushPrimitive<int32_t>(s.y, p);
        ExtraPushPrimitive<int32_t>(s.width, p);
        ExtraPushPrimitive<int32_t>(s.height, p);
        ExtraPushPrimitive<int32_t>(s.depth, p);
        ExtraPushList<VkColorAttachment>(s.colorAttachments, p, [](const uint8_t*& r, uint8_t*& p) { { std::memcpy(p, r, sizeof(VkColorAttachment)); p += sizeof(VkColorAttachment); r += sizeof(VkColorAttachment); }; });
        std::memcpy(p, &s.depthAttachment, sizeof(VkDepthAttachment)); p += sizeof(VkDepthAttachment);
        std::memcpy(p, &s.stencilAttachment, sizeof(VkStencilAttachment)); p += sizeof(VkStencilAttachment);
    }
};

EXTRA_STRUCT VkRenderContextHandle
{
    int64_t address;

    static inline int32_t SizeOf(const VkRenderContextHandle& s)
    {
        return static_cast<int32_t>(sizeof(VkRenderContextHandle));
    }

    static inline VkRenderContextHandle Decode(const uint8_t* bytes)
    {
        VkRenderContextHandle s;
        std::memcpy(&s, bytes, sizeof(VkRenderContextHandle));
        return s;
    }

    static inline void Encode(const VkRenderContextHandle& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkRenderContextHandle));
    }
};

EXTRA_STRUCT VkRenderPipelineHandle
{
    int64_t address;

    static inline int32_t SizeOf(const VkRenderPipelineHandle& s)
    {
        return static_cast<int32_t>(sizeof(VkRenderPipelineHandle));
    }

    static inline VkRenderPipelineHandle Decode(const uint8_t* bytes)
    {
        VkRenderPipelineHandle s;
        std::memcpy(&s, bytes, sizeof(VkRenderPipelineHandle));
        return s;
    }

    static inline void Encode(const VkRenderPipelineHandle& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkRenderPipelineHandle));
    }
};

EXTRA_STRUCT VkComputePipelineHandle
{
    int64_t address;

    static inline int32_t SizeOf(const VkComputePipelineHandle& s)
    {
        return static_cast<int32_t>(sizeof(VkComputePipelineHandle));
    }

    static inline VkComputePipelineHandle Decode(const uint8_t* bytes)
    {
        VkComputePipelineHandle s;
        std::memcpy(&s, bytes, sizeof(VkComputePipelineHandle));
        return s;
    }

    static inline void Encode(const VkComputePipelineHandle& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkComputePipelineHandle));
    }
};

EXTRA_STRUCT VkSamplerHandle
{
    int64_t address;

    static inline int32_t SizeOf(const VkSamplerHandle& s)
    {
        return static_cast<int32_t>(sizeof(VkSamplerHandle));
    }

    static inline VkSamplerHandle Decode(const uint8_t* bytes)
    {
        VkSamplerHandle s;
        std::memcpy(&s, bytes, sizeof(VkSamplerHandle));
        return s;
    }

    static inline void Encode(const VkSamplerHandle& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkSamplerHandle));
    }
};

EXTRA_STRUCT VkCommandBufferHandle
{
    int64_t address;

    static inline int32_t SizeOf(const VkCommandBufferHandle& s)
    {
        return static_cast<int32_t>(sizeof(VkCommandBufferHandle));
    }

    static inline VkCommandBufferHandle Decode(const uint8_t* bytes)
    {
        VkCommandBufferHandle s;
        std::memcpy(&s, bytes, sizeof(VkCommandBufferHandle));
        return s;
    }

    static inline void Encode(const VkCommandBufferHandle& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkCommandBufferHandle));
    }
};

struct VkUIntList
{
    int32_t size;
    VkUIntArray array;

    static inline int32_t SizeOf(const VkUIntList& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t);
        size += sizeof(int32_t) + s.array.length * sizeof(uint8_t);
        return size;
    }

    static inline VkUIntList Decode(const uint8_t* bytes)
    {
        VkUIntList s;
        const uint8_t* p = bytes;
        s.size = ExtraNextPrimitive<int32_t>(p);
        s.array = ExtraNextArray<uint8_t>(p);
        return s;
    }

    static inline void Encode(const VkUIntList& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushPrimitive<int32_t>(s.size, p);
        ExtraPushArray<uint8_t>(s.array, p);
    }
};

struct VkByteList
{
    int32_t size;
    ExtraByteArray array;

    static inline int32_t SizeOf(const VkByteList& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t);
        size += sizeof(int32_t) + s.array.length * sizeof(uint8_t);
        return size;
    }

    static inline VkByteList Decode(const uint8_t* bytes)
    {
        VkByteList s;
        const uint8_t* p = bytes;
        s.size = ExtraNextPrimitive<int32_t>(p);
        s.array = ExtraNextArray<uint8_t>(p);
        return s;
    }

    static inline void Encode(const VkByteList& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushPrimitive<int32_t>(s.size, p);
        ExtraPushArray<uint8_t>(s.array, p);
    }
};

struct VkUByteList
{
    int32_t size;
    VkUByteArray array;

    static inline int32_t SizeOf(const VkUByteList& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t);
        size += sizeof(int32_t) + s.array.length * sizeof(uint8_t);
        return size;
    }

    static inline VkUByteList Decode(const uint8_t* bytes)
    {
        VkUByteList s;
        const uint8_t* p = bytes;
        s.size = ExtraNextPrimitive<int32_t>(p);
        s.array = ExtraNextArray<uint8_t>(p);
        return s;
    }

    static inline void Encode(const VkUByteList& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushPrimitive<int32_t>(s.size, p);
        ExtraPushArray<uint8_t>(s.array, p);
    }
};

struct VkCharList
{
    int32_t size;
    ExtraChar16Array array;

    static inline int32_t SizeOf(const VkCharList& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t);
        size += sizeof(int32_t) + s.array.length * sizeof(uint16_t);
        return size;
    }

    static inline VkCharList Decode(const uint8_t* bytes)
    {
        VkCharList s;
        const uint8_t* p = bytes;
        s.size = ExtraNextPrimitive<int32_t>(p);
        s.array = ExtraNextArray<uint16_t>(p);
        return s;
    }

    static inline void Encode(const VkCharList& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushPrimitive<int32_t>(s.size, p);
        ExtraPushArray<uint16_t>(s.array, p);
    }
};

struct VkShortList
{
    int32_t size;
    ExtraShortArray array;

    static inline int32_t SizeOf(const VkShortList& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t);
        size += sizeof(int32_t) + s.array.length * sizeof(int16_t);
        return size;
    }

    static inline VkShortList Decode(const uint8_t* bytes)
    {
        VkShortList s;
        const uint8_t* p = bytes;
        s.size = ExtraNextPrimitive<int32_t>(p);
        s.array = ExtraNextArray<int16_t>(p);
        return s;
    }

    static inline void Encode(const VkShortList& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushPrimitive<int32_t>(s.size, p);
        ExtraPushArray<int16_t>(s.array, p);
    }
};

struct VkDoubleList
{
    int32_t size;
    ExtraDoubleArray array;

    static inline int32_t SizeOf(const VkDoubleList& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t);
        size += sizeof(int32_t) + s.array.length * sizeof(double);
        return size;
    }

    static inline VkDoubleList Decode(const uint8_t* bytes)
    {
        VkDoubleList s;
        const uint8_t* p = bytes;
        s.size = ExtraNextPrimitive<int32_t>(p);
        s.array = ExtraNextArray<double>(p);
        return s;
    }

    static inline void Encode(const VkDoubleList& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushPrimitive<int32_t>(s.size, p);
        ExtraPushArray<double>(s.array, p);
    }
};

struct VkFloatList
{
    int32_t size;
    ExtraFloatArray array;

    static inline int32_t SizeOf(const VkFloatList& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t);
        size += sizeof(int32_t) + s.array.length * sizeof(float);
        return size;
    }

    static inline VkFloatList Decode(const uint8_t* bytes)
    {
        VkFloatList s;
        const uint8_t* p = bytes;
        s.size = ExtraNextPrimitive<int32_t>(p);
        s.array = ExtraNextArray<float>(p);
        return s;
    }

    static inline void Encode(const VkFloatList& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushPrimitive<int32_t>(s.size, p);
        ExtraPushArray<float>(s.array, p);
    }
};

struct VkIntList
{
    int32_t size;
    ExtraIntArray array;

    static inline int32_t SizeOf(const VkIntList& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t);
        size += sizeof(int32_t) + s.array.length * sizeof(int32_t);
        return size;
    }

    static inline VkIntList Decode(const uint8_t* bytes)
    {
        VkIntList s;
        const uint8_t* p = bytes;
        s.size = ExtraNextPrimitive<int32_t>(p);
        s.array = ExtraNextArray<int32_t>(p);
        return s;
    }

    static inline void Encode(const VkIntList& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushPrimitive<int32_t>(s.size, p);
        ExtraPushArray<int32_t>(s.array, p);
    }
};

struct VkBooleanList
{
    int32_t size;
    VkBooleanArray array;

    static inline int32_t SizeOf(const VkBooleanList& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t);
        size += sizeof(int32_t) + s.array.length * sizeof(uint8_t);
        return size;
    }

    static inline VkBooleanList Decode(const uint8_t* bytes)
    {
        VkBooleanList s;
        const uint8_t* p = bytes;
        s.size = ExtraNextPrimitive<int32_t>(p);
        s.array = ExtraNextArray<uint8_t>(p);
        return s;
    }

    static inline void Encode(const VkBooleanList& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushPrimitive<int32_t>(s.size, p);
        ExtraPushArray<uint8_t>(s.array, p);
    }
};

struct VkUShortList
{
    int32_t size;
    VkUShortArray array;

    static inline int32_t SizeOf(const VkUShortList& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t);
        size += sizeof(int32_t) + s.array.length * sizeof(uint8_t);
        return size;
    }

    static inline VkUShortList Decode(const uint8_t* bytes)
    {
        VkUShortList s;
        const uint8_t* p = bytes;
        s.size = ExtraNextPrimitive<int32_t>(p);
        s.array = ExtraNextArray<uint8_t>(p);
        return s;
    }

    static inline void Encode(const VkUShortList& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushPrimitive<int32_t>(s.size, p);
        ExtraPushArray<uint8_t>(s.array, p);
    }
};

struct VkULongList
{
    int32_t size;
    VkULongArray array;

    static inline int32_t SizeOf(const VkULongList& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t);
        size += sizeof(int32_t) + s.array.length * sizeof(uint8_t);
        return size;
    }

    static inline VkULongList Decode(const uint8_t* bytes)
    {
        VkULongList s;
        const uint8_t* p = bytes;
        s.size = ExtraNextPrimitive<int32_t>(p);
        s.array = ExtraNextArray<uint8_t>(p);
        return s;
    }

    static inline void Encode(const VkULongList& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushPrimitive<int32_t>(s.size, p);
        ExtraPushArray<uint8_t>(s.array, p);
    }
};

struct VkLongList
{
    int32_t size;
    ExtraLongArray array;

    static inline int32_t SizeOf(const VkLongList& s)
    {
        int32_t size = 0;
        size += sizeof(int32_t);
        size += sizeof(int32_t) + s.array.length * sizeof(int64_t);
        return size;
    }

    static inline VkLongList Decode(const uint8_t* bytes)
    {
        VkLongList s;
        const uint8_t* p = bytes;
        s.size = ExtraNextPrimitive<int32_t>(p);
        s.array = ExtraNextArray<int64_t>(p);
        return s;
    }

    static inline void Encode(const VkLongList& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushPrimitive<int32_t>(s.size, p);
        ExtraPushArray<int64_t>(s.array, p);
    }
};

struct VkEntityPool
{
    VkBooleanList alive;
    VkIntList removed;
    VkIntList bulk;
    int32_t nextId;

    static inline int32_t SizeOf(const VkEntityPool& s)
    {
        int32_t size = 0;
        size += VkBooleanList::SizeOf(s.alive);
        size += VkIntList::SizeOf(s.removed);
        size += VkIntList::SizeOf(s.bulk);
        size += sizeof(int32_t);
        return size;
    }

    static inline VkEntityPool Decode(const uint8_t* bytes)
    {
        VkEntityPool s;
        const uint8_t* p = bytes;
        s.alive = VkBooleanList::Decode(p); p += VkBooleanList::SizeOf(s.alive);
        s.removed = VkIntList::Decode(p); p += VkIntList::SizeOf(s.removed);
        s.bulk = VkIntList::Decode(p); p += VkIntList::SizeOf(s.bulk);
        s.nextId = ExtraNextPrimitive<int32_t>(p);
        return s;
    }

    static inline void Encode(const VkEntityPool& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        VkBooleanList::Encode(s.alive, p); p += VkBooleanList::SizeOf(s.alive);
        VkIntList::Encode(s.removed, p); p += VkIntList::SizeOf(s.removed);
        VkIntList::Encode(s.bulk, p); p += VkIntList::SizeOf(s.bulk);
        ExtraPushPrimitive<int32_t>(s.nextId, p);
    }
};

struct VkScene
{
    VkEntityPool entities;
    VkComponentsState components;

    static inline int32_t SizeOf(const VkScene& s)
    {
        int32_t size = 0;
        size += VkEntityPool::SizeOf(s.entities);
        size += sizeof(VkComponentsState);
        return size;
    }

    static inline VkScene Decode(const uint8_t* bytes)
    {
        VkScene s;
        const uint8_t* p = bytes;
        s.entities = VkEntityPool::Decode(p); p += VkEntityPool::SizeOf(s.entities);
        std::memcpy(&s.components, p, sizeof(VkComponentsState)); p += sizeof(VkComponentsState);
        return s;
    }

    static inline void Encode(const VkScene& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        VkEntityPool::Encode(s.entities, p); p += VkEntityPool::SizeOf(s.entities);
        std::memcpy(p, &s.components, sizeof(VkComponentsState)); p += sizeof(VkComponentsState);
    }
};

struct VkComponentPool
{
    VkIntList entityToComponent;
    VkIntList componentToEntity;

    static inline int32_t SizeOf(const VkComponentPool& s)
    {
        int32_t size = 0;
        size += VkIntList::SizeOf(s.entityToComponent);
        size += VkIntList::SizeOf(s.componentToEntity);
        return size;
    }

    static inline VkComponentPool Decode(const uint8_t* bytes)
    {
        VkComponentPool s;
        const uint8_t* p = bytes;
        s.entityToComponent = VkIntList::Decode(p); p += VkIntList::SizeOf(s.entityToComponent);
        s.componentToEntity = VkIntList::Decode(p); p += VkIntList::SizeOf(s.componentToEntity);
        return s;
    }

    static inline void Encode(const VkComponentPool& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        VkIntList::Encode(s.entityToComponent, p); p += VkIntList::SizeOf(s.entityToComponent);
        VkIntList::Encode(s.componentToEntity, p); p += VkIntList::SizeOf(s.componentToEntity);
    }
};

EXTRA_STRUCT VkInt2
{
    int32_t x;
    int32_t y;

    static inline int32_t SizeOf(const VkInt2& s)
    {
        return static_cast<int32_t>(sizeof(VkInt2));
    }

    static inline VkInt2 Decode(const uint8_t* bytes)
    {
        VkInt2 s;
        std::memcpy(&s, bytes, sizeof(VkInt2));
        return s;
    }

    static inline void Encode(const VkInt2& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkInt2));
    }
};

EXTRA_STRUCT VkUInt4
{
    VkUInt x;
    VkUInt y;
    VkUInt z;
    VkUInt w;

    static inline int32_t SizeOf(const VkUInt4& s)
    {
        return static_cast<int32_t>(sizeof(VkUInt4));
    }

    static inline VkUInt4 Decode(const uint8_t* bytes)
    {
        VkUInt4 s;
        std::memcpy(&s, bytes, sizeof(VkUInt4));
        return s;
    }

    static inline void Encode(const VkUInt4& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkUInt4));
    }
};

EXTRA_STRUCT VkInt3
{
    int32_t x;
    int32_t y;
    int32_t z;

    static inline int32_t SizeOf(const VkInt3& s)
    {
        return static_cast<int32_t>(sizeof(VkInt3));
    }

    static inline VkInt3 Decode(const uint8_t* bytes)
    {
        VkInt3 s;
        std::memcpy(&s, bytes, sizeof(VkInt3));
        return s;
    }

    static inline void Encode(const VkInt3& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkInt3));
    }
};

EXTRA_STRUCT VkInt4
{
    int32_t x;
    int32_t y;
    int32_t z;
    int32_t w;

    static inline int32_t SizeOf(const VkInt4& s)
    {
        return static_cast<int32_t>(sizeof(VkInt4));
    }

    static inline VkInt4 Decode(const uint8_t* bytes)
    {
        VkInt4 s;
        std::memcpy(&s, bytes, sizeof(VkInt4));
        return s;
    }

    static inline void Encode(const VkInt4& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkInt4));
    }
};

EXTRA_STRUCT VkUInt2
{
    VkUInt x;
    VkUInt y;

    static inline int32_t SizeOf(const VkUInt2& s)
    {
        return static_cast<int32_t>(sizeof(VkUInt2));
    }

    static inline VkUInt2 Decode(const uint8_t* bytes)
    {
        VkUInt2 s;
        std::memcpy(&s, bytes, sizeof(VkUInt2));
        return s;
    }

    static inline void Encode(const VkUInt2& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkUInt2));
    }
};

EXTRA_STRUCT VkFloat3
{
    float x;
    float y;
    float z;

    static inline int32_t SizeOf(const VkFloat3& s)
    {
        return static_cast<int32_t>(sizeof(VkFloat3));
    }

    static inline VkFloat3 Decode(const uint8_t* bytes)
    {
        VkFloat3 s;
        std::memcpy(&s, bytes, sizeof(VkFloat3));
        return s;
    }

    static inline void Encode(const VkFloat3& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkFloat3));
    }
};

EXTRA_STRUCT VkFloat2
{
    float x;
    float y;

    static inline int32_t SizeOf(const VkFloat2& s)
    {
        return static_cast<int32_t>(sizeof(VkFloat2));
    }

    static inline VkFloat2 Decode(const uint8_t* bytes)
    {
        VkFloat2 s;
        std::memcpy(&s, bytes, sizeof(VkFloat2));
        return s;
    }

    static inline void Encode(const VkFloat2& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkFloat2));
    }
};

EXTRA_STRUCT VkQuaternion
{
    float x;
    float y;
    float z;
    float w;

    static inline int32_t SizeOf(const VkQuaternion& s)
    {
        return static_cast<int32_t>(sizeof(VkQuaternion));
    }

    static inline VkQuaternion Decode(const uint8_t* bytes)
    {
        VkQuaternion s;
        std::memcpy(&s, bytes, sizeof(VkQuaternion));
        return s;
    }

    static inline void Encode(const VkQuaternion& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkQuaternion));
    }
};

EXTRA_STRUCT VkUInt3
{
    VkUInt x;
    VkUInt y;
    VkUInt z;

    static inline int32_t SizeOf(const VkUInt3& s)
    {
        return static_cast<int32_t>(sizeof(VkUInt3));
    }

    static inline VkUInt3 Decode(const uint8_t* bytes)
    {
        VkUInt3 s;
        std::memcpy(&s, bytes, sizeof(VkUInt3));
        return s;
    }

    static inline void Encode(const VkUInt3& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkUInt3));
    }
};

EXTRA_STRUCT VkMat4
{
    float m00;
    float m01;
    float m02;
    float m03;
    float m10;
    float m11;
    float m12;
    float m13;
    float m20;
    float m21;
    float m22;
    float m23;
    float m30;
    float m31;
    float m32;
    float m33;

    static inline int32_t SizeOf(const VkMat4& s)
    {
        return static_cast<int32_t>(sizeof(VkMat4));
    }

    static inline VkMat4 Decode(const uint8_t* bytes)
    {
        VkMat4 s;
        std::memcpy(&s, bytes, sizeof(VkMat4));
        return s;
    }

    static inline void Encode(const VkMat4& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkMat4));
    }
};

EXTRA_STRUCT VkMat2
{
    float m00;
    float m01;
    float m10;
    float m11;

    static inline int32_t SizeOf(const VkMat2& s)
    {
        return static_cast<int32_t>(sizeof(VkMat2));
    }

    static inline VkMat2 Decode(const uint8_t* bytes)
    {
        VkMat2 s;
        std::memcpy(&s, bytes, sizeof(VkMat2));
        return s;
    }

    static inline void Encode(const VkMat2& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkMat2));
    }
};

EXTRA_STRUCT VkMat3
{
    float m00;
    float m01;
    float m02;
    float m10;
    float m11;
    float m12;
    float m20;
    float m21;
    float m22;

    static inline int32_t SizeOf(const VkMat3& s)
    {
        return static_cast<int32_t>(sizeof(VkMat3));
    }

    static inline VkMat3 Decode(const uint8_t* bytes)
    {
        VkMat3 s;
        std::memcpy(&s, bytes, sizeof(VkMat3));
        return s;
    }

    static inline void Encode(const VkMat3& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkMat3));
    }
};

struct VkNestedData
{
    int64_t id;
    VkFloat2 float2;
    VkFloat3 float3;
    VkFloat4 float4;
    VkInt2 int2;
    VkInt3 int3;
    VkInt4 int4;
    VkUInt2 uint2;
    VkUInt3 uInt3;
    VkUInt4 uInt4;
    VkMat2 mat2;
    VkMat3 mat3;
    VkMat4 mat4;
    VkQuaternion quaternion;
    ExtraMap<ExtraString, ExtraString> data;
    ExtraList<ExtraString> subscribers;

    static inline int32_t SizeOf(const VkNestedData& s)
    {
        int32_t size = 0;
        size += sizeof(int64_t);
        size += sizeof(VkFloat2);
        size += sizeof(VkFloat3);
        size += sizeof(VkFloat4);
        size += sizeof(VkInt2);
        size += sizeof(VkInt3);
        size += sizeof(VkInt4);
        size += sizeof(VkUInt2);
        size += sizeof(VkUInt3);
        size += sizeof(VkUInt4);
        size += sizeof(VkMat2);
        size += sizeof(VkMat3);
        size += sizeof(VkMat4);
        size += sizeof(VkQuaternion);
        size += sizeof(int32_t);
        { const uint8_t* r = s.data.data; for (int32_t i = 0; i < s.data.count; i++) { auto before = r; ExtraNextString(r); ExtraNextString(r); size += static_cast<int32_t>(r - before); } }
        size += sizeof(int32_t);
        { const uint8_t* r = s.subscribers.data; for (int32_t i = 0; i < s.subscribers.count; i++) { auto before = r; ExtraNextString(r); size += static_cast<int32_t>(r - before); } }
        return size;
    }

    static inline VkNestedData Decode(const uint8_t* bytes)
    {
        VkNestedData s;
        const uint8_t* p = bytes;
        s.id = ExtraNextPrimitive<int64_t>(p);
        std::memcpy(&s.float2, p, sizeof(VkFloat2)); p += sizeof(VkFloat2);
        std::memcpy(&s.float3, p, sizeof(VkFloat3)); p += sizeof(VkFloat3);
        std::memcpy(&s.float4, p, sizeof(VkFloat4)); p += sizeof(VkFloat4);
        std::memcpy(&s.int2, p, sizeof(VkInt2)); p += sizeof(VkInt2);
        std::memcpy(&s.int3, p, sizeof(VkInt3)); p += sizeof(VkInt3);
        std::memcpy(&s.int4, p, sizeof(VkInt4)); p += sizeof(VkInt4);
        std::memcpy(&s.uint2, p, sizeof(VkUInt2)); p += sizeof(VkUInt2);
        std::memcpy(&s.uInt3, p, sizeof(VkUInt3)); p += sizeof(VkUInt3);
        std::memcpy(&s.uInt4, p, sizeof(VkUInt4)); p += sizeof(VkUInt4);
        std::memcpy(&s.mat2, p, sizeof(VkMat2)); p += sizeof(VkMat2);
        std::memcpy(&s.mat3, p, sizeof(VkMat3)); p += sizeof(VkMat3);
        std::memcpy(&s.mat4, p, sizeof(VkMat4)); p += sizeof(VkMat4);
        std::memcpy(&s.quaternion, p, sizeof(VkQuaternion)); p += sizeof(VkQuaternion);
        s.data = ExtraNextMap<ExtraString, ExtraString>(p, [](const uint8_t*& p) { ExtraNextString(p); }, [](const uint8_t*& p) { ExtraNextString(p); });
        s.subscribers = ExtraNextList<ExtraString>(p, [](const uint8_t*& p) { ExtraNextString(p); });
        return s;
    }

    static inline void Encode(const VkNestedData& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushPrimitive<int64_t>(s.id, p);
        std::memcpy(p, &s.float2, sizeof(VkFloat2)); p += sizeof(VkFloat2);
        std::memcpy(p, &s.float3, sizeof(VkFloat3)); p += sizeof(VkFloat3);
        std::memcpy(p, &s.float4, sizeof(VkFloat4)); p += sizeof(VkFloat4);
        std::memcpy(p, &s.int2, sizeof(VkInt2)); p += sizeof(VkInt2);
        std::memcpy(p, &s.int3, sizeof(VkInt3)); p += sizeof(VkInt3);
        std::memcpy(p, &s.int4, sizeof(VkInt4)); p += sizeof(VkInt4);
        std::memcpy(p, &s.uint2, sizeof(VkUInt2)); p += sizeof(VkUInt2);
        std::memcpy(p, &s.uInt3, sizeof(VkUInt3)); p += sizeof(VkUInt3);
        std::memcpy(p, &s.uInt4, sizeof(VkUInt4)); p += sizeof(VkUInt4);
        std::memcpy(p, &s.mat2, sizeof(VkMat2)); p += sizeof(VkMat2);
        std::memcpy(p, &s.mat3, sizeof(VkMat3)); p += sizeof(VkMat3);
        std::memcpy(p, &s.mat4, sizeof(VkMat4)); p += sizeof(VkMat4);
        std::memcpy(p, &s.quaternion, sizeof(VkQuaternion)); p += sizeof(VkQuaternion);
        ExtraPushMap<ExtraString, ExtraString>(s.data, p, [](const uint8_t*& r, uint8_t*& p) { ExtraPushString(ExtraNextString(r), p); }, [](const uint8_t*& r, uint8_t*& p) { ExtraPushString(ExtraNextString(r), p); });
        ExtraPushList<ExtraString>(s.subscribers, p, [](const uint8_t*& r, uint8_t*& p) { ExtraPushString(ExtraNextString(r), p); });
    }
};

struct VkTestData
{
    int64_t id;
    int64_t timestamp;
    ExtraString name;
    int32_t width;
    int32_t height;
    float x;
    float y;
    bool flag;
    int16_t age;
    VkTestEnumOrdinal ordinalEnum;
    VkTestEnumRaw rawEnum;
    char fixedStringUtf8[12];
    ExtraString stringUtf8;
    uint16_t fixedStringUtf16[18];
    ExtraString16 stringUtf16;
    uint8_t fixedBytes[24];
    ExtraByteArray bytes;
    int16_t fixedShorts[48];
    ExtraShortArray shorts;
    int32_t fixedInts[64];
    ExtraIntArray ints;
    int64_t fixedLongs[36];
    ExtraLongArray longs;
    float fixedFloats[36];
    ExtraFloatArray floats;
    double fixedDoubles[36];
    ExtraDoubleArray doubles;
    VkNativeBuffer nestedDataBuffer;
    ExtraList<VkNestedData> data;

    static inline int32_t SizeOf(const VkTestData& s)
    {
        int32_t size = 0;
        size += sizeof(int64_t);
        size += sizeof(int64_t);
        size += sizeof(int32_t) + s.name.length * sizeof(char);
        size += sizeof(int32_t);
        size += sizeof(int32_t);
        size += sizeof(float);
        size += sizeof(float);
        size += sizeof(bool);
        size += sizeof(int16_t);
        size += sizeof(VkTestEnumOrdinal);
        size += sizeof(VkTestEnumRaw);
        size += 12 * sizeof(char);
        size += sizeof(int32_t) + s.stringUtf8.length * sizeof(char);
        size += 18 * sizeof(uint16_t);
        size += sizeof(int32_t) + s.stringUtf16.length * sizeof(uint16_t);
        size += 24 * sizeof(uint8_t);
        size += sizeof(int32_t) + s.bytes.length * sizeof(uint8_t);
        size += 48 * sizeof(int16_t);
        size += sizeof(int32_t) + s.shorts.length * sizeof(int16_t);
        size += 64 * sizeof(int32_t);
        size += sizeof(int32_t) + s.ints.length * sizeof(int32_t);
        size += 36 * sizeof(int64_t);
        size += sizeof(int32_t) + s.longs.length * sizeof(int64_t);
        size += 36 * sizeof(float);
        size += sizeof(int32_t) + s.floats.length * sizeof(float);
        size += 36 * sizeof(double);
        size += sizeof(int32_t) + s.doubles.length * sizeof(double);
        size += sizeof(VkNativeBuffer);
        size += sizeof(int32_t);
        { const uint8_t* r = s.data.data; for (int32_t i = 0; i < s.data.count; i++) { auto before = r; { auto tmp = VkNestedData::Decode(r); r += VkNestedData::SizeOf(tmp); }; size += static_cast<int32_t>(r - before); } }
        return size;
    }

    static inline VkTestData Decode(const uint8_t* bytes)
    {
        VkTestData s;
        const uint8_t* p = bytes;
        s.id = ExtraNextPrimitive<int64_t>(p);
        s.timestamp = ExtraNextPrimitive<int64_t>(p);
        s.name = ExtraNextString(p);
        s.width = ExtraNextPrimitive<int32_t>(p);
        s.height = ExtraNextPrimitive<int32_t>(p);
        s.x = ExtraNextPrimitive<float>(p);
        s.y = ExtraNextPrimitive<float>(p);
        s.flag = ExtraNextPrimitive<bool>(p);
        s.age = ExtraNextPrimitive<int16_t>(p);
        std::memcpy(&s.ordinalEnum, p, sizeof(VkTestEnumOrdinal)); p += sizeof(VkTestEnumOrdinal);
        std::memcpy(&s.rawEnum, p, sizeof(VkTestEnumRaw)); p += sizeof(VkTestEnumRaw);
        std::memcpy(s.fixedStringUtf8, p, 12 * sizeof(char)); p += 12 * sizeof(char);
        s.stringUtf8 = ExtraNextString(p);
        std::memcpy(s.fixedStringUtf16, p, 18 * sizeof(uint16_t)); p += 18 * sizeof(uint16_t);
        s.stringUtf16 = ExtraNextString16(p);
        std::memcpy(s.fixedBytes, p, 24 * sizeof(uint8_t)); p += 24 * sizeof(uint8_t);
        s.bytes = ExtraNextArray<uint8_t>(p);
        std::memcpy(s.fixedShorts, p, 48 * sizeof(int16_t)); p += 48 * sizeof(int16_t);
        s.shorts = ExtraNextArray<int16_t>(p);
        std::memcpy(s.fixedInts, p, 64 * sizeof(int32_t)); p += 64 * sizeof(int32_t);
        s.ints = ExtraNextArray<int32_t>(p);
        std::memcpy(s.fixedLongs, p, 36 * sizeof(int64_t)); p += 36 * sizeof(int64_t);
        s.longs = ExtraNextArray<int64_t>(p);
        std::memcpy(s.fixedFloats, p, 36 * sizeof(float)); p += 36 * sizeof(float);
        s.floats = ExtraNextArray<float>(p);
        std::memcpy(s.fixedDoubles, p, 36 * sizeof(double)); p += 36 * sizeof(double);
        s.doubles = ExtraNextArray<double>(p);
        std::memcpy(&s.nestedDataBuffer, p, sizeof(VkNativeBuffer)); p += sizeof(VkNativeBuffer);
        s.data = ExtraNextList<VkNestedData>(p, [](const uint8_t*& p) { { auto tmp = VkNestedData::Decode(p); p += VkNestedData::SizeOf(tmp); }; });
        return s;
    }

    static inline void Encode(const VkTestData& s, uint8_t* bytes)
    {
        uint8_t* p = bytes;
        ExtraPushPrimitive<int64_t>(s.id, p);
        ExtraPushPrimitive<int64_t>(s.timestamp, p);
        ExtraPushString(s.name, p);
        ExtraPushPrimitive<int32_t>(s.width, p);
        ExtraPushPrimitive<int32_t>(s.height, p);
        ExtraPushPrimitive<float>(s.x, p);
        ExtraPushPrimitive<float>(s.y, p);
        ExtraPushPrimitive<bool>(s.flag, p);
        ExtraPushPrimitive<int16_t>(s.age, p);
        std::memcpy(p, &s.ordinalEnum, sizeof(VkTestEnumOrdinal)); p += sizeof(VkTestEnumOrdinal);
        std::memcpy(p, &s.rawEnum, sizeof(VkTestEnumRaw)); p += sizeof(VkTestEnumRaw);
        std::memcpy(p, s.fixedStringUtf8, 12 * sizeof(char)); p += 12 * sizeof(char);
        ExtraPushString(s.stringUtf8, p);
        std::memcpy(p, s.fixedStringUtf16, 18 * sizeof(uint16_t)); p += 18 * sizeof(uint16_t);
        ExtraPushString16(s.stringUtf16, p);
        std::memcpy(p, s.fixedBytes, 24 * sizeof(uint8_t)); p += 24 * sizeof(uint8_t);
        ExtraPushArray<uint8_t>(s.bytes, p);
        std::memcpy(p, s.fixedShorts, 48 * sizeof(int16_t)); p += 48 * sizeof(int16_t);
        ExtraPushArray<int16_t>(s.shorts, p);
        std::memcpy(p, s.fixedInts, 64 * sizeof(int32_t)); p += 64 * sizeof(int32_t);
        ExtraPushArray<int32_t>(s.ints, p);
        std::memcpy(p, s.fixedLongs, 36 * sizeof(int64_t)); p += 36 * sizeof(int64_t);
        ExtraPushArray<int64_t>(s.longs, p);
        std::memcpy(p, s.fixedFloats, 36 * sizeof(float)); p += 36 * sizeof(float);
        ExtraPushArray<float>(s.floats, p);
        std::memcpy(p, s.fixedDoubles, 36 * sizeof(double)); p += 36 * sizeof(double);
        ExtraPushArray<double>(s.doubles, p);
        std::memcpy(p, &s.nestedDataBuffer, sizeof(VkNativeBuffer)); p += sizeof(VkNativeBuffer);
        ExtraPushList<VkNestedData>(s.data, p, [](const uint8_t*& r, uint8_t*& p) { { auto tmp = VkNestedData::Decode(r); VkNestedData::Encode(tmp, p); p += VkNestedData::SizeOf(tmp); }; });
    }
};

EXTRA_STRUCT VkMovement
{
    float speed;

    static inline int32_t SizeOf(const VkMovement& s)
    {
        return static_cast<int32_t>(sizeof(VkMovement));
    }

    static inline VkMovement Decode(const uint8_t* bytes)
    {
        VkMovement s;
        std::memcpy(&s, bytes, sizeof(VkMovement));
        return s;
    }

    static inline void Encode(const VkMovement& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkMovement));
    }
};

EXTRA_STRUCT VkCamera
{
    float fov;

    static inline int32_t SizeOf(const VkCamera& s)
    {
        return static_cast<int32_t>(sizeof(VkCamera));
    }

    static inline VkCamera Decode(const uint8_t* bytes)
    {
        VkCamera s;
        std::memcpy(&s, bytes, sizeof(VkCamera));
        return s;
    }

    static inline void Encode(const VkCamera& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkCamera));
    }
};

EXTRA_STRUCT VkVelocity
{
    float x;
    float y;
    float z;

    static inline int32_t SizeOf(const VkVelocity& s)
    {
        return static_cast<int32_t>(sizeof(VkVelocity));
    }

    static inline VkVelocity Decode(const uint8_t* bytes)
    {
        VkVelocity s;
        std::memcpy(&s, bytes, sizeof(VkVelocity));
        return s;
    }

    static inline void Encode(const VkVelocity& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkVelocity));
    }
};

EXTRA_STRUCT VkRenderable
{
    int32_t textureId;

    static inline int32_t SizeOf(const VkRenderable& s)
    {
        return static_cast<int32_t>(sizeof(VkRenderable));
    }

    static inline VkRenderable Decode(const uint8_t* bytes)
    {
        VkRenderable s;
        std::memcpy(&s, bytes, sizeof(VkRenderable));
        return s;
    }

    static inline void Encode(const VkRenderable& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkRenderable));
    }
};

EXTRA_STRUCT VkHealth
{
    float current;
    float maximum;

    static inline int32_t SizeOf(const VkHealth& s)
    {
        return static_cast<int32_t>(sizeof(VkHealth));
    }

    static inline VkHealth Decode(const uint8_t* bytes)
    {
        VkHealth s;
        std::memcpy(&s, bytes, sizeof(VkHealth));
        return s;
    }

    static inline void Encode(const VkHealth& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkHealth));
    }
};

EXTRA_STRUCT VkDamage
{
    float amount;
    float armorPenetration;

    static inline int32_t SizeOf(const VkDamage& s)
    {
        return static_cast<int32_t>(sizeof(VkDamage));
    }

    static inline VkDamage Decode(const uint8_t* bytes)
    {
        VkDamage s;
        std::memcpy(&s, bytes, sizeof(VkDamage));
        return s;
    }

    static inline void Encode(const VkDamage& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkDamage));
    }
};

EXTRA_STRUCT VkCollision
{
    float impulse;
    float damageScale;

    static inline int32_t SizeOf(const VkCollision& s)
    {
        return static_cast<int32_t>(sizeof(VkCollision));
    }

    static inline VkCollision Decode(const uint8_t* bytes)
    {
        VkCollision s;
        std::memcpy(&s, bytes, sizeof(VkCollision));
        return s;
    }

    static inline void Encode(const VkCollision& s, uint8_t* bytes)
    {
        std::memcpy(bytes, &s, sizeof(VkCollision));
    }
};

