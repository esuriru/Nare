#include "Renderer2D.h"
#include "Nare/Renderer/VertexArray.h"
#include "Nare/Renderer/Shader.h"
#include "Nare/Platform/OpenGL/OpenGLShader.h"
#include "Nare/Renderer/RenderCommand.h"

namespace Nare
{
    struct QuadVertex
    {
        Vector3 position;
        Vector4 colour;
        Vector2 texCoord;


    };

    struct Renderer2DData
    {
        const uint32_t MaxQuads = 10000;
        const uint32_t MaxVertices = MaxQuads * 4;
        const uint32_t MaxIndices = MaxQuads * 6;
        static const uint32_t MaxTextureSlots = 32; // TODO - Render capabilities

        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;

        Ref<Shader> TextureShader;
        Ref<Texture> WhiteTexture;

        uint32_t QuadIndexCount = 0;

        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;

        std::array<uint32_t, MaxTextureSlots> TextureSlots;
        uint32_t TextureSlotIndex = 1;
    };


    static Renderer2DData s_data;

    void Renderer2D::Init()
    {
        s_data.QuadVertexArray = VertexArray::Create();

        s_data.QuadVertexBuffer = VertexBuffer::Create(s_data.MaxVertices * sizeof(QuadVertex));

        s_data.QuadVertexBuffer->SetLayout({
            { ShaderDataType::Float3, "vertexPosition" },
            { ShaderDataType::Float4, "vertexColour" },
            { ShaderDataType::Float2, "vertexTexCoords" },
        });

        s_data.QuadVertexArray->AddVertexBuffer(s_data.QuadVertexBuffer);

        s_data.QuadVertexBufferBase = new QuadVertex[s_data.MaxVertices];

        uint32_t* quadIndices = new uint32_t[s_data.MaxIndices];

        uint32_t offset = 0;
        for (uint32_t i = 0; i < s_data.MaxIndices; i+=6)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }
        Ref<IndexBuffer> squareIB = IndexBuffer::Create(quadIndices, s_data.MaxIndices);
        s_data.QuadVertexArray->SetIndexBuffer(squareIB);
        delete[] quadIndices;


        s_data.WhiteTexture = Texture2D::Create(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        s_data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
        s_data.TextureShader->Bind();
        s_data.TextureShader->SetInt("texture_", 0);

        // Set all texture slots to 0
        s_data.TextureSlots = {0};
    }

    void Renderer2D::Exit()
    {
        delete[] s_data.QuadVertexBufferBase;
    }

    void Renderer2D::BeginScene()
    {
        s_data.TextureShader->Bind();

        s_data.QuadIndexCount = 0;
        s_data.QuadVertexBufferPtr = s_data.QuadVertexBufferBase;

        s_data.TextureSlotIndex = 1;
    }

    void Renderer2D::EndScene()
    {

        uint32_t dataSize = (uint8_t*)s_data.QuadVertexBufferPtr - (uint8_t*)s_data.QuadVertexBufferBase;
        s_data.QuadVertexBuffer->SetData(s_data.QuadVertexBufferBase, dataSize);

        Flush();
    }

    void Renderer2D::Flush()
    {
        RenderCommand::DrawIndexed(s_data.QuadVertexArray, s_data.QuadIndexCount);
    }


    void Renderer2D::DrawQuad(const Vector3 &pos, const Vector2 &size, const Vector4 &colour)
    {
        s_data.QuadVertexBufferPtr->position = pos;
        s_data.QuadVertexBufferPtr->colour = colour;
        s_data.QuadVertexBufferPtr->texCoord = { 0.f , 0.f };
        ++(s_data.QuadVertexBufferPtr);

        s_data.QuadVertexBufferPtr->position = { pos.x + size.x, pos.y, 0.f };
        s_data.QuadVertexBufferPtr->colour = colour;
        s_data.QuadVertexBufferPtr->texCoord = { 1.f , 0.f };
        ++(s_data.QuadVertexBufferPtr);

        s_data.QuadVertexBufferPtr->position = { pos.x + size.x, pos.y + size.y, 0 };
        s_data.QuadVertexBufferPtr->colour = colour;
        s_data.QuadVertexBufferPtr->texCoord = { 1.f , 1.f };
        ++(s_data.QuadVertexBufferPtr);

        s_data.QuadVertexBufferPtr->position = { pos.x, pos.y + size.y, 0.f };
        s_data.QuadVertexBufferPtr->colour = colour;
        s_data.QuadVertexBufferPtr->texCoord = { 0.f , 1.f };
        ++(s_data.QuadVertexBufferPtr);

        s_data.QuadIndexCount += 6;
        // s_data.TextureShader->Bind();
        // s_data.WhiteTexture->Bind();
        // s_data.TextureShader->SetFloat4("u_Color",  colour);
        // s_data.TextureShader->SetFloat("u_tilingFactor", 1.0f);

        // const auto& projection = Matrix4x4::Ortho(-1.6f, 1.6f, -0.9f, 0.9f, -10, 10);
        // const auto& view = Matrix4x4::Translate({0, 0, 0}).Inverse();
        // const auto& model = Matrix4x4::Translate(pos) * Matrix4x4::Scale(size);

        // s_data.TextureShader->SetMat4("MVP",  projection * view * model);

        // s_data.QuadVertexArray->Bind();
        // RenderCommand::DrawIndexed(s_data.QuadVertexArray);
    }


    void Renderer2D::DrawRotatedQuad(const Vector3 &pos, const Vector2 &size, float rotationDegrees, const Vector4 &colour)
    {
        s_data.TextureShader->Bind();
        s_data.WhiteTexture->Bind();
        s_data.TextureShader->SetFloat4("u_Color",  colour);
        s_data.TextureShader->SetFloat("u_tilingFactor", 1.0f);

        const auto& projection = Matrix4x4::Ortho(-1.6f, 1.6f, -0.9f, 0.9f, -10, 10);
        const auto& view = Matrix4x4::Translate({0, 0, 0}).Inverse();
        const auto& model = Matrix4x4::TRS(pos, Quaternion::Euler(0, 0, rotationDegrees), size);

        s_data.TextureShader->SetMat4("MVP",  projection * view * model);

        s_data.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_data.QuadVertexArray);
    }

    void Renderer2D::DrawRotatedQuad(const Vector3 &pos, const Vector2 &size, float rotationDegrees, const Ref<Texture2D> &texture, float tilingFactor)
    {
        s_data.TextureShader->Bind();
        s_data.TextureShader->SetFloat4("u_Color", Vector4(1.0f));
        s_data.TextureShader->SetFloat("u_tilingFactor", tilingFactor);

        const auto& projection = Matrix4x4::Ortho(-1.6f, 1.6f, -0.9f, 0.9f, -10, 10);
        const auto& view = Matrix4x4::Translate({0, 0, 0}).Inverse();
        const auto& model = Matrix4x4::TRS(pos, Quaternion::Euler(0, 0, rotationDegrees), size);

        s_data.TextureShader->SetMat4("MVP",  projection * view * model);
        texture->Bind();

        s_data.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_data.QuadVertexArray);
    }


    void Renderer2D::DrawQuad(const Vector3 &pos, const Vector2 &size, const Ref<Texture2D> &texture, float tilingFactor)
    {
        s_data.QuadVertexBufferPtr->position = pos;
        s_data.QuadVertexBufferPtr->colour = colour;
        s_data.QuadVertexBufferPtr->texCoord = { 0.f , 0.f };
        ++(s_data.QuadVertexBufferPtr);

        s_data.QuadVertexBufferPtr->position = { pos.x + size.x, pos.y, 0.f };
        s_data.QuadVertexBufferPtr->colour = colour;
        s_data.QuadVertexBufferPtr->texCoord = { 1.f , 0.f };
        ++(s_data.QuadVertexBufferPtr);

        s_data.QuadVertexBufferPtr->position = { pos.x + size.x, pos.y + size.y, 0 };
        s_data.QuadVertexBufferPtr->colour = colour;
        s_data.QuadVertexBufferPtr->texCoord = { 1.f , 1.f };
        ++(s_data.QuadVertexBufferPtr);

        s_data.QuadVertexBufferPtr->position = { pos.x, pos.y + size.y, 0.f };
        s_data.QuadVertexBufferPtr->colour = colour;
        s_data.QuadVertexBufferPtr->texCoord = { 0.f , 1.f };
        ++(s_data.QuadVertexBufferPtr);

        s_data.QuadIndexCount += 6;

#if 0
        s_data.TextureShader->Bind();
        s_data.TextureShader->SetFloat4("u_Color", Vector4(1.0f));
        s_data.TextureShader->SetFloat("u_tilingFactor", tilingFactor);

        const auto& projection = Matrix4x4::Ortho(-1.6f, 1.6f, -0.9f, 0.9f, -10, 10);
        const auto& view = Matrix4x4::Translate({0, 0, 0}).Inverse();
        const auto& model = Matrix4x4::Translate(pos) * Matrix4x4::Scale(size);

        s_data.TextureShader->SetMat4("MVP",  projection * view * model);
        texture->Bind();

        s_data.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_data.QuadVertexArray);
#endif
    }
}