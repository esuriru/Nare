#include <Nare.h>

class TestLayer : public Nare::Layer
{
public:
	TestLayer()
		: Layer("Test")
	{}

	void OnUpdate() override
	{
		//NR_CLIENT_INFO("Test Layer");
		if (Nare::Input::GetKeyDown(NR_KEY_TAB))
			NR_CLIENT_INFO("Tab key is pressed!");

	}

	void OnEvent(Nare::Event& event) override
	{
		if (event.GetEventType() == Nare::EventType::KeyPressed)
		{
			Nare::KeyPressedEvent& e = dynamic_cast<Nare::KeyPressedEvent&>(event);
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

Nare::Application* Nare::CreateApplication()
{
	return new Launcher();
}

