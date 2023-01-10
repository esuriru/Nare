#pragma once

#include "Nare/Core/Core.h"
#include "Nare/Core/NareMath.h"

namespace Nare
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

        virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& name, const std::string& vertex_file_path, const std::string& fragment_file_path);
		static Ref<Shader> Create(const std::string& file_path);

        virtual void SetMat4(const std::string& name, const Matrix4x4& mat) = 0;

        virtual void SetFloat(const std::string& name, const float& val) = 0;
        virtual void SetFloat2(const std::string& name, const Vector2& vec) = 0;
        virtual void SetFloat3(const std::string& name, const Vector3& vec) = 0;
        virtual void SetFloat4(const std::string& name, const Vector4& vec) = 0;

        virtual void SetInt(const std::string& name, const int& val) = 0;
        virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
        // virtual void SetInt2(const Vector2& vec) = 0;
        // virtual void SetInt3(const Vector3& vec) = 0;
        // virtual void SetInt4(const Vector4& vec) = 0;
	};
}
