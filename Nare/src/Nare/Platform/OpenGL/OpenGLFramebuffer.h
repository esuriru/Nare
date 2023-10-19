#pragma once

#include "Nare/Renderer/Framebuffer.h"

namespace Nare
{
    class OpenGLFrameBuffer : public Framebuffer
    {
    public:
        OpenGLFrameBuffer(const FramebufferSpecification& spec);
        virtual ~OpenGLFrameBuffer();

        inline virtual const FramebufferSpecification& GetSpecification() const override
        {
            return spec_;
        }

        void Invalidate();

    private:
        uint32_t rendererID_;
        uint32_t colorAttachment_, depthAttachment_;

        FramebufferSpecification spec_;
    };
}