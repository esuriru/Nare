#include "SubTexture2D.h"
#include "Nare/Core/NareMath.h"

namespace Nare
{
    SubTexture2D::SubTexture2D(const Ref<Texture2D> &texture, const Vector2 &min, const Vector2 &max)
        : texture_(texture)
        , textureCoordinates_
        {
            {
                { min.x, min.y },
                { max.x, min.y },
                { max.x, max.y },
                { min.x, max.y }
            }
        }
    {
    }

    Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const Vector2 &coords, const Vector2 &cellSize, const Vector2& spriteSize)
    {
        const Vector2& min = {
            (coords.x * cellSize.x) / texture->GetWidth(),
            (coords.y * cellSize.y) / texture->GetHeight()
        };

        const Vector2& max = {
            ((coords.x + spriteSize.x) * cellSize.x) / texture->GetWidth(),
            ((coords.y + spriteSize.y) * cellSize.y) / texture->GetHeight()
        };

        return CreateRef<SubTexture2D>(texture, min, max);
    }
}
