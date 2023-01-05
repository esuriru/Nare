#pragma once
#include "Nare/Renderer/RendererAPI.h"
#include "Nare/Core/NareMath.h"

namespace Nare
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Clear() override;
		virtual void SetClearColour(const Vector4& colour) override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
		
	};

}
