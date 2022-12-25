#include <Nare.h>

class Launcher : public Nare::Application
{
public:
	Launcher() = default;
	virtual ~Launcher() = default;
};

Nare::Application* Nare::CreateApplication()
{
	return new Launcher();
}

