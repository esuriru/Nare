#pragma once

namespace Nare
{
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

