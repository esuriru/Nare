#include "Shader.h"
#include <GLAD/glad.h>

#include "Renderer.h"
#include "Nare/Core/Core.h"
#include "Nare/Core/Log.h"
#include "Nare/Platform/OpenGL/OpenGLShader.h"

namespace Nare
{
	Shader* Shader::Create(const std::string& vertex_file_path, const std::string& fragment_file_path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NR_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertex_file_path, fragment_file_path);
		}

		NR_CORE_ASSERT(false, "Shader cannot be generated")
		return nullptr;
	}

	Shader* Shader::Create(const std::string& file_path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			NR_CORE_ASSERT(false, "RendererAPI::None is currently not supported")
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(file_path);
		}

		NR_CORE_ASSERT(false, "Shader cannot be generated")
		return nullptr;
	}
}
