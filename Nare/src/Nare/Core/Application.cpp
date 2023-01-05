#include "Application.h"

#include "Window.h"
#include "Log.h"
#include "Layer.h"
#include "Nare/Platform/OpenGL/OpenGLBuffer.h"
#include "Nare/Renderer/Renderer.h"
#include "Nare/Core/Timestep.h"
#include "Nare/Core/Core.h"

// Events
#include "Nare/Events/ApplicationEvent.h"
#include "Nare/Events/EventDispatcher.h"

#include "Input.h"
#include "GLFW/glfw3.h"

namespace Nare
{

#define	BIND_EVENT_FUNC(fn) std::bind(&Application::fn, this, std::placeholders::_1)

	Application* Application::s_instance_ = nullptr;

	Application::Application()
		: window_(std::unique_ptr<Window>(Window::Create()))
		, running_(true)
	{
		NR_CORE_ASSERT(!s_instance_, "Application already exists!")
		s_instance_ = this;

		window_->SetEventCallback(BIND_EVENT_FUNC(OnEvent));
		window_->SetVSyncEnabled(false);

	}

	void Application::Run() 
	{
		// Runtime loop
		while (running_)
		{
			// TODO: to change into a time class
			const auto& time = static_cast<float>(glfwGetTime());
			const Timestep timestep = time - lastTime_;
			lastTime_ = time;


			for (const auto& layer : layerStack_)
				layer->OnUpdate(timestep);

			window_->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));

		//NR_CORE_INFO(e);

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


	Application::~Application()
	{

	}
}
