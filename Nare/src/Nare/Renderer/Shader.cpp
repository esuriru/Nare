#pragma once
#include "Shader.h"
#include <GLAD/glad.h>

#include "Nare/Core/Core.h"
#include "Nare/Core/Log.h"

namespace Nare
{
	Shader::Shader(const std::string& vertex_file_path, const std::string& fragment_file_path)
		: rendererID_(NULL)
	{
		// Create the vertex shader
		GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = vertex_file_path.data();

		// Get the code from the file
		glShaderSource(vertShader, 1, &source, nullptr);

		// Compile the shader
		glCompileShader(vertShader);

		GLint isCompiled = 0;
		// Get its compilation status
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			// If not compiled, create a buffer to store the log.
			GLint maxLength = 0;
			glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorInfoLog(maxLength);
			// Send the data from the log into the buffer
			glGetShaderInfoLog(vertShader, maxLength, &maxLength, errorInfoLog.data());

			glDeleteShader(vertShader);

			NR_CORE_ERROR(errorInfoLog.data());
			NR_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		// Create the fragment shader
		GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = fragment_file_path.data();

		// Get the code from the file
		glShaderSource(fragShader, 1, &source, nullptr);

		// Compile the shader
		glCompileShader(fragShader);

		// Get its compilation status
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			// If not compiled, create a buffer to store the log.
			GLint maxLength = 0;
			glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorInfoLog(maxLength);
			// Send the data from the log into the buffer
			glGetShaderInfoLog(fragShader, maxLength, &maxLength, errorInfoLog.data());

			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			NR_CORE_ERROR(errorInfoLog.data());
			NR_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		// Create the program that the fragment and vertex shader into
		rendererID_ = glCreateProgram();
		GLuint program = rendererID_;

		// Attach the shaders
		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);

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

			glDeleteShader(vertShader);
			glDeleteShader(fragShader);

			NR_CORE_ERROR(errorInfoLog.data());
			NR_CORE_ASSERT(false, "Shader linking failure!");
			return;
		}

		// Detach shader after linking
		glDetachShader(program, vertShader);
		glDetachShader(program, fragShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(rendererID_);
	}

	void Shader::Bind() const
	{
		glUseProgram(rendererID_);
	}

	void Shader::Unbind() const
	{
		glUseProgram(NULL);
	}

	void Shader::UploadUniformMat4(const std::string& name, const Matrix4x4& matrix)
	{
		const auto& location = glGetUniformLocation(rendererID_, name.data());
		// TODO: GL_TRUE for row-major, GL_FALSE for column-major
		glUniformMatrix4fv(location, 1, GL_FALSE, matrix.data());
	}
}
