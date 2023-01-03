#include "nrpch.h"
#include "WindowsInput.h"
#include "Nare/Window.h"

#include <GLFW/glfw3.h>
#include "Nare/Application.h"

namespace Nare
{
	Input* Input::s_instance_ = new WindowsInput();
#define GET_APP_WINDOW static_cast<GLFWwindow*>(Application::Instance().GetWindow().GetNativeWindow());

	bool WindowsInput::get_key_down_(int keycode) 
	{
		auto window = GET_APP_WINDOW;
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::get_mouse_button_down_(int button)
	{
		auto window = GET_APP_WINDOW;
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	Vector2 WindowsInput::get_mouse_position_()
	{
		auto window = GET_APP_WINDOW;
		// TODO: I feel like this is more expensive than it should be. Creating more buffers than I should;

		// Mouse position buffer
		double x = 0, y = 0;
		glfwGetCursorPos(window, &x, &y);

		// Casting to float is done in the constructor
		return { x, y };
	}

}