package com.cws.extra.test

import com.cws.extra.math.vectors.Float4
import com.cws.extra.memory.ExtraBridgeData
import com.cws.extra.memory.ExtraEnum

private val DEFAULT_CLEAR_COLOR = Float4(0f, 0f, 0f, 1f)

@ExtraBridgeData
data class RenderContextInfo(
    var applicationName: String = "",
    val engineName: String = "",
    val swapchainName: String = "${applicationName}Swapchain",
    var x: Int = 0,
    var y: Int = 0,
    var width: Int = 800,
    var height: Int = 600,
    val frameCount: Int = 1,
    var isDebug: Boolean = false,
    var surface: SurfaceHandle? = null,
    val clearColor: Float4 = DEFAULT_CLEAR_COLOR,
    val enableDepth: Boolean = false,
    val enableStencil: Boolean = false,
    val frameBudgetBytes: Int = 5_000_000, // 5 MB
)

@ExtraBridgeData
data class SwapchainInfo(
    val name: String,
    val colorAttachment: ColorAttachment,
    val depthTextureInfo: TextureInfo?,
)

@ExtraBridgeData
data class BufferInfo(
    val name: String = "",
    val slot: Int = 0,
    val memoryType: MemoryType = MemoryType.HOST,
    val usages: Int = 0,
    val size: Long = 0,
    val isStatic: Boolean = false,
)

@ExtraBridgeData
data class VertexBufferInfo(
    val name: String,
    val attributes: List<Attribute>,
    val vertexCount: Int,
    val slot: Int = 0,
)

@ExtraBridgeData
data class IndexBufferInfo(
    val name: String,
    val indexCount: Int,
    val indexSize: IndexSize = IndexSize.UNSIGNED_16,
)

@ExtraBridgeData
data class SamplerInfo(
    val name: String = "",
    val magFilter: SamplerFilter = SamplerFilter.LINEAR,
    val minFilter: SamplerFilter = SamplerFilter.LINEAR,
    val addressModeU: SamplerMode = SamplerMode.CLAMP_TO_EDGE,
    val addressModeV: SamplerMode = SamplerMode.CLAMP_TO_EDGE,
    val addressModeW: SamplerMode = SamplerMode.CLAMP_TO_EDGE,
    val mipmapMode: SamplerMipMapMode = SamplerMipMapMode.NONE,
    val enableAnisotropy: Boolean = true,
    val maxAnisotropy: Float = 1f,
    val unnormalizedCoordinates: Boolean = false,
    val enableCompare: Boolean = false,
    val compareOp: CompareOp = CompareOp.ALWAYS,
    val borderColor: BorderColor = BorderColor.FLOAT_OPAQUE_BLACK,
    val mipLodBias: Float = 0f,
    val minLod: Float = 0f,
    val maxLod: Float = 32f,
)

@ExtraBridgeData
data class TextureInfo(
    var name: String = "",
    val type: TextureType = TextureType.TEXTURE2D,
    val memoryType: MemoryType = MemoryType.HOST,
    val usages: Int = TextureUsage.TEXTURE_BINDING.rawValue,
    var width: Int = 0,
    var height: Int = 0,
    var depth: Int = 1,
    var format: TextureFormat = TextureFormat.FORMAT_RGBA8,
    val mips: Int = 1,
    val baseMip: Int = 0,
    val samples: Int = 1,
    val isStatic: Boolean = true,
)

@ExtraBridgeData
data class BlendState(
    val enable: Boolean = false,
    val srcFactorColor: BlendFactor = BlendFactor.ONE,
    val dstFactorColor: BlendFactor = BlendFactor.ZERO,
    val blendOpColor: BlendOp = BlendOp.ADD,
    val srcFactorAlpha: BlendFactor = BlendFactor.ONE,
    val dstFactorAlpha: BlendFactor = BlendFactor.ZERO,
    val blendOpAlpha: BlendOp = BlendOp.ADD,
)

@ExtraBridgeData
data class Attribute(
    val location: Int = 0,
    val type: AttributeType = AttributeType.ATTRIBUTE_TYPE_VEC3,
    val format: AttributeFormat = AttributeFormat.FLOAT,
)

val Attribute.sizeInBytes: Int get() = type.rawValue * Float.SIZE_BYTES

val List<Attribute>.sizeInBytes: Int get() = sumOf { it.sizeInBytes }

@ExtraBridgeData
data class Binding(
    val type: BindingType = BindingType.UNIFORM_BUFFER,
    val shaderStages: Int = 0,
    val set: Int = 0,
    val binding: Int = 0,
    val count: Int = 1,
) {
    var resource: ResourceId? = null

    constructor(
        type: BindingType = BindingType.UNIFORM_BUFFER,
        shaderStages: Int = 0,
        set: Int = 0,
        binding: Int = 0,
        count: Int = 1,
        resource: ResourceId? = null,
    ) : this(type, shaderStages, set, binding, count) {
        this.resource = resource
    }
}

@ExtraBridgeData
data class BindingInfo(
    val name: String = "",
    val bindings: List<Binding> = emptyList(),
)

@ExtraEnum
enum class SpirvTarget {
    OPENGL,
    VULKAN
}

@ExtraBridgeData
data class ShaderInfo(
    val name: String = "",
    val entryPoint: String = "main",
    val stage: ShaderStage = ShaderStage.VERTEX,
    val spirvTarget: SpirvTarget = SpirvTarget.VULKAN,
    val spirvCode: ByteArray = ByteArray(0),
    val textCode: String = "",
)

@ExtraBridgeData
data class StencilState(
    var enabled: Boolean = false,
    var compareOp: CompareOp = CompareOp.ALWAYS,
    var reference: Int = 0,
    var compareMask: Int = 0xFF,
    var writeMask: Int = 0xFF,
    var stencilFailOp: StencilOp = StencilOp.KEEP,
    var depthFailOp: StencilOp = StencilOp.KEEP,
    var passOp: StencilOp = StencilOp.KEEP,
) {
    var readOnly: Boolean = false
        set(value) {
            field = value
            writeMask = if (value) 0 else 0xFF
        }
}

@ExtraBridgeData
data class RenderPipelineInfo(
    val name: String = "",
    val instanced: Boolean = false,
    val primitiveTopology: PrimitiveTopology = PrimitiveTopology.TRIANGLE_LIST,
    val vertexBuffer: BufferHandle? = null,
    val indexBuffer: BufferHandle? = null,
    var vertexShader: ShaderHandle? = null,
    var fragmentShader: ShaderHandle? = null,
    val geometryShader: ShaderHandle? = null,
    val bindingLayouts: List<BindingLayoutHandle> = emptyList(),
    var viewportX: Float = 0f,
    var viewportY: Float = 0f,
    var viewportWidth: Float = 0f,
    var viewportHeight: Float = 0f,
    var viewportMinDepth: Float = 0f,
    var viewportMaxDepth: Float = 1f,
    var scissorX: Int = 0,
    var scissorY: Int = 0,
    var scissorWidth: Int = 0,
    var scissorHeight: Int = 0,
    val polygonMode: PolygonMode = PolygonMode.FILL,
    val lineWidth: Float = 1f,
    val cullMode: CullMode = CullMode.NONE,
    val frontFace: FrontFace = FrontFace.CLOCKWISE,
    val sampleCount: Int = 1,
    val renderTarget: RenderTargetHandle? = null,
    val stencilState: StencilState = StencilState(),
)

@ExtraBridgeData
data class ComputePipelineInfo(
    val name: String = "",
    var computeShader: ShaderHandle? = null,
    val bindingLayouts: List<BindingLayoutHandle> = emptyList(),
)

@ExtraBridgeData
data class ColorAttachment(
    val texture: TextureHandle? = null,
    val clearColor: Float4 = DEFAULT_CLEAR_COLOR,
    val blendState: BlendState = BlendState(),
)

@ExtraBridgeData
data class DepthAttachment(
    val texture: TextureHandle? = null,
    val enabled: Boolean = false,
    val depthClearValue: Float = 1f,
    val depthCompareOp: CompareOp = CompareOp.LESS,
    val depthReadOnly: Boolean = false,
    val depthWriteEnabled: Boolean = true,
)

@ExtraBridgeData
data class StencilAttachment(
    val texture: TextureHandle? = null,
    val enabled: Boolean = false,
    val stencilClearValue: Int = 0,
)

@ExtraBridgeData
data class RenderTargetInfo(
    val name: String = "",
    val isSwapchain: Boolean = false,
    var x: Int = 0,
    var y: Int = 0,
    var width: Int = 0,
    var height: Int = 0,
    var depth: Int = 0,
    val colorAttachments: List<ColorAttachment> = emptyList(),
    val depthAttachment: DepthAttachment = DepthAttachment(),
    val stencilAttachment: StencilAttachment = StencilAttachment(),
)