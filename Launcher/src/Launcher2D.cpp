#include "Launcher2D.h"

namespace Nare
{
    Launcher2D::Launcher2D()
        : Layer("Launcher2D") 
    {
    }

    void Launcher2D::OnAttach()
    {
        _squareVA = VertexArray::Create();

        std::vector<float> square_vertices = {
            -0.75f, -0.75f, 0.0f,
            0.75f, -0.75f, 0.0f,
            0.75f, 0.75f, 0.0f,
            -0.75f, 0.75f, 0.0f
        };


        Ref<VertexBuffer> squareVB(VertexBuffer::Create(square_vertices.data(), square_vertices.size() * sizeof(float)));
        const BufferLayout squareLayout = {
            { ShaderDataType::Float3, "vertexPosition" },
        };

        squareVB->SetLayout(squareLayout);
        _squareVA->AddVertexBuffer(squareVB);

        std::vector<uint32_t> square_indices = {
            0, 1, 2,
            2, 3, 0
        };

        Ref<IndexBuffer> squareIB(IndexBuffer::Create(square_indices.data(), square_indices.size()));
        _squareVA->SetIndexBuffer(squareIB);

        _shader = Shader::Create("assets/shaders/FlatColour.glsl");
    }

    void Launcher2D::OnDetach()
    {


    }

    void Launcher2D::OnUpdate(Timestep ts)
    {
        RenderCommand::SetClearColour({ 0.1f,  0.1f, 0.1f, 1.f });
        RenderCommand::Clear();
        
        Renderer::BeginScene();

        // TODO: Add these functions: Shader::SetMat4, Shader::SetFloat4
        // std::dynamic_pointer_cast<OpenGLShader>(_shader)->Bind();
        // std::dynamic_pointer_cast<OpenGLShader>(_shader)->UploadUniformFloat4("u_Color", { 1.0f, 0.f, 1.0f, 1.0f });
        
        // Renderer::Submit(_squareVA, _shader);
        Renderer2D::DrawQuad(Vector2(0.f, 0.f), { 0.f , 0.f }, { 1.0f, 0.f, 1.0f, 1.0f });

        Renderer::EndScene();

    }

    void Launcher2D::OnEvent(Event &event)
    {
    }
}
