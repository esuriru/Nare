#include "RenderCommand.h"

#include "Nare/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Nare
{
	// TODO: One byte memory leak.
	RendererAPI* RenderCommand::s_rendererAPI_ = new OpenGLRendererAPI();
}
