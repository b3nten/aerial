#include <Aerial.h>

class SandboxApp : public Aerial::Application
{
public:
    SandboxApp()
	{
    	AERIAL_LOG_INFO("SandboxApp created!");
    }

	~SandboxApp() override
	{
		AERIAL_LOG_INFO("SandboxApp destroyed!");
	}
};

Aerial::ApplicationSettings Aerial::CreateApplicationSettings()
{
	return { "Sandbox", 1280, 720 };
}

Aerial::Application* Aerial::CreateApplication()
{
	AERIAL_LOG_INFO("Creating SandboxApp");
    return new SandboxApp();
}

// ReSharper disable once CppUnusedIncludeDirective
#include <Aerial/Core/EntryPoint.h>
