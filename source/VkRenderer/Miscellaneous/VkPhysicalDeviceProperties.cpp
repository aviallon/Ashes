#include "VkRendererPrerequisites.hpp"

namespace vk_renderer
{
	ashes::PhysicalDeviceProperties convert( VkPhysicalDeviceProperties const & value )
	{
		ashes::PhysicalDeviceProperties result;
		result.apiVersion = value.apiVersion;
		result.deviceID = value.deviceID;
		result.deviceName = value.deviceName;
		std::memcpy( result.pipelineCacheUUID, value.pipelineCacheUUID, sizeof( value.pipelineCacheUUID ) );
		result.vendorID = value.vendorID;
		result.deviceType = convertPhysicalDeviceType( value.deviceType );
		result.driverVersion = value.driverVersion;

		result.limits.maxImageDimension1D = value.limits.maxImageDimension1D;
		result.limits.maxImageDimension2D = value.limits.maxImageDimension2D;
		result.limits.maxImageDimension3D = value.limits.maxImageDimension3D;
		result.limits.maxImageDimensionCube = value.limits.maxImageDimensionCube;
		result.limits.maxImageArrayLayers = value.limits.maxImageArrayLayers;
		result.limits.maxTexelBufferElements = value.limits.maxTexelBufferElements;
		result.limits.maxUniformBufferRange = value.limits.maxUniformBufferRange;
		result.limits.maxStorageBufferRange = value.limits.maxStorageBufferRange;
		result.limits.maxPushConstantsSize = value.limits.maxPushConstantsSize;
		result.limits.maxMemoryAllocationCount = value.limits.maxMemoryAllocationCount;
		result.limits.maxSamplerAllocationCount = value.limits.maxSamplerAllocationCount;
		result.limits.bufferImageGranularity = value.limits.bufferImageGranularity;
		result.limits.sparseAddressSpaceSize = value.limits.sparseAddressSpaceSize;
		result.limits.maxBoundDescriptorSets = value.limits.maxBoundDescriptorSets;
		result.limits.maxPerStageDescriptorSamplers = value.limits.maxPerStageDescriptorSamplers;
		result.limits.maxPerStageDescriptorUniformBuffers = value.limits.maxPerStageDescriptorUniformBuffers;
		result.limits.maxPerStageDescriptorStorageBuffers = value.limits.maxPerStageDescriptorStorageBuffers;
		result.limits.maxPerStageDescriptorSampledImages = value.limits.maxPerStageDescriptorSampledImages;
		result.limits.maxPerStageDescriptorStorageImages = value.limits.maxPerStageDescriptorStorageImages;
		result.limits.maxPerStageDescriptorInputAttachments = value.limits.maxPerStageDescriptorInputAttachments;
		result.limits.maxPerStageResources = value.limits.maxPerStageResources;
		result.limits.maxDescriptorSetSamplers = value.limits.maxDescriptorSetSamplers;
		result.limits.maxDescriptorSetUniformBuffers = value.limits.maxDescriptorSetUniformBuffers;
		result.limits.maxDescriptorSetUniformBuffersDynamic = value.limits.maxDescriptorSetUniformBuffersDynamic;
		result.limits.maxDescriptorSetStorageBuffers = value.limits.maxDescriptorSetStorageBuffers;
		result.limits.maxDescriptorSetStorageBuffersDynamic = value.limits.maxDescriptorSetStorageBuffersDynamic;
		result.limits.maxDescriptorSetSampledImages = value.limits.maxDescriptorSetSampledImages;
		result.limits.maxDescriptorSetStorageImages = value.limits.maxDescriptorSetStorageImages;
		result.limits.maxDescriptorSetInputAttachments = value.limits.maxDescriptorSetInputAttachments;
		result.limits.maxVertexInputAttributes = value.limits.maxVertexInputAttributes;
		result.limits.maxVertexInputBindings = value.limits.maxVertexInputBindings;
		result.limits.maxVertexInputAttributeOffset = value.limits.maxVertexInputAttributeOffset;
		result.limits.maxVertexInputBindingStride = value.limits.maxVertexInputBindingStride;
		result.limits.maxVertexOutputComponents = value.limits.maxVertexOutputComponents;
		result.limits.maxTessellationGenerationLevel = value.limits.maxTessellationGenerationLevel;
		result.limits.maxTessellationPatchSize = value.limits.maxTessellationPatchSize;
		result.limits.maxTessellationControlPerVertexInputComponents = value.limits.maxTessellationControlPerVertexInputComponents;
		result.limits.maxTessellationControlPerVertexOutputComponents = value.limits.maxTessellationControlPerVertexOutputComponents;
		result.limits.maxTessellationControlPerPatchOutputComponents = value.limits.maxTessellationControlPerPatchOutputComponents;
		result.limits.maxTessellationControlTotalOutputComponents = value.limits.maxTessellationControlTotalOutputComponents;
		result.limits.maxTessellationEvaluationInputComponents = value.limits.maxTessellationEvaluationInputComponents;
		result.limits.maxTessellationEvaluationOutputComponents = value.limits.maxTessellationEvaluationOutputComponents;
		result.limits.maxGeometryShaderInvocations = value.limits.maxGeometryShaderInvocations;
		result.limits.maxGeometryInputComponents = value.limits.maxGeometryInputComponents;
		result.limits.maxGeometryOutputComponents = value.limits.maxGeometryOutputComponents;
		result.limits.maxGeometryOutputVertices = value.limits.maxGeometryOutputVertices;
		result.limits.maxGeometryTotalOutputComponents = value.limits.maxGeometryTotalOutputComponents;
		result.limits.maxFragmentInputComponents = value.limits.maxFragmentInputComponents;
		result.limits.maxFragmentOutputAttachments = value.limits.maxFragmentOutputAttachments;
		result.limits.maxFragmentDualSrcAttachments = value.limits.maxFragmentDualSrcAttachments;
		result.limits.maxFragmentCombinedOutputResources = value.limits.maxFragmentCombinedOutputResources;
		result.limits.maxComputeSharedMemorySize = value.limits.maxComputeSharedMemorySize;
		result.limits.maxComputeWorkGroupCount[0] = value.limits.maxComputeWorkGroupCount[0];
		result.limits.maxComputeWorkGroupCount[1] = value.limits.maxComputeWorkGroupCount[1];
		result.limits.maxComputeWorkGroupCount[2] = value.limits.maxComputeWorkGroupCount[2];
		result.limits.maxComputeWorkGroupInvocations = value.limits.maxComputeWorkGroupInvocations;
		result.limits.maxComputeWorkGroupSize[0] = value.limits.maxComputeWorkGroupSize[0];
		result.limits.maxComputeWorkGroupSize[1] = value.limits.maxComputeWorkGroupSize[1];
		result.limits.maxComputeWorkGroupSize[2] = value.limits.maxComputeWorkGroupSize[2];
		result.limits.subPixelPrecisionBits = value.limits.subPixelPrecisionBits;
		result.limits.subTexelPrecisionBits = value.limits.subTexelPrecisionBits;
		result.limits.mipmapPrecisionBits = value.limits.mipmapPrecisionBits;
		result.limits.maxDrawIndexedIndexValue = value.limits.maxDrawIndexedIndexValue;
		result.limits.maxDrawIndirectCount = value.limits.maxDrawIndirectCount;
		result.limits.maxSamplerLodBias = value.limits.maxSamplerLodBias;
		result.limits.maxSamplerAnisotropy = value.limits.maxSamplerAnisotropy;
		result.limits.maxViewports = value.limits.maxViewports;
		result.limits.maxViewportDimensions[0] = value.limits.maxViewportDimensions[0];
		result.limits.maxViewportDimensions[1] = value.limits.maxViewportDimensions[1];
		result.limits.viewportBoundsRange[0] = value.limits.viewportBoundsRange[0];
		result.limits.viewportBoundsRange[1] = value.limits.viewportBoundsRange[1];
		result.limits.viewportSubPixelBits = value.limits.viewportSubPixelBits;
		result.limits.minMemoryMapAlignment = value.limits.minMemoryMapAlignment;
		result.limits.minTexelBufferOffsetAlignment = value.limits.minTexelBufferOffsetAlignment;
		result.limits.minUniformBufferOffsetAlignment = value.limits.minUniformBufferOffsetAlignment;
		result.limits.minStorageBufferOffsetAlignment = value.limits.minStorageBufferOffsetAlignment;
		result.limits.minTexelOffset = value.limits.minTexelOffset;
		result.limits.maxTexelOffset = value.limits.maxTexelOffset;
		result.limits.minTexelGatherOffset = value.limits.minTexelGatherOffset;
		result.limits.maxTexelGatherOffset = value.limits.maxTexelGatherOffset;
		result.limits.minInterpolationOffset = value.limits.minInterpolationOffset;
		result.limits.maxInterpolationOffset = value.limits.maxInterpolationOffset;
		result.limits.subPixelInterpolationOffsetBits = value.limits.subPixelInterpolationOffsetBits;
		result.limits.maxFramebufferWidth = value.limits.maxFramebufferWidth;
		result.limits.maxFramebufferHeight = value.limits.maxFramebufferHeight;
		result.limits.maxFramebufferLayers = value.limits.maxFramebufferLayers;
		result.limits.framebufferColorSampleCounts = value.limits.framebufferColorSampleCounts;
		result.limits.framebufferDepthSampleCounts = value.limits.framebufferDepthSampleCounts;
		result.limits.framebufferStencilSampleCounts = value.limits.framebufferStencilSampleCounts;
		result.limits.framebufferNoAttachmentsSampleCounts = value.limits.framebufferNoAttachmentsSampleCounts;
		result.limits.maxColorAttachments = value.limits.maxColorAttachments;
		result.limits.sampledImageColorSampleCounts = value.limits.sampledImageColorSampleCounts;
		result.limits.sampledImageIntegerSampleCounts = value.limits.sampledImageIntegerSampleCounts;
		result.limits.sampledImageDepthSampleCounts = value.limits.sampledImageDepthSampleCounts;
		result.limits.sampledImageStencilSampleCounts = value.limits.sampledImageStencilSampleCounts;
		result.limits.storageImageSampleCounts = value.limits.storageImageSampleCounts;
		result.limits.maxSampleMaskWords = value.limits.maxSampleMaskWords;
		result.limits.timestampComputeAndGraphics = value.limits.timestampComputeAndGraphics;
		result.limits.timestampPeriod = value.limits.timestampPeriod;
		result.limits.maxClipDistances = value.limits.maxClipDistances;
		result.limits.maxCullDistances = value.limits.maxCullDistances;
		result.limits.maxCombinedClipAndCullDistances = value.limits.maxCombinedClipAndCullDistances;
		result.limits.discreteQueuePriorities = value.limits.discreteQueuePriorities;
		result.limits.pointSizeRange[0] = value.limits.pointSizeRange[0];
		result.limits.pointSizeRange[1] = value.limits.pointSizeRange[1];
		result.limits.lineWidthRange[0] = value.limits.lineWidthRange[0];
		result.limits.lineWidthRange[1] = value.limits.lineWidthRange[1];
		result.limits.pointSizeGranularity = value.limits.pointSizeGranularity;
		result.limits.lineWidthGranularity = value.limits.lineWidthGranularity;
		result.limits.strictLines = value.limits.strictLines;
		result.limits.standardSampleLocations = value.limits.standardSampleLocations;
		result.limits.optimalBufferCopyOffsetAlignment = value.limits.optimalBufferCopyOffsetAlignment;
		result.limits.optimalBufferCopyRowPitchAlignment = value.limits.optimalBufferCopyRowPitchAlignment;
		result.limits.nonCoherentAtomSize = value.limits.nonCoherentAtomSize;

		result.sparseProperties.residencyAlignedMipSize = value.sparseProperties.residencyAlignedMipSize;
		result.sparseProperties.residencyNonResidentStrict = value.sparseProperties.residencyNonResidentStrict;
		result.sparseProperties.residencyStandard2DBlockShape = value.sparseProperties.residencyStandard2DBlockShape;
		result.sparseProperties.residencyStandard2DMultisampleBlockShape = value.sparseProperties.residencyStandard2DMultisampleBlockShape;
		result.sparseProperties.residencyStandard3DBlockShape = value.sparseProperties.residencyStandard3DBlockShape;

		return result;
	}
}