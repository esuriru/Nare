#pragma once
#include "Nare/Scene/Coordinator.h"
#include "LayerStack.h"
#include "nrpch.h"

#include "Nare/Events/Event.h"
#include "Nare/Events/KeyEvent.h"
#include "Nare/Events/MouseEvent.h"
#include "Nare/Events/ApplicationEvent.h"
#include "Nare/Renderer/Buffer.h"

#include "Nare/Renderer/Shader.h"
#include "Nare/Renderer/VertexArray.h"

/**
 * \brief Engine core namespace
 */
namespace Nare
{
	class Layer;
	class WindowCloseEvent;
	class Window;

	/**
	 * \brief Application created that uses the engine.
	 */
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

#pragma region INLINE_FUNCTIONS
		inline static Application& Instance()
		{
			return *s_instance_;
		}

		inline Window& GetWindow()
		{
			return *window_;
		}
#pragma endregion INLINE_FUNCTIONS
		

#pragma region LAYER_STACK

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		//void PopLayer(Layer* layer);
		//void PopOverlay(Layer* overlay);

#pragma endregion LAYER_STACK
	private:
		bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> window_;
		bool running_;
		LayerStack layerStack_;

        bool minimized_;

		float lastTime_{};


	protected:
		static Application* s_instance_;

	};

	// To be defined in client application
	Application* CreateApplication();
}

