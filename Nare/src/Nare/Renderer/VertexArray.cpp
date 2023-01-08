#include "VertexArray.h"

#include "Renderer.h"
#include "Nare/Core/Core.h"
#include "Nare/Platform/OpenGL/OpenGLVertexArray.h"

namespace Nare
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NR_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		NR_CORE_ASSERT(false, "VertexBuffer cannot be generated");
		return nullptr;

	}
}
