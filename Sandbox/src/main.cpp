#include <Aerial/Aerial.h>

class TestSystem : public Aerial::System
{
protected:
	void OnCreate() override
	{
		AERIAL_LOG_INFO("TestSystem created!");
	}

	void OnUpdate() override
	{
		AERIAL_LOG_DEBUG("Updating {}", 1);
	}
};

class SandboxApp final : public Aerial::Application
{
public:
    SandboxApp()
	{
    	this->m_AppContext << Aerial::CreateArc<TestSystem>();
    }

    ~SandboxApp() override = default;
};

Aerial::Application* Aerial::CreateApplication() {
	AERIAL_LOG_INFO("Creating SandboxApp");
    return new SandboxApp();
}

// ReSharper disable once CppUnusedIncludeDirective
#include <Aerial/Core/EntryPoint.h>
