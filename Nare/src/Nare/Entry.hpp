#pragma once

#include <iostream>

extern Nare::Application* Nare::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Nare::CreateApplication();
	std::cout << "Welcome to Nare.\n";
	app->Run();
	delete app;
}
