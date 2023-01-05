#pragma once

namespace Nare
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Shader* Create(const std::string& vertex_file_path, const std::string& fragment_file_path);

	};
}
