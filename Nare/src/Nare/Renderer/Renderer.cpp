#include "nrpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

#include "Nare/Renderer/VertexArray.h"

namespace Nare
{
	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader)
	{
		shader->Bind();

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
