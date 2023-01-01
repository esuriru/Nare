#pragma once
#include "nrpch.h"

/**
 * \brief Engine core namespace
 */
namespace Nare
{
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
	private:
		std::unique_ptr<Window> window_;
		bool running_;
	};

	// To be defined in client application
	Application* CreateApplication();
}

