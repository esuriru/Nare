#include "nrpch.h"
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
		WindowsWindow::Exit();
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

			// TODO: glfwTerminate on system shutdown
			NR_CORE_ASSERT(glfw_init_success, "Could not initialize GLFW.")
			s_GLFWInitialized = true;
		}

		gl_window_ = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), data_.Title.data(), nullptr, nullptr);

		if (!gl_window_)
			NR_CORE_FATAL("Could not create the window.");

		glfwMakeContextCurrent(gl_window_);
		glfwSetWindowUserPointer(gl_window_, &data_);
		SetVSyncEnabled(true);

	}

	void WindowsWindow::Exit()
	{
		glfwDestroyWindow(gl_window_);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(gl_window_);
	}

	void WindowsWindow::SetVSyncEnabled(bool enabled)
	{
		glfwSwapInterval(enabled);

		data_.VSyncEnabled = enabled;
	}

	bool WindowsWindow::IsVSyncEnabled() const
	{
		return data_.VSyncEnabled;
	}
}
