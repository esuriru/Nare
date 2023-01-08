#include "OpenGLShader.h"

#include <GLAD/glad.h>

#include "Nare/Core/Core.h"
#include "Nare/Core/Log.h"
#include "Nare/Utils/Utility.h"

namespace Nare
{
	// TODO: Maybe add geometry shader?
	std::vector<std::string> OpenGLShader::s_validShaderTypes_ = {
		"vertex",
		"pixel",
		"fragment"
	};

	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

		NR_CORE_ASSERT(false, "Unknown shader type.");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertex_source, const std::string& fragment_source)
		: rendererID_(NULL)
        , name_(name)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertex_source;
		sources[GL_FRAGMENT_SHADER] = fragment_source;
		Compile(sources);
	}

	OpenGLShader::OpenGLShader(const std::string& file_path)
		: rendererID_(NULL)
	{
		const auto& shaderSource = ReadFile(file_path);
		auto shaderSources = Preprocess(shaderSource);

		Compile(shaderSources);

        // Extract name from filepath

        // e.g Texture.glsl
        auto lastSlash = file_path.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;

        auto lastDot = file_path.rfind('.');
        auto count = lastDot == std::string::npos ? file_path.size() - lastSlash : lastDot - lastSlash;

        name_ = file_path.substr(lastSlash, count);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(rendererID_);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(rendererID_);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(NULL);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		const auto& location = glGetUniformLocation(rendererID_, name.data());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		const auto& location = glGetUniformLocation(rendererID_, name.data());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const Vector2& vec)
	{
		const auto& location = glGetUniformLocation(rendererID_, name.data());
		glUniform2fv(location, 1, vec.data());
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const Vector3& vec)
	{
		const auto& location = glGetUniformLocation(rendererID_, name.data());
		glUniform3fv(location, 1, vec.data());
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const Matrix4x4& matrix)
	{
		const auto& location = glGetUniformLocation(rendererID_, name.data());
		// TODO: GL_TRUE for row-major, GL_FALSE for column-major
		glUniformMatrix4fv(location, 1, GL_FALSE, matrix.data());
	}

	void OpenGLShader::Compile(std::unordered_map<GLenum, std::string> shaderSources)
	{
		// Create the program that the fragment and vertex shader into
		GLuint program = glCreateProgram();
        NR_CORE_ASSERT(shaderSources.size() <= 2, "Nare only supports a maximum of 2 shaders for now.")
        std::array<GLenum, 2> shaderIDs;
        int shaderIDindex = 0;


		for (auto& kv_pair : shaderSources)
		{
			GLenum type = kv_pair.first;
			const std::string& source = kv_pair.second;

			// Create the shader
			GLuint shader = glCreateShader(type);

			const GLchar* source_data = source.data();

			// Set shader source
			glShaderSource(shader, 1, &source_data, nullptr);

			// Compile
			glCompileShader(shader);

			GLint isCompiled = 0;

			// Retrieve compilation status
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				// If not compiled, create a buffer to store the log.
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> errorInfoLog(maxLength);
				// Send the data from the log into the buffer
				glGetShaderInfoLog(shader, maxLength, &maxLength, errorInfoLog.data());

				glDeleteShader(shader);

				glDeleteProgram(program);

				NR_CORE_ERROR(errorInfoLog.data());

				// TODO: Add which specific shader failed compiling
				NR_CORE_ASSERT(false, "Shader compilation failure!")
				return;
			}
			// Attach the compiled shader
			glAttachShader(program, shader);
            shaderIDs[shaderIDindex++] = shader;
		}

		rendererID_ = program;

		// Link the program
		glLinkProgram(program);

		// Get its linked status
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			// If not linked, create a buffer to store the log.
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorInfoLog(maxLength);
			// Send the data from the log into the buffer
			glGetProgramInfoLog(program, maxLength, &maxLength, errorInfoLog.data());

			// Avoid memory leaks
			glDeleteProgram(program);

			for (auto& id : shaderIDs)
				glDeleteShader(id);

			NR_CORE_ERROR(errorInfoLog.data());
			NR_CORE_ASSERT(false, "OpenGLShader linking failure!")
			return;
		}

		// Detach shader after linking
		for (auto& id : shaderIDs)
			glDetachShader(program, id);
	}

	std::string OpenGLShader::ReadFile(const std::string& file_path)
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

	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* token = "#type";
		const size_t tokenLength = strlen(token);
		size_t pos = source.find(token, 0);

		while (pos != std::string::npos)
		{
			const size_t endOfLine = source.find_first_of("\r\n", pos);
			NR_CORE_ASSERT(endOfLine != std::string::npos, "Syntax error");
			const size_t begin = pos + tokenLength + 1; // Get the number of characters after #type declaration
			const std::string type = source.substr(begin, endOfLine - begin);

			NR_CORE_ASSERT(Utility::Contains(s_validShaderTypes_, type), "Invalid shader type specification")

			const size_t nextLinePos = source.find_first_not_of("\r\n", endOfLine);
			pos = source.find(token, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] =
				source.substr(nextLinePos,
					pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));

		}

		return shaderSources;
	}


	void OpenGLShader::UploadUniformFloat4(const std::string& name, const Vector4& vec)
	{
		const auto& location = glGetUniformLocation(rendererID_, name.data());
		glUniform4fv(location, 1, vec.data());
	}

    void ShaderLibrary::Add(const Ref<Shader> &shader)
    {
        auto& name = shader->GetName();
        Add(name, shader);
    }

    void ShaderLibrary::Add(const std::string &name, const Ref<Shader> &shader)
    {
        NR_CORE_ASSERT(!Exists(name), "Shader already exists.");
        shaders_[name] = shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string &name, const std::string &filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string &filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Get(const std::string &name)
    {
        // TODO: Should not be fatal
        NR_CORE_ASSERT(Exists(name), "Shader not found.");
        return shaders_[name];
    }

    bool ShaderLibrary::Exists(const std::string &name) const
    {
        return shaders_.find(name) != shaders_.end();
    }
}
