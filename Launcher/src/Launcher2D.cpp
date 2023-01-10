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
            -0.75f, -0.75f, 0.0f, 0.f, 0.f,
            0.75f, -0.75f, 0.0f, 1.0f, 0.f,
            0.75f, 0.75f, 0.0f, 1.0f, 1.0f,
            -0.75f, 0.75f, 0.0f, 0.f, 1.0f
        };

        Vector4 t = { 0.1f, 0.2f, 0.3f, 0.4f };
        Vector4* test = &t;

        Ref<VertexBuffer> squareVB(VertexBuffer::Create(square_vertices.data(), square_vertices.size() * sizeof(float)));
        const BufferLayout squareLayout = {
            { ShaderDataType::Float3, "vertexPosition" },
            { ShaderDataType::Float2, "vertexTexCoords" },
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
        _poppyTexture = Texture2D::Create("assets/textures/poppychibi.png");
    }

    void Launcher2D::OnDetach()
    {


    }

    void Launcher2D::OnUpdate(Timestep ts)
    {
        RenderCommand::SetClearColour({ 0.3f,  0.3f, 0.3f, 1.f });
        RenderCommand::Clear();
        
        Renderer2D::BeginScene();

        // TODO: Add these functions: Shader::SetMat4, Shader::SetFloat4
        // std::dynamic_pointer_cast<OpenGLShader>(_shader)->Bind();
        // std::dynamic_pointer_cast<OpenGLShader>(_shader)->UploadUniformFloat4("u_Color", { 1.0f, 0.f, 1.0f, 1.0f });
        
        // Renderer::Submit(_squareVA, _shader);
        // Renderer2D::DrawRotatedQuad(Vector2(0.0f, 0.0f), { 0.4f , 0.2f }, 50.f, { 0.5f, 0.f, 1.0f, 1.0f });
        // Renderer2D::DrawQuad(Vector2(-0.5f, 0.f), { 1.f , 1.f }, _poppyTexture, 2.0f);
        // Renderer2D::DrawRotatedQuad(Vector2(0.2f, -0.2f), { 1.5f , 1.5f }, 42.f, _poppyTexture, 1.0f);
        Renderer2D::DrawQuad(Vector2(0.5f, 0.8f), { 1.f , 1.f }, { 0.0f, 0.f, 1.0f, 1.0f });
        Renderer2D::DrawQuad(Vector2(-0.2f, 0.0f), { 1.5f , 1.f }, { 1.0f, 0.f, 1.0f, 1.0f });
        Renderer2D::DrawQuad(Vector2(-0.4f, 0.2f), { 0.3f , 1.f }, { 0.0f, 1.f, 1.0f, 1.0f });
        Renderer2D::DrawQuad(Vector2(0.7f, -0.4f), { 1.f , 1.5f }, { 0.0f, 1.f, 0.0f, 1.0f });
        Renderer2D::DrawQuad(Vector2(-0.5f, -0.7f), { 1.f , 1.f }, _poppyTexture);

        Renderer2D::EndScene();
    }

    void Launcher2D::OnEvent(Event &event)
    {
    }
}
