/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#include "Command/Commands/GlBeginSubpassCommand.hpp"

#include "RenderPass/GlFrameBuffer.hpp"
#include "RenderPass/GlRenderPass.hpp"

#include "ashesgl4_api.hpp"

namespace ashes::gl4
{
	void buildBeginSubpassCommand( VkRenderPass renderPass
		, VkFramebuffer frameBuffer
		, VkSubpassDescription subpass
		, CmdList & list )
	{
		glLogCommand( "BeginSubpassCommand" );

		if ( get( frameBuffer )->getInternal() != GL_INVALID_INDEX )
		{
			auto references = ashes::makeArrayView( subpass.pColorAttachments
				, subpass.colorAttachmentCount );
			list.push_back( makeCmd< OpType::eDrawBuffers >( get( frameBuffer )->getDrawBuffers( references ) ) );
		}
	}
}
