#include <Aerial/Aerial.h>

struct Vec2
{
	float x,y;
};

struct Material
{
	std::string color;
};

struct Texture
{
	std::string path;
};

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
    	auto WindowSystem = Aerial::CreateArc<TestSystem>();
    	auto InputSystem = Aerial::CreateArc<TestSystem>();
    	auto RenderSystem = Aerial::CreateArc<TestSystem>();
    	auto PhysicsSystem = Aerial::CreateArc<TestSystem>();

    	this->m_AppContext
    		<< WindowSystem
    		<< InputSystem
    		<< RenderSystem
    		<< PhysicsSystem;

    	const auto ent = this->m_AppContext.CreateEntity()
    		<< Aerial::Component<Vec2>(1.0f, 2.0f)
    		<< Aerial::Component<Material>("#fff")
			<< Aerial::Component<Texture>("path/to/texture.png");

		AERIAL_LOG_DEBUG(static_cast<const char*>(ent));
    }

    ~SandboxApp() override = default;
};

Aerial::Application* Aerial::CreateApplication() {
	AERIAL_LOG_INFO("Creating SandboxApp");
    return new SandboxApp();
}

// ReSharper disable once CppUnusedIncludeDirective
#include <Aerial/Core/EntryPoint.h>
