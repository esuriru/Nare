#pragma once

#include <glad/glad.h>
#include "Nare/Renderer/Texture.h"

namespace Nare
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();

        virtual void SetData(void* data, uint32_t size) override;

		inline virtual uint32_t GetWidth() const override
		{
			return width_;
		}

		inline virtual uint32_t GetHeight() const override
		{
			return height_;
		}

		virtual void Bind(uint32_t slot) const override;
        
        inline virtual bool operator==(const Texture& other) const override
        {
            return rendererID_ == dynamic_cast<const OpenGLTexture2D&>(other).rendererID_;
        }

	private:
		std::string path_;
		uint32_t width_, height_;

		uint32_t rendererID_;
        GLenum internalFormat_, dataFormat_;
	};
}