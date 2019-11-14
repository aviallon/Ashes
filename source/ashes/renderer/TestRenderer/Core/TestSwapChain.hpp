/**
*\file
*	Instance.h
*\author
*	Sylvain Doremus
*/
#pragma once

#include "renderer/TestRenderer/TestRendererPrerequisites.hpp"

namespace ashes::test
{
	class SwapchainKHR
	{
	public:
		SwapchainKHR( VkDevice device
			, VkSwapchainCreateInfoKHR createInfo );
		~SwapchainKHR();

		uint32_t getImageCount()const;
		VkImageArray getImages()const;
		VkResult acquireNextImage( uint64_t timeout
			, VkSemaphore semaphore
			, VkFence fence
			, uint32_t & imageIndex )const;
		VkResult present( uint32_t imageIndex )const;

	protected:
		VkDevice m_device;
		VkSwapchainCreateInfoKHR m_createInfo;
		VkImage m_image{ VK_NULL_HANDLE };
		VkDeviceMemory m_deviceMemory{ VK_NULL_HANDLE };
		VkImageView m_view{ VK_NULL_HANDLE };
	};
}