#pragma once

#include "Nare/Renderer/Shader.h"
#include "Nare/Core/NareMath.h"

// TODO: REMOVE
typedef unsigned int GLenum;


namespace Nare
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertex_source, const std::string& fragment_source);
		OpenGLShader(const std::string& file_path);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

        virtual const std::string& GetName() const override
        {
            return name_;
        }


		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const Vector2& vec);
		void UploadUniformFloat3(const std::string& name, const Vector3& vec);
		void UploadUniformFloat4(const std::string& name, const Vector4& vec);

		void UploadUniformMat4(const std::string& name, const Matrix4x4& vec);


	private:
		uint32_t rendererID_;

        std::string name_;

		std::string ReadFile(const std::string& file_path);

		// TODO: Make this a typedef
		std::unordered_map<GLenum, std::string> Preprocess(const std::string& source);

		static std::vector<std::string> s_validShaderTypes_;
		void Compile(std::unordered_map<GLenum, std::string> shaderSources);

	};

    class ShaderLibrary
    {
    public:
        void Add(const Ref<Shader>& shader);
        void Add(const std::string& name, const Ref<Shader>& shader);

        Ref<Shader> Load(const std::string& name, const std::string& filepath);
        Ref<Shader> Load(const std::string& filepath);

        Ref<Shader> Get(const std::string& name);

        bool Exists(const std::string& name) const;
    private:
        std::unordered_map<std::string, Ref<Shader>> shaders_;
    };

}
