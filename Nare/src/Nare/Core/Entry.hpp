#pragma once

#ifdef NR_PLATFORM_WINDOWS

#include "Log.h"

extern Nare::Application* Nare::CreateApplication();

int main(int argc, char** argv)
{
	Nare::Log::Init();
	const auto app = Nare::CreateApplication();
	app->Run();
	delete app;
	Nare::Log::Exit();
}

#endif 