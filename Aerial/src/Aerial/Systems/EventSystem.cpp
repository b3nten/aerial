#include "EventSystem.h"
#include "../Core/Application.h"

namespace Aerial::CoreSystems
{
	Arc<std::vector<SDL_Event>> GetSDLEventQueue()
	{
		SDL_PumpEvents();
		int count = SDL_PeepEvents(NULL, INT_MAX, SDL_PEEKEVENT, SDL_EVENT_FIRST, SDL_EVENT_LAST);
		if (count <= 0) return CreateArc<std::vector<SDL_Event>>(0);
		auto events = CreateArc<std::vector<SDL_Event>>(count);
		SDL_PeepEvents(events->data(), count, SDL_PEEKEVENT, SDL_EVENT_FIRST, SDL_EVENT_LAST);
		return events;
	}

	void EventSystem::OnUpdate()
	{
		SDL_PumpEvents();

		int count = SDL_PeepEvents(NULL, INT_MAX, SDL_PEEKEVENT, SDL_EVENT_FIRST, SDL_EVENT_LAST);
		if (count <= 0) return;

		std::vector<SDL_Event> events(count);

		SDL_PeepEvents(events.data(), count, SDL_PEEKEVENT, SDL_EVENT_FIRST, SDL_EVENT_LAST);

		for (int i = 0; i < count; i++)
		{
			SDL_Event* e = &events[i];

			if (e->type == SDL_EVENT_QUIT)
			{
				Application::SDLAppResult = SDL_APP_SUCCESS;
			}
			else
			{
				// create event and add to event queue;
				if (e->type != 1024) AERIAL_LOG_INFO("EventSystem::OnUpdate() - Event type: %d", e->type);
			}

			// flush callbacks
			FlushListeners();
		}
	}

	void EventSystem::FlushListeners()
	{

	}
}