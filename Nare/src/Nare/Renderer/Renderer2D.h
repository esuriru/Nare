#pragma once
#include "Nare/Core/NareMath.h"
#include "Nare/Renderer/Texture.h"

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
        static void DrawQuad(const Vector2& pos, const Vector2& size, const Vector4& colour);
        static void DrawQuad(const Vector3& pos, const Vector2& size, const Vector4& colour);

        static void DrawRotatedQuad(const Vector3& pos, const Vector2& size, float rotation, const Vector4& colour);

        // Textures
        static void DrawQuad(const Vector3& pos, const Vector2& size, const Ref<Texture2D>& texture, float tilingFactor = 1.0f);

        static void DrawRotatedQuad(const Vector3& pos, const Vector2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor = 1.0f);
#pragma endregion QUAD
    private:

    };
}
