#pragma once
#include "nrpch.h"


namespace Nare
{
	class Shader
	{
	public:
		Shader(const std::string& vertex_file_path, const std::string& fragment_file_path);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t rendererID_;

	};
}