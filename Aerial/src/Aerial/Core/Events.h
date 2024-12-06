#pragma once
#include "Core.h"
#include <functional>
#include <variant>

namespace Aerial
{
	struct SDLEvent
	{
		Uint32 Type;
        SDL_Event Event;
	};

	class EventQueue
	{

	public:

		template <typename Event>
		void Listen(std::function<void(Event&)>&& handler)
		{

		}

		template <typename Event>
		void Listen(Arc<std::function<void(Event&)>> handler)
		{

		}

		template <typename T>
		void Push(T&& e)
        {

        }

		void DispatchListeners()
		{
			AERIAL_PROFILE_FUNC;

			for (EventEntry& e : eventQueue)
            {
				for (auto& handlers = listeners[e.type]; auto& [func, _] : handlers)
                {

                }
            }
		}

		void ClearQueue()
		{
			// clear bumpalloc
		}

	private:
		struct HandlerEntry
		{
			void* func;
			size_t id;
		};

		struct EventEntry
		{
			size_t type;
			void* event;
		};

		std::deque<EventEntry> eventQueue;
		std::unordered_map<size_t, std::list<HandlerEntry>> listeners;
		size_t nextHandlerId = 0;
	};
}
