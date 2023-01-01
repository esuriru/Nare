#include "WindowsWindow.h"

namespace Nare
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		WindowsWindow::Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		// Initialize data
		data_.Title = props.Title;
		data_.Width = props.Width;
		data_.Height = props.Height;

		if (!s_GLFWInitialized)
		{
			const int glfw_init_success = glfwInit();
				
			s_GLFWInitialized = true;
		}

	}
}
