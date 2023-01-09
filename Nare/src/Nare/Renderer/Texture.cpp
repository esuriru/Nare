#include "Texture.h"

#include "Renderer.h"
#include "Nare/Core/Core.h"

#include "Nare/Platform/OpenGL/OpenGLTexture2D.h"

namespace Nare
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	NR_CORE_ASSERT(false, "RendererAPI::None is currently not supported.") return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(path);
		}

		NR_CORE_ASSERT(false, "Unknonw Renderer API.");
		return nullptr;
	}

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
    {
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	NR_CORE_ASSERT(false, "RendererAPI::None is currently not supported.") return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLTexture2D>(width, height);
		}

		NR_CORE_ASSERT(false, "Unknonw Renderer API.");
		return nullptr;
    }
}
