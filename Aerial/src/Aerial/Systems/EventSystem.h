#pragma once
#include "../Core/Core.h"
#include "../ECS/System.h"
#include <functional>

namespace Aerial
{
	struct Event
	{

	};

	struct InputEvent : Event
	{

	};

	struct KeyEvent : InputEvent
	{

	};

	struct MouseEvent : InputEvent
	{

	};
}

namespace Aerial::CoreSystems
{
	class AERIAL_API EventSystem final : public System
	{

	public:
		std::vector<Event> GetEventQueue() { return m_EventQueue; }

		void PushEvent(Event e) { m_EventQueue.push_back(e); }

		// Returns a function that can be used to remove the listener.
		template <typename T>
		std::function<void> AddEventListener(std::function<void(T)> listener)
		{

		}

	protected:
		void OnStart() override {}
		void OnPreUpdate() override {}
		void OnUpdate() override;
		void OnPostUpdate() override {}
		void OnEnd() override {}
		void FlushListeners();
		std::vector<Event> m_EventQueue;

	};
}