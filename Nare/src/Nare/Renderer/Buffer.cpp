#include "Buffer.h"

#include "Renderer.h"
#include "Nare/Core.h"
#include "Nare/Platform/OpenGL/OpenGLBuffer.h"

namespace Nare
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			NR_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
			break;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		NR_CORE_ASSERT(false, "VertexBuffer cannot be generated");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			NR_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
			break;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}

		NR_CORE_ASSERT(false, "IndexBuffer cannot be generated");
		return nullptr;
	}

}
