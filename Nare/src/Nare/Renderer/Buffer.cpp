#include "Buffer.h"

#include "Renderer.h"
#include "Nare/Core.h"
#include "Nare/Platform/OpenGL/OpenGLBuffer.h"

namespace Nare
{
	/**
	 * \brief Create a vertex buffer (respective to the rendering API)  
	 * \param vertices Pointer to the first element in the storage (.data() for std::vector)
	 * \param size Size in bytes of the storage
	 * \return Raw vertex buffer pointer
	 */
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NR_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		NR_CORE_ASSERT(false, "VertexBuffer cannot be generated")
		return nullptr;
	}

	/**
	 * \brief Create a index buffer (respective to the rendering API)  
	 * \param indices Pointer to the first element in the storage (.data() for std::vector)
	 * \param count Number of indices in the storage
	 * \return Raw index buffer pointer
	 */
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NR_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		}

		NR_CORE_ASSERT(false, "IndexBuffer cannot be generated")
		return nullptr;
	}

}