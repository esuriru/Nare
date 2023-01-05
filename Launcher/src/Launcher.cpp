#include <Nare.h>

namespace Nare
{
	class TestLayer : public Layer
	{
	public:
		TestLayer()
			: Layer("Test")
		{}

		void OnUpdate(Timestep ts) override
		{
			//NR_CLIENT_INFO("Test Layer");
			NR_CLIENT_TRACE("Delta time: ", ts.GetSeconds(), " (", ts.GetMilliseconds(), " ms)");
			if (Nare::Input::GetKeyDown(NR_KEY_TAB))
				NR_CLIENT_INFO("Tab key is pressed!");
		}

		void OnEvent(Event& event) override
		{
			if (event.GetEventType() == EventType::KeyPressed)
			{
				auto& e = dynamic_cast<KeyPressedEvent&>(event);
				NR_CLIENT_TRACE("Key pressed: ", static_cast<char>(e.GetKeyCode()));
			}
		}
	};

	class Launcher : public Nare::Application
	{
	public:
		Launcher()
		{
			PushLayer(new TestLayer());
		}
		virtual ~Launcher() = default;
	};

	Application* Nare::CreateApplication()
	{
		return new Launcher();
	}
}
