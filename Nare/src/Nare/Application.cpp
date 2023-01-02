#include "Application.h"
#include <GLFW/glfw3.h>
#include "Window.h"

#include "Log.h"
#include "Events/ApplicationEvent.h"

namespace Nare
{
	void Application::Run() 
	{
		WindowResizeEvent e(1280, 720);

		while (running_)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window_->OnUpdate();
		}
	}

	Application::Application()
		: window_(std::unique_ptr<Window>(Window::Create()))
		, running_(true)
	{

	}

	Application::~Application()
	{

	}
	
}
