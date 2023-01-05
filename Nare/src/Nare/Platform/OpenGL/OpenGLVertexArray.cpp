#include "OpenGLVertexArray.h"
#include <GLAD/glad.h>

namespace Nare
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::None:		break;
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Mat3:		return GL_FLOAT;
			case ShaderDataType::Mat4:		return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Bool:		return GL_BOOL;
		}

		NR_CORE_ASSERT(false, "Unknown ShaderDataType.")
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
		: rendererID_(0)
	{
		glCreateVertexArrays(1, &rendererID_);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &rendererID_);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(rendererID_);
		indexBuffer->Bind();

		indexBuffer_ = indexBuffer;
	}


	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		NR_CORE_ASSERT(!vertexBuffer->GetLayout().GetElements().empty(), "Vertex buffer has no layout elements.")

		glBindVertexArray(rendererID_);
		vertexBuffer->Bind();

		uint32_t layout_index = 0;
		const auto& layout = vertexBuffer->GetLayout();

		for (const auto& element : layout) 
		{
			glEnableVertexAttribArray(layout_index);
			glVertexAttribPointer(layout_index,
				static_cast<GLint>(element.GetComponentCount()),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				static_cast<GLint>(layout.GetStride()),
				reinterpret_cast<const void*>(element.Offset));  // NOLINT(performance-no-int-to-ptr)
			++layout_index;
		}

		vertexBuffers_.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(rendererID_);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
}