#pragma once

#include "Nare/Renderer/Buffer.h"

namespace Nare
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;
	private:
		uint32_t rendererID_;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		inline virtual uint32_t GetCount() const
		{
			return count_;
		}

		virtual void Bind() const;
		virtual void Unbind() const;
	private:
		uint32_t rendererID_;
		uint32_t count_;
	};
}