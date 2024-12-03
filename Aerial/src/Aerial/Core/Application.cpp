#include "./Application.h"

#include "Profiler.h"
#include "../Systems/EventSystem.h"
#include "../Systems/InputSystem.h"
#include "../Systems/AssetSystem.h"

namespace Aerial
{
	Application::Application()
	{
		AERIAL_ASSERT(s_Instance == nullptr, "You cannot create more than one application!");

		s_Instance = this;

		// Add core application level systems;
		auto coreEventSystem = CreateArc<CoreSystems::EventSystem>();
		auto coreInputSystem = CreateArc<CoreSystems::InputSystem>();
		auto coreAssetSystem = CreateArc<CoreSystems::AssetSystem>();

		this->m_AppContext << coreEventSystem << coreInputSystem << coreAssetSystem;
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
