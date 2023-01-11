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

        chessPieces_ = Texture2D::Create("assets/textures/ChessPieces.png");
        pawn_ = SubTexture2D::CreateFromCoords(chessPieces_, { 0.f, 0.f }, { 320.f, 320.f }, { 1.f, 1.f });

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

        shader_ = Shader::Create("assets/shaders/FlatColour.glsl");
        poppyTexture_ = Texture2D::Create("assets/textures/poppychibi.png");
    }

    void Launcher2D::OnDetach()
    {


    }

    void Launcher2D::OnUpdate(Timestep ts)
    {
        static float rotation = 0.0f;
        rotation += ts * 20.0f;

        Renderer2D::ResetStats();
        RenderCommand::SetClearColour({ 0.3f,  0.3f, 0.3f, 1.f });
        RenderCommand::Clear();
        
        Renderer2D::BeginScene();

        
        // Renderer::Submit(_squareVA, _shader);
        // Renderer2D::DrawRotatedQuad(Vector2(0.0f, 0.0f), { 0.4f , 0.2f }, 50.f, { 0.5f, 0.f, 1.0f, 1.0f });
        // Renderer2D::DrawQuad(Vector2(-0.5f, 0.f), { 1.f , 1.f }, _poppyTexture, 2.0f);
        // Renderer2D::DrawRotatedQuad(Vector2(0.2f, -0.2f), { 1.5f , 1.5f }, 42.f, _poppyTexture, 1.0f);
        Renderer2D::DrawQuad({0.0f, 0.0f, 0.8f}, { 1.f , 1.f }, { 0.0f, 0.f, 1.0f, 0.8f });
        Renderer2D::DrawRotatedQuad(Vector3(0.0f, 0.0f, -0.8f), { 1.0f , 1.0f }, rotation, poppyTexture_, 4.f);

        Renderer2D::DrawRotatedQuad(Vector3(0.5f, 0.0f, -0.8f), { 1.0f , 1.0f }, -rotation, pawn_);
        Renderer2D::DrawQuad({-0.4f, 0.2f, 0.5f}, { 0.3f , 1.f }, { 0.0f, 1.f, 1.0f, 0.5f });
        Renderer2D::DrawQuad({0.7f, -0.4f,0.3f}, { 1.f , 1.5f }, { 0.0f, 1.f, 0.0f, 0.3f });
        // Renderer2D::DrawQuad(Vector3(-0.5f, -0.8f, 0.2f), { 4.5f , 8.f }, _poppyTexture, 10.f);
        // Renderer2D::DrawQuad(Vector3(-0.8f, -0.8f, 0.5f), { 1.0f , 1.0f }, _poppyTexture, 4.f);

        Renderer2D::EndScene();
        // auto stats = Renderer2D::GetStats();
        // NR_CORE_TRACE("Draw calls: ", stats.DrawCalls);
        // NR_CORE_TRACE("Quads: ", stats.QuadCount);

    }

    void Launcher2D::OnEvent(Event &event)
    {
    }
}
