/*
This file belongs to Renderer.
See LICENSE file in root folder
*/
#pragma once

#include <RendererPrerequisites.hpp>

namespace vk_renderer
{
	/**
	*\brief
	*	Convertit un renderer::MemoryPropertyFlags en VkMemoryPropertyFlags.
	*\param[in] flags
	*	Le renderer::MemoryPropertyFlags.
	*\return
	*	Le VkMemoryPropertyFlags.
	*/
	VkMemoryPropertyFlags convert( renderer::MemoryPropertyFlags const & flags );
}
