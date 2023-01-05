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

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		inline virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override
		{
			return vertexBuffers_;
		}
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override
		{
			return indexBuffer_;
		}

	private:
		std::vector<Ref<VertexBuffer>> vertexBuffers_;
		Ref<IndexBuffer> indexBuffer_;

		uint32_t rendererID_;
	};
}

