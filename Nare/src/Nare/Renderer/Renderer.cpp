#include "nrpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

#include "Nare/Renderer/VertexArray.h"
#include "Nare/Renderer/Renderer2D.h"

namespace Nare
{
	void Renderer::Init()
	{
		RenderCommand::Init();
        Renderer2D::Init();
	}

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
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
