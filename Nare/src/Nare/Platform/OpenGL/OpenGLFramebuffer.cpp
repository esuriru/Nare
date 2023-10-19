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

    OpenGLFrameBuffer::~OpenGLFrameBuffer()
    {
        glDeleteFramebuffers(1, &rendererID_);
    }

    void OpenGLFrameBuffer::Invalidate()
    {
        glCreateFramebuffers(1, &rendererID_);
        glBindFramebuffer(GL_FRAMEBUFFER, rendererID_);

        glCreateTextures(GL_TEXTURE_2D, 1, &colorAttachment_);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, spec_.Width, spec_.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr); 

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachment_, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &depthAttachment_);
        glBindTexture(GL_TEXTURE_2D, depthAttachment_);
        glTexStorage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, spec_.Width, spec_.Height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthAttachment_, 0);

        NR_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");


        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
