#include <Nare.h>
#include <Nare/Core/Entry.hpp>

#include "Launcher2D.h"

namespace Nare
{
	class LauncherLayer : public Layer
	{
	public:
		LauncherLayer()
			: Layer("Test")
		{
			vertexArray_ = VertexArray::Create();

			// For testing
			float vertices[21] = {
				-0.5f, -0.5f, 0.0f, 1.0f, 0.f, 1.0f, 1.0f,
				0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				0.0f, 0.5f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f
			};

			Ref<VertexBuffer> vb(VertexBuffer::Create(vertices, sizeof(vertices)));

			const BufferLayout layout = {
				{ ShaderDataType::Float3, "vertexPosition" },
				{ ShaderDataType::Float4, "vertexColour" }
			};

			vb->SetLayout(layout);
			vertexArray_->AddVertexBuffer(vb);

			std::vector<uint32_t> indices = { 0, 1, 2 };
			Ref<IndexBuffer> ib(IndexBuffer::Create(indices.data(), indices.size()));
			vertexArray_->SetIndexBuffer(ib);

			std::vector<float> square_vertices = {
				-0.75f, -0.75f, 0.0f, 0.f, 0.f,
				0.75f, -0.75f, 0.0f, 1.0f, 0.f,
				0.75f, 0.75f, 0.0f, 1.0f, 1.0f,
				-0.75f, 0.75f, 0.0f, 0.f, 1.0f
			};

            squareVertexArray_ = VertexArray::Create();

			Ref<VertexBuffer> squareVB(VertexBuffer::Create(square_vertices.data(), square_vertices.size() * sizeof(float)));
			const BufferLayout squareLayout = {
				{ ShaderDataType::Float3, "vertexPosition" },
				{ ShaderDataType::Float2, "vertexTexCoords" }
			};

			squareVB->SetLayout(squareLayout);
			squareVertexArray_->AddVertexBuffer(squareVB);

			std::vector<uint32_t> square_indices = {
				0, 1, 2,
				2, 3, 0
			};

			Ref<IndexBuffer> squareIB(IndexBuffer::Create(square_indices.data(), square_indices.size() * sizeof(float)));
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

			std::string textureVertexSrc = R"(
				#version 330 core

				layout(location = 0) in vec3 vertexPosition;
				layout(location = 1) in vec2 vertexTexCoords;

				out vec3 vPos;
				out vec2 texCoords;

				void main()
				{
					gl_Position = vec4(vertexPosition, 1.0);
					vPos = vertexPosition;
					texCoords = vertexTexCoords;
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

			std::string textureFragmentSrc = R"(
				#version 330 core

				layout(location = 0) out vec4 color;

				in vec2 texCoords;

				uniform sampler2D texture_;

				void main()
				{
					color = texture(texture_, texCoords).rgba;
				}
			)";

            auto textureShader = shaderLib_.Load("assets/shaders/Texture.glsl");



			texture_ = Texture2D::Create(R"(C:\Users\User\Pictures\kassadin.jpg)");
			png_texture_ = Texture2D::Create(R"(C:\Users\User\Downloads\logopng.png)");

			std::dynamic_pointer_cast<OpenGLShader>(textureShader)->Bind();
			std::dynamic_pointer_cast<OpenGLShader>(textureShader)->UploadUniformInt("texture_", 0);
		}

		inline void OnUpdate(Timestep ts) override
		{
			RenderCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();


            auto textureShader = shaderLib_.Get("Texture");
			texture_->Bind();
			Renderer::Submit(squareVertexArray_, textureShader);

			png_texture_->Bind();
			Renderer::Submit(squareVertexArray_, textureShader);

			//Renderer::Submit(vertexArray_, shader_);

			Renderer::EndScene();
		}

		inline void OnEvent(Event& event) override
		{
			EventDispatcher dispatcher(event);
			dispatcher.Dispatch<KeyPressedEvent>(NR_BIND_EVENT_FUNC(LauncherLayer::OnKeyPressedEvent));

            if (event.GetEventType() == EventType::WindowResize)
            {
                auto& re = dynamic_cast<WindowResizeEvent&>(event);

            }
		}

		inline bool OnKeyPressedEvent(KeyPressedEvent& event)
		{
			if (event.GetKeyCode() == NR_KEY_LEFT)
			{
				NR_CLIENT_WARN("Left has been pressed");
			}

			return false;
		}
	private:
		// TODO: Shaders (to be asset files)

        ShaderLibrary shaderLib_;

		// TODO: Vertex Arrays, maybe to be in a list.
		Ref<VertexArray> vertexArray_;
		Ref<VertexArray> squareVertexArray_;

		Ref<Texture2D> texture_;
		Ref<Texture2D> png_texture_;
	};

	class Launcher : public Nare::Application
	{
	public:
		Launcher()
		{
			// PushLayer(new LauncherLayer());
            PushLayer(new Launcher2D());
		}
		virtual ~Launcher() = default;
	};

	Application* Nare::CreateApplication()
	{
		return new Launcher();
	}
}
