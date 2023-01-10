#pragma once
#include "RendererAPI.h"
#include "Nare/Core/Core.h"
#include "Nare/Mathf/Vector4.h"

namespace Nare
{
	class RenderCommand
	{
	public:
#pragma region INLINE_FUNCTIONS
		inline static void Init()
		{
			s_rendererAPI_->Init();
		}

		inline static void SetClearColour(const Vector4& colour)
		{
			s_rendererAPI_->SetClearColour(colour);
		}

		inline static void Clear()
		{
			s_rendererAPI_->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
		{
			s_rendererAPI_->DrawIndexed(vertexArray, indexCount);
		}

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            s_rendererAPI_->SetViewport(x, y, width, height);
        }
#pragma endregion INLINE_FUNCTIONS

	private:
		static Scope<RendererAPI> s_rendererAPI_;
	};
}