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
	}

	void OnEvent(Nare::Event& event) override
	{
		NR_CLIENT_TRACE(event);
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

