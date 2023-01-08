#include "Renderer2D.h"
#include "Nare/Renderer/VertexArray.h"
#include "Nare/Renderer/Shader.h"
#include "Nare/Platform/OpenGL/OpenGLShader.h"
#include "Nare/Renderer/RenderCommand.h"

namespace Nare
{
    struct Renderer2DStorage
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<Shader> FlatColourShader;
    };

    static Renderer2DStorage* s_data;

    void Renderer2D::Init()
    {
        s_data = new Renderer2DStorage();

        s_data->QuadVertexArray = VertexArray::Create();

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
        s_data->QuadVertexArray->AddVertexBuffer(squareVB);

        std::vector<uint32_t> square_indices = {
            0, 1, 2,
            2, 3, 0
        };

        Ref<IndexBuffer> squareIB(IndexBuffer::Create(square_indices.data(), square_indices.size()));
        s_data->QuadVertexArray->SetIndexBuffer(squareIB);

        s_data->FlatColourShader = Shader::Create("assets/shaders/FlatColour.glsl");
    }

    void Renderer2D::Exit()
    {
        delete s_data;
    }

    void Renderer2D::BeginScene()
    {
    }

    void Renderer2D::EndScene()
    {
    }

    void Renderer2D::DrawQuad(const Vector2 &pos, const Vector2 &size, const Vector4 &colour)
    {
        DrawQuad({ pos.x, pos.y, 0 }, size, colour);
    }

    void Renderer2D::DrawQuad(const Vector3 &pos, const Vector2 &size, const Vector4 &colour)
    {
        s_data->FlatColourShader->Bind();
        s_data->FlatColourShader->SetFloat4("u_Color", colour);

        const auto& projection = Matrix4x4::Ortho(-1.6f, 1.6f, -0.9f, 0.9f, -10, 10);
        const auto& view = Matrix4x4::Translate({0, 0, 0}).Inverse();
        const auto& model = Matrix4x4::Translate(pos) * Matrix4x4::Scale(size);

        s_data->FlatColourShader->SetMat4("model",  projection * view * model);

        s_data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_data->QuadVertexArray);
    }

}