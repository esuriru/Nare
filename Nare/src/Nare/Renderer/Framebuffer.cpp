#include "Framebuffer.h"

#include "Nare/Renderer/Renderer.h"

namespace Nare
{
    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification &spec)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
            NR_CORE_ASSERT(false, "RendererAPI::None is currently not supported");
            return nullptr;
        // case RendererAPI::API::OpenGL: return CreateRef<OpenGLFramebuffer>(spec);
        case RendererAPI::API::OpenGL:
            return nullptr;
        }

        NR_CORE_ASSERT(false, "Framebuffer cannot be generated");
        return nullptr;
    }

}
