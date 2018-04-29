/*
This file belongs to RendererLib.
See LICENSE file in root folder.
*/
#include "Pipeline/PipelineLayout.hpp"

#include "Core/Device.hpp"
#include "Core/RenderingResources.hpp"
#include "Descriptor/DescriptorSetLayout.hpp"

namespace renderer
{
	PipelineLayout::PipelineLayout( Device const & device
		, DescriptorSetLayoutCRefArray const & layouts
		, PushConstantRangeCRefArray const & pushConstantRanges )
		: m_device{ device }
	{
		registerObject( m_device, "PipelineLayout", this );
	}

	PipelineLayout::~PipelineLayout()
	{
		unregisterObject( m_device, this );
	}
}