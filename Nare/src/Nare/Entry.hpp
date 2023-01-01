#pragma once

#ifdef NR_PLATFORM_WINDOWS

#include <iostream>

extern Nare::Application* Nare::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Nare::CreateApplication();
	app->Run();
	delete app;
}

#endif 
