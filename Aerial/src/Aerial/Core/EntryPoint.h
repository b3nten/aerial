#pragma once
#include "Application.h"

inline extern Aerial::Application* Aerial::CreateApplication();

inline int main(int argc, char** argv)
{
	const auto app = Aerial::CreateApplication();
	app->Run();
	delete app;
}
