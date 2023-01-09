#pragma once

#include "Nare/Renderer/Buffer.h"

namespace Nare
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		virtual ~OpenGLVertexBuffer() override;

		virtual void Bind() const override;
		virtual void Unbind() const override;
        virtual void SetData(const void* data, uint32_t size) override;

		inline virtual const BufferLayout& GetLayout() const override
		{
			return layout_;
		}
		inline virtual void SetLayout(const BufferLayout& layout) override
		{
			layout_ = layout;
		}
	private:
		uint32_t rendererID_;
		BufferLayout layout_;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer() override;

		inline virtual uint32_t GetCount() const
		{
			return count_;
		}

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t rendererID_;
		uint32_t count_;
	};
}