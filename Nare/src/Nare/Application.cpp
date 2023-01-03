#include "Application.h"

#include <glad/glad.h>
#include "Window.h"
#include "Log.h"
#include "Layer.h"
#include "Nare/Platform/OpenGL/OpenGLBuffer.h"

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
		NR_CORE_ASSERT(!s_instance_, "Application already exists!");
		s_instance_ = this;

		window_->SetEventCallback(BIND_EVENT_FUNC(OnEvent));

		glGenVertexArrays(1, &vertexArray_);
		glBindVertexArray(vertexArray_);


		// For testing
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		vertexBuffer_.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
	
		// Vertices
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);


		unsigned int indices[3] = { 0, 1, 2 };
		indexBuffer_.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 vertexPosition;

			out vec3 vPos;

			void main()
			{
				gl_Position = vec4(vertexPosition, 1.0);
				vPos = vertexPosition;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 vPos;

			void main()
			{
				color = vec4(vPos * 0.5 + 0.5, 1.0);
				
			}
		)";


		shader_.reset(new Shader(vertexSrc, fragmentSrc));


	}

	void Application::Run() 
	{
		// Runtime loop
		while (running_)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			shader_->Bind();
			glBindVertexArray(vertexArray_);
			glDrawElements(GL_TRIANGLES, static_cast<int>(indexBuffer_->GetCount()), GL_UNSIGNED_INT, nullptr);

			for (const auto& layer : layerStack_)
				layer->OnUpdate();

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
