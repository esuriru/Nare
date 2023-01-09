#include "nrpch.h"
#include "WindowsWindow.h"

#include "Nare/Events/ApplicationEvent.h"
#include "Nare/Events/MouseEvent.h"
#include "Nare/Events/KeyEvent.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

#include "Nare/Core/Log.h"

namespace Nare
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* desc)
	{
		NR_CORE_ERROR("GLFW Error: (", error, "): {", desc, "}");
	}

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

		NR_CORE_INFO("Creating window ", props.Title, "(", props.Width, ", ", props.Height, ")");


		if (!s_GLFWInitialized)
		{
			const int glfw_init_success = glfwInit();

			// TODO: glfwTerminate on system shutdown
			NR_CORE_ASSERT(glfw_init_success, "Could not initialize GLFW.")
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		window_ = glfwCreateWindow(static_cast<int>(props.Width), static_cast<int>(props.Height), data_.Title.data(), nullptr, nullptr);

		context_ = new OpenGLContext(window_);
		context_->Init();

		if (!window_)
			NR_CORE_FATAL("Could not create the window.");

		glfwSetWindowUserPointer(window_, &data_);
		SetVSyncEnabled(true);

#pragma region GLFW_CALLBACKS
		glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);

			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(window_, [](GLFWwindow* window)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(window_, [](GLFWwindow* window, double x_offset, double y_offset)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseScrolledEvent event({ static_cast<float>(x_offset), static_cast<float>(y_offset) });
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double x_pos, double y_pos)
		{
			WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			MouseMovedEvent event({ static_cast<float>(x_pos), static_cast<float>(y_pos) });
			data.EventCallback(event);
		});
#pragma endregion GLFW_CALLBACKS
	}

	void WindowsWindow::Exit()
	{
		glfwDestroyWindow(window_);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window_);
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
