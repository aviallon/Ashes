/*
This file belongs to Ashes.
See LICENSE file in root folder.
*/
#include "Ashes/Core/SwapChain.hpp"

#include "Ashes/Core/Device.hpp"

namespace ashes
{
	SwapChain::SwapChain( Device const & device
		, Extent2D const & size )
		: m_device{ device }
		, m_dimensions{ size }
	{
		registerObject( m_device, "SwapChain", this );
	}

	SwapChain::~SwapChain()
	{
		unregisterObject( m_device, this );
	}
}