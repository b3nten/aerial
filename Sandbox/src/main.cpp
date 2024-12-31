#include <Aerial.h>

class sandbox_app : public aerial::application
{
public:
    sandbox_app()
	{
    	AERIAL_LOG_INFO("SandboxApp created!");
    }

	~sandbox_app() override
	{
		AERIAL_LOG_INFO("SandboxApp destroyed!");
	}
};

aerial::application_settings aerial::create_application_settings()
{
	return { "Sandbox", 1280, 720 };
}

aerial::application* aerial::create_application()
{
	AERIAL_LOG_INFO("Creating SandboxApp");
    return new sandbox_app();
}

// ReSharper disable once CppUnusedIncludeDirective
#include <Aerial/Core/EntryPoint.h>
