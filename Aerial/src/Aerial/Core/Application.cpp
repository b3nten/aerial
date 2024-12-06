#include "./Application.h"
#include "Profiler.h"
#include "../Systems/InputSystem.h"
#include "../Systems/RenderSystem.h"
#include "./Events.h"

namespace Aerial
{
	Application::Application()
	{
		AERIAL_ASSERT(s_Instance == nullptr, "You cannot create more than one application!");
		s_Instance = this;

		m_AppContext << CreateArc<CoreSystems::RenderSystem>();
	}

	Application::~Application()
	{
		s_Instance = nullptr;
	}

	void Application::Update(const float deltaTime)
	{
		AERIAL_PROFILE_FUNC;

		// Set the frame delta time;
		this->m_FrameDelta = FrameDelta(deltaTime);

		// Dispatch listeners in the event queue;
		Events.DispatchListeners();

		// Update systems;
		m_AppContext.Update();

		// Clear the event queue and associated memory;
		Events.ClearQueue();
	}
}
