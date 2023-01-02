#pragma once

#ifdef NR_PLATFORM_WINDOWS

#include "Log.h"

extern Nare::Application* Nare::CreateApplication();

int main(int argc, char** argv)
{
	Nare::Log::Init();
	auto app = Nare::CreateApplication();
	app->Run();
	delete app;
}

#endif 
