#pragma once
#include "nrpch.h"

#include "Texture.h"
#include "Nare/Core/Core.h"

namespace Nare
{
    class SubTexture2D
    {
    public:
        SubTexture2D(const Ref<Texture2D>& texture, const Vector2& min, const Vector2& max);

        inline const Ref<Texture2D> GetTexture() const
        {
            return texture_;
        }

        inline const Vector2* GetTexCoords() const
        {
            return textureCoordinates_.data();
        }

        static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const Vector2& coords, const Vector2& cellSize, const Vector2& spriteSize = { 1, 1 });

    private:
        Ref<Texture2D> texture_;
        
        std::array<Vector2, 4> textureCoordinates_;
    };
}