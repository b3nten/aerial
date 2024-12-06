#include "./Application.h"

#include "Profiler.h"
#include "../Systems/InputSystem.h"
#include "../Systems/AssetSystem.h"
#include "./Events.h"
#include "./LinkedList.h"

namespace Aerial
{
	Application::Application()
	{
		AERIAL_ASSERT(s_Instance == nullptr, "You cannot create more than one application!");

		s_Instance = this;

		// Add core application level systems;
		auto coreInputSystem = CreateArc<CoreSystems::InputSystem>();
		auto coreAssetSystem = CreateArc<CoreSystems::AssetSystem>();

		Events.Listen<SDLEvent>([](auto& e)
		{
			AERIAL_LOG_INFO("lambda %d", e.Event.type);
		});

		auto handler = CreateArc<std::function<void(SDLEvent&)>>([](auto& e)
		{
			AERIAL_LOG_INFO("handler %d", e.Event.type);
		});
		Events.Listen<SDLEvent>(handler);

		this->m_AppContext << coreInputSystem << coreAssetSystem;
	}

	Application::~Application()
	{
		s_Instance = nullptr;
	}

	void Application::Update(float deltaTime)
	{
		AERIAL_PROFILE_FUNC;
		this->m_FrameDelta = FrameDelta(deltaTime);
		m_AppContext.Update();
	}
}
