#include "Application.h"

#include <glad/glad.h>
#include "Window.h"
#include "Log.h"
#include "Layer.h"

// Events
#include "Events/ApplicationEvent.h"
#include "Events/EventDispatcher.h"

namespace Nare
{
#define	BIND_EVENT_FUNC(x) (std::bind(&Application::x, this, std::placeholders::_1))

	void Application::Run() 
	{
		WindowResizeEvent e(1280, 720);

		while (running_)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (const auto& layer : layerStack_)
				layer->OnUpdate();

			window_->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));

		NR_CORE_INFO(e);

		// Backwards for loop
		for (auto it = layerStack_.end(); it != layerStack_.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack_.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		layerStack_.PushOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running_ = false;
		return true;
	}

	Application::Application()
		: window_(std::unique_ptr<Window>(Window::Create()))
		, running_(true)
	{
		window_->SetEventCallback(BIND_EVENT_FUNC(OnEvent));

		unsigned int id;
		glGenVertexArrays(1, &id);
	}

	Application::~Application()
	{

	}
}
