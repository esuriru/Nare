#include "RenderCommand.h"

#include "Nare/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Nare
{
	// TODO: One byte memory leak.
	Scope<RendererAPI> RenderCommand::s_rendererAPI_ = std::make_unique<OpenGLRendererAPI>();
}
