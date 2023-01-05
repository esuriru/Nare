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

		vertexArray_.reset(VertexArray::Create());

		// For testing
		float vertices[21] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vb(VertexBuffer::Create(vertices, sizeof(vertices)));

		coordinator_.reset(Coordinator::Instance());

		const BufferLayout layout = {
			{ ShaderDataType::Float3, "vertexPosition" },
			{ ShaderDataType::Float4, "vertexColour" }
		};

		vb->SetLayout(layout);
		vertexArray_->AddVertexBuffer(vb);

		std::vector<uint32_t> indices = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> ib(IndexBuffer::Create(indices.data(), indices.size()));
		vertexArray_->SetIndexBuffer(ib);

		std::vector<float> square_vertices = {
			-0.75f, -0.75f, 0.0f, 
			0.75f, -0.75f, 0.0f, 
			0.75f, 0.75f, 0.0f,
			-0.75f, 0.75f, 0.0f,
		};

		squareVertexArray_.reset(VertexArray::Create());

		std::shared_ptr<VertexBuffer> squareVB(VertexBuffer::Create(square_vertices.data(), square_vertices.size() * sizeof(float)));
		const BufferLayout squareLayout = {
			{ ShaderDataType::Float3, "vertexPosition" }
		};

		squareVB->SetLayout(squareLayout);
		squareVertexArray_->AddVertexBuffer(squareVB);

		std::vector<uint32_t> square_indices = {
			0, 1, 2,
			2, 3, 0
		};

		std::shared_ptr<IndexBuffer> squareIB(IndexBuffer::Create(square_indices.data(), square_indices.size() * sizeof(float)));
		squareVertexArray_->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 vertexPosition;
			layout(location = 1) in vec4 vertexColour;

			out vec3 vPos;
			out vec4 fragColour;

			void main()
			{
				gl_Position = vec4(vertexPosition, 1.0);
				vPos = vertexPosition;
				fragColour = vertexColour;
			}
		)";

		std::string rainbowVertexSrc = R"(
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
			in vec4 fragColour;

			void main()
			{
				//color = vec4(vPos * 0.5 + 0.5, 1.0);
				color = fragColour;
			}
		)";

		std::string rainbowFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 vPos;

			void main()
			{
				color = vec4(vPos * 0.5 + 0.5, 1.0);
			}
		)";


		shader_.reset(new Shader(vertexSrc, fragmentSrc));
		rainbowShader_.reset(new Shader(rainbowVertexSrc, rainbowFragmentSrc));
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

			RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			rainbowShader_->Bind();
			Renderer::Submit(squareVertexArray_);

			shader_->Bind();
			Renderer::Submit(vertexArray_);

			Renderer::EndScene();

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
