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
        , minimized_(false)
	{
		NR_CORE_ASSERT(!s_instance_, "Application already exists!")
		s_instance_ = this;

		Renderer::Init();

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


            if (!minimized_)
            {
                for (const auto& layer : layerStack_)
                    layer->OnUpdate(timestep);
            }

			window_->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(OnWindowResize));

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

    bool Application::OnWindowResize(WindowResizeEvent &e)
    {
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            minimized_ = true;
            return false;
        }

        minimized_ = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        return true;
    }

    Application::~Application()
	{

	}
}
