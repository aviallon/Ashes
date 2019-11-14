/*
See LICENSE file in root folder
*/
#ifndef ___GlRenderer_QueryPool_H___
#define ___GlRenderer_QueryPool_H___

#include "renderer/Gl3Renderer/GlRendererPrerequisites.hpp"

namespace ashes::gl3
{
	class QueryPool
	{
	public:
		QueryPool( VkDevice device
			, VkQueryPoolCreateInfo createInfo );
		~QueryPool();

		VkResult getResults( uint32_t firstQuery
			, uint32_t queryCount
			, VkDeviceSize stride
			, VkQueryResultFlags flags
			, UInt32Array & data )const;
		VkResult getResults( uint32_t firstQuery
			, uint32_t queryCount
			, VkDeviceSize stride
			, VkQueryResultFlags flags
			, UInt64Array & data )const;

		inline auto begin()const
		{
			return m_names.begin();
		}

		inline auto end()const
		{
			return m_names.end();
		}

		inline auto getType()const
		{
			return m_queryType;
		}

	protected:
		VkDevice m_device;
		VkQueryPoolCreateFlags m_flags;
		VkQueryType m_queryType;
		uint32_t m_queryCount;
		VkQueryPipelineStatisticFlags m_pipelineStatistics;
		std::vector< GLuint > m_names;
	};
}

#endif