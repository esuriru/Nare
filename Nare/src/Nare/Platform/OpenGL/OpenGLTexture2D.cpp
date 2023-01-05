#include "nrpch.h"
#include "OpenGLTexture2D.h"

#include <stb_image.h>

#include <GLAD/glad.h>

namespace Nare
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: rendererID_(0)
	{
		int width, height, channels;

		// Flip the image
		stbi_set_flip_vertically_on_load(1);
		const auto& data = stbi_load(path.data(), &width, &height, &channels, 0);
		// TODO: Might not want to make it fatal
		NR_CORE_ASSERT(data, "Failed to load image!");

		width_ = width;
		height_ = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &rendererID_);
		glTextureStorage2D(rendererID_, 1, GL_RGB8, static_cast<GLint>(width_), static_cast<GLint>(height_));

		glTextureParameteri(rendererID_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(rendererID_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(rendererID_, 0, 0, 0, static_cast<GLint>(width_), static_cast<GLint>(height_), GL_RGB, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &rendererID_);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, rendererID_);
	}
}