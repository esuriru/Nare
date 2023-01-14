#include "nrpch.h"
#include "Mesh.h"

namespace Nare
{
    Ref<Mesh> Mesh::CreateFromOBJ(const std::string &file_path)
    {
        Ref<Mesh> mesh = CreateRef<Mesh>();

        // Buffers
        std::vector<Vector3> raw_verts;
        std::vector<Vector3> raw_normals;
        std::vector<Vector2> raw_uv;
        std::vector<uint32_t> raw_face_indices;
        std::vector<uint32_t> raw_texture_indices;
        std::vector<uint32_t> raw_normal_indices;

        std::ifstream file_data(file_path, std::ios::in | std::ios::binary);
        // TODO - should not be an assert
        NR_CORE_ASSERT(!file_data.is_open(), "Could not open this file: ", file_path);
        std::string line;

        while (std::getline(file_data, line))
        {
            if (line.front() == 'v')
            {
                std::istringstream data(line.substr(2));
                Vector3 vertice; 
                data >> vertice.x >> vertice.y >> vertice.z;
                raw_verts.push_back(vertice);
            }

            if (line.substr(0, 2) == "vt")
            {
                std::istringstream data(line.substr(3));
                Vector2 tex_coords; 
                data >> tex_coords.x >> tex_coords.y;
                raw_uv.push_back(tex_coords);
            }

            if (line.substr(0, 2) == "vn")
            {
                std::istringstream data(line.substr(3));
                Vector3 normal;
                data >> normal.x >> normal.y >> normal.z;
                raw_normals.push_back(normal);
            }

            if (line.front() == 'f')
            {
                uint32_t f_a, f_b, f_c, f_d;
                uint32_t t_a, t_b, t_c, t_d;
                uint32_t n_a, n_b, n_c, n_d;

                auto line_data = line.data();
                int indices_number = sscanf_s(line_data, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &f_a, &t_a, &n_a, &f_b, &t_b, &n_b, &f_c, &t_c, &n_c, &f_d, &t_d, &n_d);

                if (indices_number == 9)
                {
                    raw_face_indices.push_back(f_a);
                    raw_face_indices.push_back(f_b);
                    raw_face_indices.push_back(f_c);

                    raw_texture_indices.push_back(t_a);
                    raw_texture_indices.push_back(t_b);
                    raw_texture_indices.push_back(t_c);

                    raw_normal_indices.push_back(n_a);
                    raw_normal_indices.push_back(n_b);
                    raw_normal_indices.push_back(n_c);
                }
                else if (indices_number == 12)
                {
                    raw_face_indices.push_back(f_a);
                    raw_face_indices.push_back(f_b);
                    raw_face_indices.push_back(f_c);
                    raw_face_indices.push_back(f_d);

                    raw_texture_indices.push_back(t_a);
                    raw_texture_indices.push_back(t_b);
                    raw_texture_indices.push_back(t_c);
                    raw_texture_indices.push_back(t_d);

                    raw_normal_indices.push_back(n_a);
                    raw_normal_indices.push_back(n_b);
                    raw_normal_indices.push_back(n_c);
                    raw_normal_indices.push_back(n_d);
                }
                else
                {
                    NR_CORE_ASSERT(false, "Wrong number of indices scanned while importing OBJ.");
                    return nullptr;
                }
            }
        }
        file_data.close();

        uint32_t i;
        for (i = 0; i < raw_face_indices.size(); ++i)
        {
            Vector3 vert = raw_verts[raw_face_indices[i] - 1];
            Vector2 tex_coord = raw_uv[raw_texture_indices[i] - 1];
            Vector3 norm = raw_normals[raw_normal_indices[i] - 1];

            mesh->vertices.push_back(vert);
            mesh->uv.push_back(tex_coord);
            mesh->normals.push_back(norm);
        }

        mesh->CreateBuffers(i);
        return mesh;
    }

    Mesh::Mesh()
    {

    }

    std::string Mesh::ReadFile(const std::string &file_path)
    {
#ifdef NR_PLATFORM_WINDOWS
		std::string result;
		std::ifstream in(file_path, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
			// TODO: Make this not an assert.
			NR_CORE_ASSERT(false, "Could not open file: '", file_path, "'");

		return result;
#endif
    }

    void Mesh::CreateBuffers(int count)
    {
        std::map<Mesh::Vertex, uint16_t> vertex_map;

        std::vector<float> vertex_data;
        std::vector<uint32_t> indices;

        Vertex v;
        uint32_t index;

        for (int j = 0; j < count; ++j)
        {
            v = { vertices[j], normals[j], uv[j] };

            std::map<Mesh::Vertex, uint16_t>::iterator map_iterator = vertex_map.find(v);
            if (map_iterator == vertex_map.end())
            {
                indices.push_back(map_iterator->second);    
            }
            else
            {
                for (int i = 0; i < 3; ++i)
                    vertex_data.push_back(vertices[j][i]);

                for (int i = 0; i < 3; ++i)
                    vertex_data.push_back(normals[j][i]);

                for (int i = 0; i < 2; ++i)
                    vertex_data.push_back(uv[j][i]);

                uint32_t new_index = static_cast<uint32_t>(vertex_data.size() / 8) - 1;
                indices.push_back(new_index);
                vertex_map[v] = new_index;
            }
        }

        Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertex_data.data(), vertex_data.size() * sizeof(float));
        vertexBuffer->SetLayout({
            { ShaderDataType::Float3, "vertexPosition" },
            { ShaderDataType::Float3, "vertexNormal" },
            { ShaderDataType::Float2, "vertexUV"}
        });

        Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices.data(), indices.size());

        vertexArray_->AddVertexBuffer(vertexBuffer);
        vertexArray_->SetIndexBuffer(indexBuffer);
    }

}