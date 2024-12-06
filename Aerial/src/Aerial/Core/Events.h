#pragma once
#include "Core.h"
#include <functional>
#include <variant>
#include "Memory.h"

using namespace Aerial::NumberExtensions;

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
		EventQueue() = default;
		EventQueue(const EventQueue&) = delete;
		EventQueue(EventQueue&&) = delete;
		EventQueue& operator=(const EventQueue&) = delete;

		template <typename Event>
		void Listen(std::function<void(Event&)>&& handler)
		{

		}

		template <typename Event>
		void Listen(Arc<std::function<void(Event&)>> handler)
		{

		}

		template <typename T, typename ...Args>
		void Push(Args&& ...args)
        {
			T* event = m_Arena.Make<T>(std::forward<Args>(args)...);
			eventQueue.push_back({ typeid(T).hash_code(), event });
        }

		template <typename T>
		void Push(const T& event)
		{
			T* e = m_Arena.Make<T>(event);
			eventQueue.push_back({ typeid(T).hash_code(), e });
		}

		template <typename T>
		void Push(T&& event)
		{
			T* e = m_Arena.Make<T>(std::forward<T>(event));
			eventQueue.push_back({ typeid(T).hash_code(), e });
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
			eventQueue.clear();
			m_Arena.Clear();
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

		BumpAlloc m_Arena = BumpAlloc(100_KiB);
		std::deque<EventEntry> eventQueue;
		std::unordered_map<size_t, std::list<HandlerEntry>> listeners;
		size_t nextHandlerId = 0;
	};
}
