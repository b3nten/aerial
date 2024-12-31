#pragma once
#include "Core.h"
#include <functional>
#include <variant>
#include "Memory.h"

using namespace aerial::number_ext;

namespace aerial
{
	struct sdl_event
	{
		Uint32 Type;
        SDL_Event Event;
	};

	class event_queue
	{

	public:
		event_queue() = default;
		event_queue(const event_queue&) = delete;
		event_queue(event_queue&&) = delete;
		event_queue& operator=(const event_queue&) = delete;

		template <typename Event>
		void listen(std::function<void(Event&)>&& handler)
		{

		}

		template <typename Event>
		void listen(arc<std::function<void(Event&)>> handler)
		{

		}

		template <typename T, typename ...Args>
		void push(Args&& ...args)
        {
			T* event = m_arena.make<T>(std::forward<Args>(args)...);
			m_event_queue.push_back({ typeid(T).hash_code(), event });
        }

		template <typename T>
		void push(const T& event)
		{
			T* e = m_arena.make<T>(event);
			m_event_queue.push_back({ typeid(T).hash_code(), e });
		}

		template <typename T>
		void push(T&& event)
		{
			T* e = m_arena.make<T>(std::forward<T>(event));
			m_event_queue.push_back({ typeid(T).hash_code(), e });
		}

		void dispatch_listeners()
		{
			AERIAL_PROFILE_FUNC;

			for (event_entry& e : m_event_queue)
            {
				for (auto& handlers = m_listeners[e.type]; auto& [func, _] : handlers)
                {

                }
            }
		}

		void clear_queue()
		{
			m_event_queue.clear();
			m_arena.clear();
		}

	private:

		struct handler_entry
		{
			void* func;
			size_t id;
		};

		struct event_entry
		{
			size_t type;
			void* event;
		};

		bump_alloc m_arena = bump_alloc(100_KiB);
		std::deque<event_entry> m_event_queue;
		std::unordered_map<size_t, std::list<handler_entry>> m_listeners;
		size_t m_next_handler_id = 0;
	};
}
