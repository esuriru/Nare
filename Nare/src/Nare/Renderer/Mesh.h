#pragma once

#include "Nare/Core/Core.h"
#include "Nare/Core/NareMath.h"
#include "Buffer.h"

namespace Nare
{
    class Mesh
    {
    public:
        std::vector<Vector3> vertices;
        std::vector<Vector3> normals;
        std::vector<Vector2> uv;

        static Ref<Mesh> CreateFromOBJ(const std::string& file_path);

    private:
        Mesh();

        Ref<VertexBuffer> vertexBuffer_;
        Ref<IndexBuffer> indexBuffer_;

        static std::string ReadFile(const std::string& file_path);

        void CreateBuffers();
    };

}