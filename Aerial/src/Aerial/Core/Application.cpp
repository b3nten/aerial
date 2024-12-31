#include "./Application.h"
#include "Profiler.h"
#include "../Systems/RenderSystem.h"
#include "./Events.h"

namespace aerial
{
	application::application()
	{
		AERIAL_ASSERT(s_instance == nullptr, "You cannot create more than one application!");
		s_instance = this;
		m_app_context << make_arc<core_systems::render_system>();
	}

	application::~application()
	{
		s_instance = nullptr;
	}

	void application::update(const float deltaTime)
	{
		AERIAL_PROFILE_FUNC;

		// Set the frame delta time;
		this->m_frame_delta = FrameDelta(deltaTime);

		// Dispatch m_listeners in the event queue;
		events.dispatch_listeners();

		// update systems;
		m_app_context.run_systems_update();

		// Clear the event queue and associated memory;
		events.clear_queue();
	}
}
