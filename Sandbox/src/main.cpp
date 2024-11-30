#include <Aerial/Aerial.h>

class SandboxApp final : public Aerial::Application
{
public:
    SandboxApp()
	{
    	AERIAL_LOG_INFO("SandboxApp created!");
    }

	~SandboxApp()
	{
		AERIAL_LOG_INFO("SandboxApp destroyed!");
	}
};

Aerial::ApplicationSettings Aerial::CreateApplicationSettings()
{
	return ApplicationSettings("Aerial Sandbox", 1280, 720, SDL_WINDOW_FULLSCREEN);
}

Aerial::Application* Aerial::CreateApplication()
{
	AERIAL_LOG_INFO("Creating SandboxApp");
    return new SandboxApp();
}

// ReSharper disable once CppUnusedIncludeDirective
#include <Aerial/Core/EntryPoint.h>
