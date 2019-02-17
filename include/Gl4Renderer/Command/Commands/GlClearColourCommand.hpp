/*
This file belongs to Ashes.
See LICENSE file in root folder
*/
#pragma once

#include "Gl4Renderer/Command/Commands/GlCommandBase.hpp"

#include <Ashes/RenderPass/ClearValue.hpp>

namespace gl_renderer
{
	/**
	*\brief
	*	Commande de vidage d'une image.
	*/
	class ClearColourCommand
		: public CommandBase
	{
	public:
		/**
		*\brief
		*	Constructeur.
		*\param[in] image
		*	L'image à vider.
		*\param[in] colour
		*	La couleur de vidage.
		*/
		ClearColourCommand( Device const & device
			, ashes::TextureView const & image
			, ashes::ClearColorValue const & colour );

		void apply( ContextLock const & context )const override;
		CommandPtr clone()const override;

	private:
		TextureView const & m_image;
		ashes::ClearColorValue m_colour;
		GlInternal m_internal;
		GlFormat m_format;
		GlType m_type;
	};
}