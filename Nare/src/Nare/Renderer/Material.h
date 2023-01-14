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
        Vector4 ambient;
        Vector4 diffuse;
        Vector4 specular;
        float shininess;

        Ref<Shader> shader;
    };
}