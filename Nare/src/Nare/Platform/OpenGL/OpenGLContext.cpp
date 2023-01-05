#include "nrpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <GLAD/glad.h>

#include "Nare/Core/Core.h"

namespace Nare
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: windowHandle_(windowHandle)
	{
		NR_CORE_ASSERT(windowHandle, "Window handle is null. Could not create context.");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(windowHandle_);
		const int glad_init_success = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		NR_CORE_ASSERT(glad_init_success, "Could not initialize GLAD.");

		NR_CORE_INFO("OpenGL Info: ");
		NR_CORE_INFO("	Vendor: ", glGetString(GL_VENDOR));
		NR_CORE_INFO("	Renderer: ", glGetString(GL_RENDERER));
		NR_CORE_INFO("	Version: ", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(windowHandle_);
	}
	
}
