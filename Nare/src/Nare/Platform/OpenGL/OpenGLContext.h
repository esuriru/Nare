#pragma once
#include "Nare/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Nare
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* windowHandle_;
		
	};
}
