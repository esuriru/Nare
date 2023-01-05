#pragma once
#include "nrpch.h"

#include "Nare/Core/NareMath.h"


namespace Nare
{
	class Shader
	{
	public:
		Shader(const std::string& vertex_file_path, const std::string& fragment_file_path);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4(const std::string& name, const Matrix4x4& matrix);
	private:
		uint32_t rendererID_;

	};
}
