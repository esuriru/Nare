#pragma once
#include "RendererAPI.h"
#include "Nare/Mathf/Vector4.h"

namespace Nare
{
	class RenderCommand
	{
	public:

#pragma region INLINE_FUNCTIONS
		inline static void SetClearColour(const Vector4& colour)
		{
			s_rendererAPI_->SetClearColour(colour);
		}

		inline static void Clear()
		{
			s_rendererAPI_->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_rendererAPI_->DrawIndexed(vertexArray);
		}
#pragma endregion INLINE_FUNCTIONS

	private:
		static RendererAPI* s_rendererAPI_;
	};
}