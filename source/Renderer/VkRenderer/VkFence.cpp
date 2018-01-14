/*
This file belongs to Renderer.
See LICENSE file in root folder.
*/
#include "VkFence.hpp"

#include "VkDevice.hpp"

namespace vk_renderer
{
	Fence::Fence( Device const & device
		, renderer::FenceCreateFlags flags )
		: renderer::Fence{ device, flags }
		, m_device{ device }
	{
		VkFenceCreateInfo createInfo
		{
			VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
			nullptr,
			convert( flags )   // flags
		};
		DEBUG_DUMP( createInfo );
		auto res = CreateFence( device
			, &createInfo
			, nullptr
			, &m_fence );

		if ( !checkError( res ) )
		{
			throw std::runtime_error{ "Fence creation failed: " + getLastError() };
		}
	}

	Fence::~Fence()
	{
		DestroyFence( m_device
			, m_fence
			, nullptr );
	}

	renderer::WaitResult Fence::wait( uint32_t timeout )const
	{
		auto res = WaitForFences( m_device
			, 1
			, &m_fence
			, VK_TRUE
			, timeout );
		checkError( res );
		return res == VK_SUCCESS
			? renderer::WaitResult::eSuccess
			: ( res == VK_TIMEOUT
				? renderer::WaitResult::eTimeOut
				: renderer::WaitResult::eError );
	}

	void Fence::reset()const
	{
		ResetFences( m_device
			, 1
			, &m_fence );
	}
}
