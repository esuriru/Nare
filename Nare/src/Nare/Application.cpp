#include "Application.h"

#include <glad/glad.h>
#include "Window.h"
#include "Log.h"
#include "Layer.h"

// Events
#include "Events/ApplicationEvent.h"
#include "Events/EventDispatcher.h"

#include "Input.h"

namespace Nare
{
	Application* Nare::Application::s_instance_ = nullptr;

#define	BIND_EVENT_FUNC(x) (std::bind(&Application::x, this, std::placeholders::_1))

	Application::Application()
		: window_(std::unique_ptr<Window>(Window::Create()))
		, running_(true)
	{
		window_->SetEventCallback(BIND_EVENT_FUNC(OnEvent));
		s_instance_ = this;

		glGenVertexArrays(1, &vertexArray_);
		glBindVertexArray(vertexArray_);

		glGenBuffers(1, &vertexBuffer_);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer_);

		// For testing
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Vertices
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &indexBuffer_);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer_);

		unsigned int indices[3] = { 0, 1, 2 };

		//glEnableVertexAttribArray(1);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//glDisableVertexAttribArray(0);

	}

	void Application::Run() 
	{
		// WindowResizeEvent e(1280, 720);

		// Runtime loop
		while (running_)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(vertexArray_);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (const auto& layer : layerStack_)
				layer->OnUpdate();

			//const Vector2& mousePos = Input::GetMousePosition();
			//NR_CORE_TRACE(mousePos);


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
