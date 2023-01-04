#pragma once

#include "Nare/Renderer/VertexArray.h"

namespace Nare
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		inline virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override
		{
			return vertexBuffers_;
		}
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override
		{
			return indexBuffer_;
		}

	private:
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers_;
		std::shared_ptr<IndexBuffer> indexBuffer_;

		uint32_t rendererID_;
	};
}

