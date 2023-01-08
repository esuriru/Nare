#pragma once
#include "RendererAPI.h"
#include "RenderCommand.h"
#include "Shader.h"

namespace Nare
{
	class VertexArray;

	class Renderer
	{
	public:
		static void Init();
        static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene();
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader);

		inline static RendererAPI::API GetAPI()
		{
			return RendererAPI::GetAPI();
		}
	};
}
