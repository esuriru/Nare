#include "Renderer2D.h"
#include "Nare/Renderer/VertexArray.h"
#include "Nare/Renderer/Shader.h"
#include "Nare/Platform/OpenGL/OpenGLShader.h"
#include "Nare/Renderer/RenderCommand.h"


namespace Nare
{
    // TODO - To make a camera
    // const auto& projection = Matrix4x4::Ortho(-1.6f, 1.6f, -0.9f, 0.9f, -10, 10);
    // const auto& view = Matrix4x4::Translate({0, 0, 0}).Inverse();
    struct QuadVertex
    {
        Vector3 position;
        Vector4 colour;
        Vector2 texCoord;
        float texIndex;
        float tilingFactor;
    };

    struct Renderer2DData
    {
        static const uint32_t MaxQuads = 10000;
        static const uint32_t MaxVertices = MaxQuads * 4;
        static const uint32_t MaxIndices = MaxQuads * 6;
        static const uint32_t MaxTextureSlots = 32; // TODO - Render capabilities

        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;

        Ref<Shader> TextureShader;
        Ref<Texture> WhiteTexture;

        uint32_t QuadIndexCount = 0;

        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;

        std::array<Ref<Texture>, MaxTextureSlots> TextureSlots;
        uint32_t TextureSlotIndex = 1; // 0 = white texture

        Vector4 QuadVertexPositions[4]; 

        // TODO - Make a macro that makes it so that stats aren't calculated.
        Renderer2D::Stats stats;
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
            { ShaderDataType::Float, "textureIndex" },
            { ShaderDataType::Float, "tilingFactor" },
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

        int32_t samplers[s_data.MaxTextureSlots];
        for (int32_t i = 0; i < s_data.MaxTextureSlots; ++i)
            samplers[i] = i;

        s_data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
        s_data.TextureShader->Bind();
        s_data.TextureShader->SetIntArray("u_Textures", samplers, s_data.MaxTextureSlots);

        s_data.TextureSlots[0] = s_data.WhiteTexture;

        s_data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0, 1.0f };
        s_data.QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0, 1.0f };
        s_data.QuadVertexPositions[2] = { 0.5f, 0.5f, 0.0, 1.0f };
        s_data.QuadVertexPositions[3] = { -0.5f, 0.5f, 0.0, 1.0f };
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
        for (uint32_t i = 0; i < s_data.TextureSlotIndex; ++i)
            s_data.TextureSlots[i]->Bind(i);

        RenderCommand::DrawIndexed(s_data.QuadVertexArray, s_data.QuadIndexCount);
        ++s_data.stats.DrawCalls;
    }

    Renderer2D::Stats Renderer2D::GetStats()
    {
        return s_data.stats;
    }

    void Renderer2D::ResetStats()
    {
        memset(&s_data.stats, 0, sizeof(Stats));
    }

    void Renderer2D::FlushAndReset()
    {
        EndScene();

        s_data.QuadIndexCount = 0;
        s_data.QuadVertexBufferPtr = s_data.QuadVertexBufferBase;

        s_data.TextureSlotIndex = 1;
    }

    void Renderer2D::DrawQuad(const Vector3 &pos, const Vector2 &size, const Ref<SubTexture2D> &subtexture, float tilingFactor)
    {
        // TODO - make this a static colour, or even make a helper class that stores a Vector4.
        constexpr Vector4 white = { 1.0f, 1.0f, 1.0f, 1.0f };
        constexpr size_t quadVertexCount = 4;
        const Vector2* texCoords = subtexture->GetTexCoords();
        const Ref<Texture2D> texture = subtexture->GetTexture();

        if (s_data.QuadIndexCount >= Renderer2DData::MaxIndices)
            FlushAndReset();

        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < s_data.TextureSlotIndex; ++i)
        {
            if (*s_data.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = static_cast<float>(i);
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            textureIndex = static_cast<float>(s_data.TextureSlotIndex);
            s_data.TextureSlots[s_data.TextureSlotIndex] = texture;
            ++s_data.TextureSlotIndex;
        }

        Matrix4x4 model = Matrix4x4::Translate(pos) * Matrix4x4::Scale(size);

        s_data.QuadVertexBufferPtr->position = model * s_data.QuadVertexPositions[0];
        s_data.QuadVertexBufferPtr->colour = white;
        s_data.QuadVertexBufferPtr->texCoord = { 0.f , 0.f };
        s_data.QuadVertexBufferPtr->texIndex = textureIndex;
        s_data.QuadVertexBufferPtr->tilingFactor = tilingFactor;
        ++(s_data.QuadVertexBufferPtr);

        s_data.QuadVertexBufferPtr->position = model * s_data.QuadVertexPositions[1];
        s_data.QuadVertexBufferPtr->colour = white;
        s_data.QuadVertexBufferPtr->texCoord = { 1.f , 0.f };
        s_data.QuadVertexBufferPtr->texIndex = textureIndex;
        s_data.QuadVertexBufferPtr->tilingFactor = tilingFactor;
        ++(s_data.QuadVertexBufferPtr);

        s_data.QuadVertexBufferPtr->position = model * s_data.QuadVertexPositions[2];
        s_data.QuadVertexBufferPtr->colour = white;
        s_data.QuadVertexBufferPtr->texCoord = { 1.f , 1.f };
        s_data.QuadVertexBufferPtr->texIndex = textureIndex;
        s_data.QuadVertexBufferPtr->tilingFactor = tilingFactor;
        ++(s_data.QuadVertexBufferPtr);

        s_data.QuadVertexBufferPtr->position = model * s_data.QuadVertexPositions[3];
        s_data.QuadVertexBufferPtr->colour = white;
        s_data.QuadVertexBufferPtr->texCoord = { 0.f , 1.f };
        s_data.QuadVertexBufferPtr->texIndex = textureIndex;
        s_data.QuadVertexBufferPtr->tilingFactor = tilingFactor;
        ++(s_data.QuadVertexBufferPtr);

        s_data.QuadIndexCount += 6;
        ++s_data.stats.QuadCount;

    }

    void Renderer2D::DrawQuad(const Vector3 &pos, const Vector2 &size, const Vector4 &colour)
    {
        constexpr size_t quadVertexCount = 4;
        constexpr float texIndex = 0.0f; // White texture
        constexpr float tilingFactor = 1.0f; 
        constexpr std::array<Vector2, 4> texCoords {
            {
                { 0.0f, 0.0f },
                { 1.0f, 0.0f },
                { 1.0f, 1.0f },
                { 0.0f, 1.0f }
            }
        };

        if (s_data.QuadIndexCount >= Renderer2DData::MaxIndices)
            FlushAndReset();

        Matrix4x4 model = Matrix4x4::Translate(pos) * Matrix4x4::Scale(size);

        for (size_t i = 0; i < quadVertexCount; ++i)
        {
            s_data.QuadVertexBufferPtr->position = model * s_data.QuadVertexPositions[i];
            s_data.QuadVertexBufferPtr->colour = colour;
            s_data.QuadVertexBufferPtr->texCoord = texCoords[i];
            s_data.QuadVertexBufferPtr->texIndex = texIndex;
            s_data.QuadVertexBufferPtr->tilingFactor = tilingFactor;
            ++s_data.QuadVertexBufferPtr;
        }

        s_data.QuadIndexCount += 6;
        ++s_data.stats.QuadCount;
    }


    void Renderer2D::DrawRotatedQuad(const Vector3 &pos, const Vector2 &size, float rotationDegrees, const Vector4 &colour)
    {
        constexpr size_t quadVertexCount = 4;
        constexpr float texIndex = 0.0f; // White texture
        constexpr float tilingFactor = 1.0f; 
        constexpr std::array<Vector2, 4> texCoords {
            {
                { 0.0f, 0.0f },
                { 1.0f, 0.0f },
                { 1.0f, 1.0f },
                { 0.0f, 1.0f }
            }
        };

        if (s_data.QuadIndexCount >= Renderer2DData::MaxIndices)
            FlushAndReset();

        Matrix4x4 model = Matrix4x4::TRS(pos, Quaternion::Euler(0, 0, rotationDegrees), colour);

        for (size_t i = 0; i < quadVertexCount; ++i)
        {
            s_data.QuadVertexBufferPtr->position = model * s_data.QuadVertexPositions[i];
            s_data.QuadVertexBufferPtr->colour = colour;
            s_data.QuadVertexBufferPtr->texCoord = texCoords[i];
            s_data.QuadVertexBufferPtr->texIndex = texIndex;
            s_data.QuadVertexBufferPtr->tilingFactor = tilingFactor;
            ++(s_data.QuadVertexBufferPtr);
        }

        s_data.QuadIndexCount += 6;
        ++s_data.stats.QuadCount;
    }

    void Renderer2D::DrawRotatedQuad(const Vector3 &pos, const Vector2 &size, float rotationDegrees, const Ref<Texture2D> &texture, float tilingFactor)
    {
        // TODO - make this a static colour, or even make a helper class that stores a Vector4.
        constexpr Vector4 white = { 1.0f, 1.0f, 1.0f, 1.0f };
        constexpr size_t quadVertexCount = 4;
        constexpr std::array<Vector2, 4> texCoords {
            {
                { 0.0f, 0.0f },
                { 1.0f, 0.0f },
                { 1.0f, 1.0f },
                { 0.0f, 1.0f }
            }
        };

        if (s_data.QuadIndexCount >= Renderer2DData::MaxIndices)
            FlushAndReset();

        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < s_data.TextureSlotIndex; ++i)
        {
            if (*s_data.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = static_cast<float>(i);
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            textureIndex = static_cast<float>(s_data.TextureSlotIndex);
            s_data.TextureSlots[s_data.TextureSlotIndex] = texture;
            ++s_data.TextureSlotIndex;
        }

        Matrix4x4 model = Matrix4x4::TRS(pos, Quaternion::Euler(0, 0, rotationDegrees), size);

        for (size_t i = 0; i < quadVertexCount; ++i)
        {
            s_data.QuadVertexBufferPtr->position = model * s_data.QuadVertexPositions[i];
            s_data.QuadVertexBufferPtr->colour = white;
            s_data.QuadVertexBufferPtr->texCoord = texCoords[i];
            s_data.QuadVertexBufferPtr->texIndex = textureIndex;
            s_data.QuadVertexBufferPtr->tilingFactor = tilingFactor;
            ++(s_data.QuadVertexBufferPtr);
        }

        s_data.QuadIndexCount += 6;
        ++s_data.stats.QuadCount;
    }

    void Renderer2D::DrawRotatedQuad(const Vector3 &pos, const Vector2 &size, float rotationDegrees, const Ref<SubTexture2D> &subtexture, float tilingFactor)
    {
        // TODO - make this a static colour, or even make a helper class that stores a Vector4.
        constexpr Vector4 white = { 1.0f, 1.0f, 1.0f, 1.0f };
        constexpr size_t quadVertexCount = 4;
        const Vector2* texCoords = subtexture->GetTexCoords();
        const Ref<Texture2D> texture = subtexture->GetTexture();

        if (s_data.QuadIndexCount >= Renderer2DData::MaxIndices)
            FlushAndReset();

        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < s_data.TextureSlotIndex; ++i)
        {
            if (*s_data.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = static_cast<float>(i);
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            textureIndex = static_cast<float>(s_data.TextureSlotIndex);
            s_data.TextureSlots[s_data.TextureSlotIndex] = texture;
            ++s_data.TextureSlotIndex;
        }

        Matrix4x4 model = Matrix4x4::TRS(pos, Quaternion::Euler(0, 0, rotationDegrees), size);

        for (size_t i = 0; i < quadVertexCount; ++i)
        {
            s_data.QuadVertexBufferPtr->position = model * s_data.QuadVertexPositions[i];
            s_data.QuadVertexBufferPtr->colour = white;
            s_data.QuadVertexBufferPtr->texCoord = texCoords[i];
            s_data.QuadVertexBufferPtr->texIndex = textureIndex;
            s_data.QuadVertexBufferPtr->tilingFactor = tilingFactor;
            ++(s_data.QuadVertexBufferPtr);
        }
        s_data.QuadIndexCount += 6;

        ++s_data.stats.QuadCount;
    }


    void Renderer2D::DrawQuad(const Vector3 &pos, const Vector2 &size, const Ref<Texture2D> &texture, float tilingFactor)
    {
        // TODO - make this a static colour, or even make a helper class that stores a Vector4.
        constexpr Vector4 white = { 1.0f, 1.0f, 1.0f, 1.0f };
        constexpr size_t quadVertexCount = 4;
        constexpr std::array<Vector2, 4> texCoords {
            {
                { 0.0f, 0.0f },
                { 1.0f, 0.0f },
                { 1.0f, 1.0f },
                { 0.0f, 1.0f }
            }
        };

        if (s_data.QuadIndexCount >= Renderer2DData::MaxIndices)
            FlushAndReset();

        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < s_data.TextureSlotIndex; ++i)
        {
            if (*s_data.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = static_cast<float>(i);
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            if (s_data.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
                FlushAndReset();
            textureIndex = static_cast<float>(s_data.TextureSlotIndex);
            s_data.TextureSlots[s_data.TextureSlotIndex] = texture;
            ++s_data.TextureSlotIndex;
        }

        Matrix4x4 model = Matrix4x4::Translate(pos) * Matrix4x4::Scale(size);

        for (size_t i = 0; i < quadVertexCount; ++i)
        {
            s_data.QuadVertexBufferPtr->position = model * s_data.QuadVertexPositions[i];
            s_data.QuadVertexBufferPtr->colour = white;
            s_data.QuadVertexBufferPtr->texCoord = texCoords[i];
            s_data.QuadVertexBufferPtr->texIndex = textureIndex;
            s_data.QuadVertexBufferPtr->tilingFactor = tilingFactor;
            ++(s_data.QuadVertexBufferPtr);
        }

        s_data.QuadIndexCount += 6;
        ++s_data.stats.QuadCount;

    }
}