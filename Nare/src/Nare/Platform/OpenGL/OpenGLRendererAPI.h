#pragma once
#include "Nare/Core/Core.h"
#include "Nare/Renderer/RendererAPI.h"
#include "Nare/Core/NareMath.h"

namespace Nare
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void Clear() override;
		virtual void SetClearColour(const Vector4& colour) override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		
	};

}
