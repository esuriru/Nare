#pragma once
#include "nrpch.h"

// TODO: Make it all in one header to include.
#include "Nare/NareMath.h"

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

		virtual void Clear() = 0;
		virtual void SetClearColour(const Vector4& colour) = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI()
		{
			return s_API_;
		}
	private:
		static API s_API_;
	};
}