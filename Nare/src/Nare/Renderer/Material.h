#pragma once

#include "Nare/Core/NareMath.h"
#include "Shader.h"

namespace Nare
{
    class Material
    {
    public:
        Material();
        ~Material() = default;

        Vector4 colour;
        Ref<Shader> shader;
    };
}