#include "VertexArray.h"

#include "Renderer.h"
#include "Nare/Platform/OpenGL/OpenGLVertexArray.h"

namespace Nare
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NR_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}

		NR_CORE_ASSERT(false, "VertexBuffer cannot be generated");
		return nullptr;

	}
}
