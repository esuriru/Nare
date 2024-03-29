#pragma once

#include "Nare/Core/Core.h"

namespace Nare
{
    struct FramebufferSpecification
    {
        uint32_t Width, Height;

        uint32_t Samples = 1;

        bool SwapChainTarget = false;
    };

    class Framebuffer
    {
    public:
        virtual const FramebufferSpecification& GetSpecification() const = 0;
        static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
    };
}