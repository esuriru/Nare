#pragma once

#include "Nare/Core/NareMath.h"
#include "Nare/Renderer/Texture.h"
#include "Nare/Renderer/SubTexture2D.h"

namespace Nare
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Exit();

        static void BeginScene();
        static void EndScene();

        static void Flush();

        // Primitives

#pragma region QUAD
        // Flat colours
        static void DrawQuad(const Vector3 &pos, const Vector2 &size, const Vector4 &colour);
        static void DrawRotatedQuad(const Vector3 &pos, const Vector2 &size, float rotation, const Vector4 &colour);

        // Textures
        static void DrawQuad(const Vector3 &pos, const Vector2 &size, const Ref<Texture2D> &texture, float tilingFactor = 1.0f);
        static void DrawQuad(const Vector3 &pos, const Vector2 &size, const Ref<SubTexture2D> &texture, float tilingFactor = 1.0f);
        static void DrawRotatedQuad(const Vector3 &pos, const Vector2 &size, float rotation, const Ref<Texture2D> &texture, float tilingFactor = 1.0f);
        static void DrawRotatedQuad(const Vector3 &pos, const Vector2 &size, float rotation, const Ref<SubTexture2D> &texture, float tilingFactor = 1.0f);
#pragma endregion QUAD

        struct Stats
        {
            uint32_t DrawCalls = 0;
            uint32_t QuadCount = 0;

            inline uint32_t GetTotalVertexCount()
            {
                return QuadCount * 4;
            }

            inline uint32_t GetTotalIndexCount()
            {
                return QuadCount * 6;
            }
        };
        static Stats GetStats();
        static void ResetStats();

    private:
        static void FlushAndReset();
    };
}
