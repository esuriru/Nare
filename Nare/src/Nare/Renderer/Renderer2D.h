#pragma once
#include "Nare/Core/NareMath.h"

namespace Nare
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Exit();

        static void BeginScene();
        static void EndScene();

        // Primitives
        static void DrawQuad(const Vector2& pos, const Vector2& size, const Vector4& colour);
        static void DrawQuad(const Vector3& pos, const Vector2& size, const Vector4& colour);
    private:

    };
}
