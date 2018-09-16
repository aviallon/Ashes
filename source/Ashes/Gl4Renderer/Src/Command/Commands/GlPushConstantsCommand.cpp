/*
This file belongs to GlRenderer.
See LICENSE file in root folder.
*/
#include "GlPushConstantsCommand.hpp"

#include "Buffer/PushConstantsBuffer.hpp"

namespace gl_renderer
{
	PushConstantsCommand::PushConstantsCommand( Device const & device
		, PushConstantsDesc const & pcb )
		: CommandBase{ device }
		, m_pcb{ pcb }
	{
	}

	void PushConstantsCommand::apply( ContextLock const & context )const
	{
		glLogCommand( "PushConstantsCommand" );
		auto buffer = m_pcb.data.data();

		for ( auto & constant : m_pcb.constants )
		{
			switch ( constant.format )
			{
			case ashes::ConstantFormat::eFloat:
				glLogCall( context
					, glUniform1fv
					, constant.location
					, 1u
					, reinterpret_cast< GLfloat const * >( buffer ) );
				break;

			case ashes::ConstantFormat::eVec2f:
				glLogCall( context
					, glUniform2fv
					, constant.location
					, 1u
					, reinterpret_cast< GLfloat const * >( buffer ) );
				break;

			case ashes::ConstantFormat::eVec3f:
				glLogCall( context
					, glUniform3fv
					, constant.location
					, 1u
					, reinterpret_cast< GLfloat const * >( buffer ) );
				break;

			case ashes::ConstantFormat::eVec4f:
				glLogCall( context
					, glUniform4fv
					, constant.location
					, 1u
					, reinterpret_cast< GLfloat const * >( buffer ) );
				break;

			case ashes::ConstantFormat::eMat2f:
				glLogCall( context
					, glUniformMatrix2fv
					, constant.location
					, 1u
					, GL_FALSE
					, reinterpret_cast< GLfloat const * >( buffer ) );
				break;

			case ashes::ConstantFormat::eMat3f:
				glLogCall( context
					, glUniformMatrix3fv
					, constant.location
					, 1u
					, GL_FALSE
					, reinterpret_cast< GLfloat const * >( buffer ) );
				break;

			case ashes::ConstantFormat::eMat4f:
				glLogCall( context
					, glUniformMatrix4fv
					, constant.location
					, 1u
					, GL_FALSE
					, reinterpret_cast< GLfloat const * >( buffer ) );
				break;

			case ashes::ConstantFormat::eInt:
				glLogCall( context
					, glUniform1iv
					, constant.location
					, 1u
					, reinterpret_cast< GLint const * >( buffer ) );
				break;

			case ashes::ConstantFormat::eVec2i:
				glLogCall( context
					, glUniform2iv
					, constant.location
					, 1u
					, reinterpret_cast< GLint const * >( buffer ) );
				break;

			case ashes::ConstantFormat::eVec3i:
				glLogCall( context
					, glUniform3iv
					, constant.location
					, 1u
					, reinterpret_cast< GLint const * >( buffer ) );
				break;

			case ashes::ConstantFormat::eVec4i:
				glLogCall( context
					, glUniform4iv
					, constant.location
					, 1u
					, reinterpret_cast< GLint const * >( buffer ) );
				break;

			case ashes::ConstantFormat::eUInt:
				glLogCall( context
					, glUniform1uiv
					, constant.location
					, 1u
					, reinterpret_cast< GLuint const * >( buffer ) );
				break;

			case ashes::ConstantFormat::eVec2ui:
				glLogCall( context
					, glUniform2uiv
					, constant.location
					, 1u
					, reinterpret_cast< GLuint const * >( buffer ) );
				break;

			case ashes::ConstantFormat::eVec3ui:
				glLogCall( context
					, glUniform3uiv
					, constant.location
					, 1u
					, reinterpret_cast< GLuint const * >( buffer ) );
				break;

			case ashes::ConstantFormat::eVec4ui:
				glLogCall( context
					, glUniform4uiv
					, constant.location
					, 1u
					, reinterpret_cast< GLuint const * >( buffer ) );
				break;

			case ashes::ConstantFormat::eColour:
				glLogCall( context
					, glUniform4fv
					, constant.location
					, 1u
					, reinterpret_cast< GLfloat const * >( buffer ) );
				break;

			default:
				assert( false && "Unsupported constant format" );
				break;
			}

			buffer += getSize( constant.format );
		}
	}

	CommandPtr PushConstantsCommand::clone()const
	{
		return std::make_unique< PushConstantsCommand >( *this );
	}
}