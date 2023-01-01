#include "Application.h"
#include "Window.h"

#include "Log.h"
#include "Events/ApplicationEvent.h"

namespace Nare
{
	void Application::Run() 
	{
		WindowResizeEvent e(1280, 720);
		int a = 2;
		NR_CORE_ERROR("sting", "test");
		NR_CORE_INFO(e);
		while (running_)
		{
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
