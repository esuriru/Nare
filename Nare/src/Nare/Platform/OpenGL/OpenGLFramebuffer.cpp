#include "nrpch.h"
#include "OpenGLFramebuffer.h"

#include "glad/glad.h"

namespace Nare
{
    OpenGLFrameBuffer::OpenGLFrameBuffer(const FramebufferSpecification &spec)
        : spec_(spec)
    {
        Invalidate();
    }
    void OpenGLFrameBuffer::Invalidate()
    {
        glCreateFramebuffers(1, &rendererID_);

        glCreateTextures(GL_TEXTURE_2D, 1, &colorAttachment_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, spec_.Width, spec_.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr); 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
}
