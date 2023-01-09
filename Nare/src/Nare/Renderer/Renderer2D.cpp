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
        Ref<Shader> TextureShader;
        Ref<Texture> WhiteTexture;
    };

    static Renderer2DStorage* s_data;

    void Renderer2D::Init()
    {
        s_data = new Renderer2DStorage();

        s_data->QuadVertexArray = VertexArray::Create();

        std::vector<float> square_vertices = {
            -0.75f, -0.75f, 0.0f, 0.f, 0.f,
            0.75f, -0.75f, 0.0f, 1.0f, 0.f,
            0.75f, 0.75f, 0.0f, 1.0f, 1.0f,
            -0.75f, 0.75f, 0.0f, 0.0f, 1.0f
        };

        Ref<VertexBuffer> squareVB(VertexBuffer::Create(square_vertices.data(), square_vertices.size() * sizeof(float)));
        const BufferLayout squareLayout = {
            { ShaderDataType::Float3, "vertexPosition" },
            { ShaderDataType::Float2, "vertexTexCoords" },
        };

        squareVB->SetLayout(squareLayout);
        s_data->QuadVertexArray->AddVertexBuffer(squareVB);

        std::vector<uint32_t> square_indices = {
            0, 1, 2,
            2, 3, 0
        };

        Ref<IndexBuffer> squareIB(IndexBuffer::Create(square_indices.data(), square_indices.size()));
        s_data->QuadVertexArray->SetIndexBuffer(squareIB);

        s_data->WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        s_data->FlatColourShader = Shader::Create("assets/shaders/FlatColour.glsl");
        s_data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
        s_data->TextureShader->Bind();
        s_data->TextureShader->SetInt("texture_", 0);
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
        s_data->TextureShader->Bind();
        s_data->WhiteTexture->Bind();
        s_data->TextureShader->SetFloat4("u_Color",  colour);
        s_data->TextureShader->SetFloat("u_tilingFactor", 1.0f);

        const auto& projection = Matrix4x4::Ortho(-1.6f, 1.6f, -0.9f, 0.9f, -10, 10);
        const auto& view = Matrix4x4::Translate({0, 0, 0}).Inverse();
        const auto& model = Matrix4x4::Translate(pos) * Matrix4x4::Scale(size);

        s_data->TextureShader->SetMat4("MVP",  projection * view * model);

        s_data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_data->QuadVertexArray);
    }


    void Renderer2D::DrawRotatedQuad(const Vector3 &pos, const Vector2 &size, float rotationDegrees, const Vector4 &colour)
    {
        s_data->TextureShader->Bind();
        s_data->WhiteTexture->Bind();
        s_data->TextureShader->SetFloat4("u_Color",  colour);
        s_data->TextureShader->SetFloat("u_tilingFactor", 1.0f);

        const auto& projection = Matrix4x4::Ortho(-1.6f, 1.6f, -0.9f, 0.9f, -10, 10);
        const auto& view = Matrix4x4::Translate({0, 0, 0}).Inverse();
        const auto& model = Matrix4x4::TRS(pos, Quaternion::Euler(0, 0, rotationDegrees), size);

        s_data->TextureShader->SetMat4("MVP",  projection * view * model);

        s_data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_data->QuadVertexArray);
    }
    void Renderer2D::DrawRotatedQuad(const Vector3 &pos, const Vector2 &size, float rotationDegrees, const Ref<Texture2D> &texture, float tilingFactor)
    {
        s_data->TextureShader->Bind();
        s_data->TextureShader->SetFloat4("u_Color", Vector4(1.0f));
        s_data->TextureShader->SetFloat("u_tilingFactor", tilingFactor);

        const auto& projection = Matrix4x4::Ortho(-1.6f, 1.6f, -0.9f, 0.9f, -10, 10);
        const auto& view = Matrix4x4::Translate({0, 0, 0}).Inverse();
        const auto& model = Matrix4x4::TRS(pos, Quaternion::Euler(0, 0, rotationDegrees), size);

        s_data->TextureShader->SetMat4("MVP",  projection * view * model);
        texture->Bind();

        s_data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_data->QuadVertexArray);
    }


    void Renderer2D::DrawQuad(const Vector3 &pos, const Vector2 &size, const Ref<Texture2D> &texture, float tilingFactor)
    {
        s_data->TextureShader->Bind();
        s_data->TextureShader->SetFloat4("u_Color", Vector4(1.0f));
        s_data->TextureShader->SetFloat("u_tilingFactor", tilingFactor);

        const auto& projection = Matrix4x4::Ortho(-1.6f, 1.6f, -0.9f, 0.9f, -10, 10);
        const auto& view = Matrix4x4::Translate({0, 0, 0}).Inverse();
        const auto& model = Matrix4x4::Translate(pos) * Matrix4x4::Scale(size);

        s_data->TextureShader->SetMat4("MVP",  projection * view * model);
        texture->Bind();

        s_data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_data->QuadVertexArray);
    }
}