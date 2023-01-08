#pragma once
#include "nrpch.h"

// TODO: Make it all in one header to include.
#include "Nare/Core/Core.h"
#include "Nare/Core/NareMath.h"

namespace Nare
{
	class VertexArray;

	class RendererAPI
	{
	public:
		enum class API 
		{
			None = 0,
			OpenGL
		};
		virtual void Init() = 0;

		virtual void Clear() = 0;
		virtual void SetClearColour(const Vector4& colour) = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		inline static API GetAPI()
		{
			return s_API_;
		}
	private:
		static API s_API_;
	};
}