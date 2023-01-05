#include "nrpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

#include "Nare/Renderer/VertexArray.h"

namespace Nare
{
	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();

		RenderCommand::DrawIndexed(vertexArray);
	}
}
