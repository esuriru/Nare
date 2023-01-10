#include "nrpch.h"
#include "OpenGLBuffer.h"

#include <GLAD/glad.h>


namespace Nare
{
#pragma region VERTEX_BUFFER
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &rendererID_);
		glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLint>(size), vertices, GL_STATIC_DRAW);
	}

    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
    {
		glCreateBuffers(1, &rendererID_);
		glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
		glBufferData(GL_ARRAY_BUFFER, static_cast<GLint>(size), nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &rendererID_);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

    void OpenGLVertexBuffer::SetData(const void *data, uint32_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

#pragma endregion VERTEX_BUFFER

#pragma region INDEX_BUFFER

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: count_(count)
	{
		glCreateBuffers(1, &rendererID_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLint>(count * sizeof(uint32_t)), indices, GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &rendererID_);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
#pragma endregion INDEX_BUFFER
}
