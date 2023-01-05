#pragma once

#include "Nare/Renderer/Texture.h"

namespace Nare
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		inline virtual uint32_t GetWidth() const override
		{
			return width_;
		}

		inline virtual uint32_t GetHeight() const override
		{
			return height_;
		}

		virtual void Bind(uint32_t slot) const override;

	private:
		std::string path_;
		uint32_t width_, height_;

		uint32_t rendererID_;
	};
}