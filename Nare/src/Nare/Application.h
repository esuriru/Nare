#pragma once

/**
 * \brief Engine core namespace
 */
namespace Nare
{
	/**
	 * \brief Application created that uses the engine.
	 */
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	};

	// To be defined in client application
	Application* CreateApplication();
}

