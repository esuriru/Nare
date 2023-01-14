#pragma once

#include "Nare/Core/Core.h"
#include "Nare/Core/NareMath.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Material.h"

namespace Nare
{
    class Mesh
    {
    public:
        Material material;

        std::vector<Vector3> vertices;
        std::vector<Vector3> normals;
        std::vector<Vector2> uv;

        static Ref<Mesh> CreateFromOBJ(const std::string& file_path);

    private:
        Mesh();

        struct Vertex
        {
            Vector3 pos;
            Vector3 norm;
            Vector2 texCoord;

            inline bool operator<(const Vertex& rhs) const
            {
                return memcmp(static_cast<const void*>(this), static_cast<const void*>(&rhs), sizeof(Vertex)) > 0;
            }
        };


        Ref<VertexArray> vertexArray_;

        static std::string ReadFile(const std::string& file_path);

        void CreateBuffers(int count);

        friend class Renderer;
    };

}