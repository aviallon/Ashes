/*
This file belongs to Renderer.
See LICENSE file in root folder.
*/
#include "Core/VkDevice.hpp"

#include "Buffer/VkBuffer.hpp"
#include "Buffer/VkBufferView.hpp"
#include "Buffer/VkGeometryBuffers.hpp"
#include "Buffer/VkUniformBuffer.hpp"
#include "Command/VkCommandPool.hpp"
#include "Command/VkQueue.hpp"
#include "Core/VkConnection.hpp"
#include "Core/VkRenderer.hpp"
#include "Core/VkSwapChain.hpp"
#include "Descriptor/VkDescriptorSetBinding.hpp"
#include "Descriptor/VkDescriptorSetLayout.hpp"
#include "Image/VkSampler.hpp"
#include "Image/VkTexture.hpp"
#include "Image/VkTextureView.hpp"
#include "Miscellaneous/VkQueryPool.hpp"
#include "Pipeline/VkPipeline.hpp"
#include "Pipeline/VkPipelineLayout.hpp"
#include "Pipeline/VkVertexLayout.hpp"
#include "RenderPass/VkRenderBuffer.hpp"
#include "RenderPass/VkRenderPass.hpp"
#include "RenderPass/VkRenderSubpass.hpp"
#include "Shader/VkShaderProgram.hpp"
#include "Sync/VkSemaphore.hpp"

namespace vk_renderer
{
	Device::Device( Renderer const & renderer
		, renderer::ConnectionPtr && connection )
		: renderer::Device{ renderer, *connection }
		, m_renderer{ renderer }
		, m_connection{ static_cast< Connection * >( connection.release() ) }
		, m_gpu{ m_connection->getGpu() }
		, m_version{ "Vulkan 1.0.0" }
	{
		std::vector< VkDeviceQueueCreateInfo > queueCreateInfos;
		std::vector< float > queuePriorities = { 1.0f };

		queueCreateInfos.push_back(
		{
			VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,                 // sType
			nullptr,                                                    // pNext
			0,                                                          // flags
			m_connection->getGraphicsQueueFamilyIndex(),                 // queueFamilyIndex
			static_cast< uint32_t >( queuePriorities.size() ),          // queueCount
			queuePriorities.data()                                      // pQueuePriorities
		} );

		if ( m_connection->getPresentQueueFamilyIndex() != m_connection->getGraphicsQueueFamilyIndex() )
		{
			queueCreateInfos.push_back(
			{
				VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,             // sType
				nullptr,                                                // pNext
				0,                                                      // flags
				m_connection->getPresentQueueFamilyIndex(),              // queueFamilyIndex
				static_cast< uint32_t >( queuePriorities.size() ),      // queueCount
				queuePriorities.data()                                  // pQueuePriorities
			} );
		}

		VkDeviceCreateInfo deviceInfo
		{
			VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
			nullptr,
			0,                                                                               // flags
			static_cast< uint32_t >( queueCreateInfos.size() ),                              // queueCreateInfoCount
			queueCreateInfos.data(),                                                         // pQueueCreateInfos
			static_cast< uint32_t >( m_gpu.getLayerNames().size() ),                         // enabledLayerCount
			m_gpu.getLayerNames().empty() ? nullptr : m_gpu.getLayerNames().data(),          // ppEnabledLayerNames
			static_cast< uint32_t >( m_gpu.getExtensionNames().size() ),                     // enabledExtensionCount
			m_gpu.getExtensionNames().empty() ? nullptr : m_gpu.getExtensionNames().data(),  // ppEnabledExtensionNames
			nullptr                                                                          // pEnabledFeatures
		};
		DEBUG_DUMP( deviceInfo );

		auto res = vk::CreateDevice( m_gpu, &deviceInfo, nullptr, &m_device );

		if ( !checkError( res ) )
		{
			throw std::runtime_error{ "LogicalDevice creation failed: " + getLastError() };
		}
		
		m_presentQueue = std::make_unique< Queue >( *this, m_connection->getPresentQueueFamilyIndex() );
		m_presentCommandPool = std::make_unique< CommandPool >( *this
			, m_presentQueue->getFamilyIndex()
			, renderer::CommandPoolCreateFlag::eResetCommandBuffer | renderer::CommandPoolCreateFlag::eTransient );

		if ( m_connection->getGraphicsQueueFamilyIndex() != m_connection->getPresentQueueFamilyIndex() )
		{
			m_graphicsQueue = std::make_unique< Queue >( *this, m_connection->getGraphicsQueueFamilyIndex() );
		}
		else
		{
			m_graphicsQueue = std::make_unique< Queue >( *this, m_connection->getPresentQueueFamilyIndex() );
		}

		m_graphicsCommandPool = std::make_unique< CommandPool >( *this
			, m_graphicsQueue->getFamilyIndex()
			, renderer::CommandPoolCreateFlag::eResetCommandBuffer | renderer::CommandPoolCreateFlag::eTransient );
	}

	Device::~Device()
	{
		m_graphicsCommandPool.reset();
		m_graphicsQueue.reset();
		m_presentCommandPool.reset();
		m_presentQueue.reset();
		vk::DestroyDevice( m_device, nullptr );
	}

	renderer::RenderPassPtr Device::createRenderPass( std::vector< renderer::PixelFormat > const & formats
		, renderer::RenderSubpassPtrArray const & subpasses
		, renderer::RenderPassState const & initialState
		, renderer::RenderPassState const & finalState
		, bool clear
		, renderer::SampleCountFlag samplesCount )const
	{
		return std::make_unique< RenderPass >( *this
			, formats
			, subpasses
			, initialState
			, finalState
			, clear
			, samplesCount );
	}

	renderer::RenderSubpassPtr Device::createRenderSubpass( std::vector< renderer::PixelFormat > const & formats
		, renderer::RenderSubpassState const & neededState )const
	{
		return std::make_unique< RenderSubpass >( *this
			, formats
			, neededState );
	}

	renderer::VertexLayoutPtr Device::createVertexLayout( uint32_t bindingSlot
		, uint32_t stride )const
	{
		return std::make_unique< VertexLayout >( bindingSlot
			, stride );
	}

	renderer::GeometryBuffersPtr Device::createGeometryBuffers( renderer::VertexBufferBase const & vbo
		, uint64_t vboOffset
		, renderer::VertexLayout const & layout )const
	{
		return std::make_unique< GeometryBuffers >( vbo
			, vboOffset
			, layout );
	}

	renderer::GeometryBuffersPtr Device::createGeometryBuffers( renderer::VertexBufferBase const & vbo
		, uint64_t vboOffset
		, renderer::VertexLayout const & layout
		, renderer::BufferBase const & ibo
		, uint64_t iboOffset
		, renderer::IndexType type )const
	{
		return std::make_unique< GeometryBuffers >( vbo
			, vboOffset
			, layout
			, ibo
			, iboOffset
			, type );
	}

	renderer::GeometryBuffersPtr Device::createGeometryBuffers( renderer::VertexBufferCRefArray const & vbos
		, std::vector< uint64_t > vboOffsets
		, renderer::VertexLayoutCRefArray const & layouts )const
	{
		return std::make_unique< GeometryBuffers >( vbos
			, vboOffsets
			, layouts );
	}

	renderer::GeometryBuffersPtr Device::createGeometryBuffers( renderer::VertexBufferCRefArray const & vbos
		, std::vector< uint64_t > vboOffsets
		, renderer::VertexLayoutCRefArray const & layouts
		, renderer::BufferBase const & ibo
		, uint64_t iboOffset
		, renderer::IndexType type )const
	{
		return std::make_unique< GeometryBuffers >( vbos
			, vboOffsets
			, layouts
			, ibo
			, iboOffset
			, type );
	}

	renderer::PipelineLayoutPtr Device::createPipelineLayout()const
	{
		return std::make_unique< PipelineLayout >( *this
			, nullptr );
	}

	renderer::PipelineLayoutPtr Device::createPipelineLayout( renderer::DescriptorSetLayout const & layout )const
	{
		return std::make_unique< PipelineLayout >( *this
			, &layout );
	}

	renderer::PipelinePtr Device::createPipeline( renderer::PipelineLayout const & layout
		, renderer::ShaderProgram const & program
		, renderer::VertexLayoutCRefArray const & vertexLayouts
		, renderer::RenderPass const & renderPass
		, renderer::PrimitiveTopology topology
		, renderer::RasterisationState const & rasterisationState
		, renderer::ColourBlendState const & colourBlendState )const
	{
		return std::make_shared< Pipeline >( *this
			, layout
			, program
			, vertexLayouts
			, renderPass
			, topology
			, rasterisationState
			, colourBlendState );
	}

	renderer::DescriptorSetLayoutPtr Device::createDescriptorSetLayout( renderer::DescriptorSetLayoutBindingArray && bindings )const
	{
		return std::make_unique< DescriptorSetLayout >( *this, std::move( bindings ) );
	}

	renderer::TexturePtr Device::createTexture( renderer::ImageLayout initialLayout )const
	{
		return std::make_shared< Texture >( *this, initialLayout );
	}

	renderer::RenderBufferPtr Device::createRenderBuffer( renderer::PixelFormat format
		, renderer::UIVec2 const & size )
	{
		return std::make_unique< RenderBuffer >( *this, format, size );
	}

	renderer::TextureViewPtr Device::createTextureView( renderer::Texture const & texture
		, renderer::PixelFormat format
		, uint32_t baseMipLevel
		, uint32_t levelCount
		, uint32_t baseArrayLayer
		, uint32_t layerCount )const
	{
		return std::make_shared< TextureView >( *this
			, static_cast< Texture const & >( texture )
			, format
			, baseMipLevel
			, levelCount
			, baseArrayLayer
			, layerCount );
	}

	renderer::SamplerPtr Device::createSampler( renderer::WrapMode wrapS
		, renderer::WrapMode wrapT
		, renderer::WrapMode wrapR
		, renderer::Filter minFilter
		, renderer::Filter magFilter
		, renderer::MipmapMode mipFilter
		, float minLod
		, float maxLod
		, float lodBias
		, renderer::BorderColour borderColour
		, float maxAnisotropy
		, renderer::CompareOp compareOp )const
	{
		return std::make_unique< Sampler >( *this
			, wrapS
			, wrapT
			, wrapR
			, minFilter
			, magFilter
			, mipFilter
			, minLod
			, maxLod
			, lodBias
			, borderColour
			, maxAnisotropy
			, compareOp );
	}

	renderer::BufferBasePtr Device::createBuffer( uint32_t size
		, renderer::BufferTargets target
		, renderer::MemoryPropertyFlags memoryFlags )const
	{
		return std::make_unique< Buffer >( *this
			, size
			, target
			, memoryFlags );
	}

	renderer::BufferViewPtr Device::createBufferView( renderer::BufferBase const & buffer
		, renderer::PixelFormat format
		, uint32_t offset
		, uint32_t range )const
	{
		return std::make_unique< BufferView >( *this
			, static_cast< Buffer const & >( buffer )
			, format
			, offset
			, range );
	}

	renderer::UniformBufferBasePtr Device::createUniformBuffer( uint32_t count
		, uint32_t size
		, renderer::BufferTargets target
		, renderer::MemoryPropertyFlags memoryFlags )const
	{
		return std::make_unique< UniformBuffer >( *this
			, count
			, size
			, target
			, memoryFlags );
	}

	renderer::SwapChainPtr Device::createSwapChain( renderer::UIVec2 const & size )const
	{
		renderer::SwapChainPtr result;

		try
		{
			result = std::make_unique< SwapChain >( *this, size );
		}
		catch ( std::exception & exc )
		{
			std::cerr << "Could not create the swap chain:\n" << exc.what() << std::endl;
		}
		catch ( ... )
		{
			std::cerr << "Could not create the swap chain:\nUnknown error" << std::endl;
		}

		return result;
	}

	renderer::SemaphorePtr Device::createSemaphore()const
	{
		return std::make_unique< Semaphore >( *this );
	}

	renderer::CommandPoolPtr Device::createCommandPool( uint32_t queueFamilyIndex
		, renderer::CommandPoolCreateFlags const & flags )const
	{
		return std::make_unique< CommandPool >( *this
			, queueFamilyIndex
			, flags );
	}

	renderer::ShaderProgramPtr Device::createShaderProgram()const
	{
		return std::make_unique< ShaderProgram >( *this );
	}

	renderer::QueryPoolPtr Device::createQueryPool( renderer::QueryType type
		, uint32_t count
		, renderer::QueryPipelineStatisticFlags pipelineStatistics )const
	{
		return std::make_unique< QueryPool >( *this
			, type
			, count
			, pipelineStatistics );
	}

	void Device::waitIdle()const
	{
		vk::DeviceWaitIdle( m_device );
	}

	renderer::Mat4 Device::perspective( renderer::Radians fovy
		, float aspect
		, float zNear
		, float zFar )
	{
		float const tanHalfFovy = tan( fovy / float( 2 ) );

		renderer::Mat4 result( float( 0 ) );
		result[0][0] = float( 1 ) / ( aspect * tanHalfFovy );
		result[1][1] = float( 1 ) / ( tanHalfFovy );
		result[2][3] = -float( 1 );
		result[2][2] = zFar / ( zNear - zFar );
		result[3][2] = -( zFar * zNear ) / ( zFar - zNear );

		return result;
	}

	renderer::Mat4 Device::ortho( float left
		, float right
		, float bottom
		, float top
		, float zNear
		, float zFar )
	{
		renderer::Mat4 result{ 1 };
		result[0][0] = float( 2 ) / ( right - left );
		result[1][1] = float( 2 ) / ( top - bottom );
		result[3][0] = -( right + left ) / ( right - left );
		result[3][1] = -( top + bottom ) / ( top - bottom );
		result[2][2] = -float( 1 ) / ( zFar - zNear );
		result[3][2] = -zNear / ( zFar - zNear );

		return result;
	}

	VkMemoryRequirements Device::getBufferMemoryRequirements( VkBuffer buffer )const
	{
		VkMemoryRequirements requirements;
		vk::GetBufferMemoryRequirements( m_device
			, buffer
			, &requirements );
		return requirements;
	}

	VkMemoryRequirements Device::getImageMemoryRequirements( VkImage image )const
	{
		VkMemoryRequirements requirements;
		vk::GetImageMemoryRequirements( m_device
			, image
			, &requirements );
		return requirements;
	}
}