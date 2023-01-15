#include "nrpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

#include "Nare/Scene/Coordinator.h"
#include "Nare/Scene/Transform.h"
#include "Nare/Scene/Components.h"

#include "Nare/Renderer/VertexArray.h"
#include "Nare/Renderer/Renderer2D.h"

#include "Mesh.h"

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

    void Renderer::RenderMesh(const Mesh &mesh, const Matrix4x4 model_matrix)
    {
         
        mesh.material.shader->Bind();
        mesh.vertexArray_->Bind();
        RenderCommand::DrawIndexed(mesh.vertexArray_);
    }
}
