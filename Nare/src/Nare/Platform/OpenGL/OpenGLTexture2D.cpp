#include "nrpch.h"
#include "OpenGLTexture2D.h"

#include <stb_image.h>

#include <GLAD/glad.h>

namespace Nare
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: rendererID_(0)
	{
		// Create buffers
		int width, height, channels;

		// Flip the image
		stbi_set_flip_vertically_on_load(1);
		const auto& data = stbi_load(path.data(), &width, &height, &channels, 0);
		// TODO: Might not want to make it fatal
		NR_CORE_ASSERT(data, "Failed to load image!");

		width_ = width;
		height_ = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

        internalFormat_ = internalFormat;
        dataFormat_ = dataFormat;

		NR_CORE_ASSERT(internalFormat & dataFormat, "Format not supported")

        // TODO - need to read up more on what this does: apparently, STB_image does not perform any kind of alignment
        // https://stackoverflow.com/questions/23150123/loading-png-with-stb-image-for-opengl-texture-gives-wrong-colors
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID_);
		glTextureStorage2D(rendererID_, 1, internalFormat, static_cast<GLint>(width_), static_cast<GLint>(height_));

		glTextureParameteri(rendererID_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererID_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
		glTextureParameteri(rendererID_, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(rendererID_, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(rendererID_, 0, 0, 0, static_cast<GLint>(width_), static_cast<GLint>(height_), dataFormat, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : width_(width), height_(height)
    {
        internalFormat_ = GL_RGBA8;
        dataFormat_ = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID_);
		glTextureStorage2D(rendererID_, 1, internalFormat_, static_cast<GLint>(width_), static_cast<GLint>(height_));

		glTextureParameteri(rendererID_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererID_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(rendererID_, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(rendererID_, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &rendererID_);
	}

    void OpenGLTexture2D::SetData(void *data, uint32_t size)
    {
#ifdef NR_ENABLE_ASSERTS
        uint32_t bytes_per_channel = dataFormat_ == GL_RGBA ? 4 : 3;
#endif
        NR_CORE_ASSERT(size == width_ * height_ * bytes_per_channel, "Data must be the entire texture.");
		glTextureSubImage2D(rendererID_, 0, 0, 0, static_cast<GLint>(width_), static_cast<GLint>(height_), dataFormat_, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, rendererID_);
	}
}
