#include "nrpch.h"
#include "Application.h"

#include "Log.h"
#include "Events/ApplicationEvent.h"

namespace Nare
{
	void Application::Run() 
	{
		WindowResizeEvent e(1280, 720);
		NR_CORE_TRACE("Trace");
		NR_CORE_INFO("Info");
		NR_CORE_WARN("Warn");
		NR_CORE_ERROR("Error");
		NR_CORE_FATAL("Fatal");
		while (true)
		{
		}
	}

	Application::Application()
	{

	}

	Application::~Application()
	{

	}
	
}
