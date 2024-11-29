#pragma once
#include "../Core/Core.h"
#include <entt/entt.hpp>
#include "../Core/UUID.h"

namespace Aerial
{
	class AERIAL_API Entity
	{
		friend class Context;

		explicit Entity(entt::registry* registry);
		Entity(entt::registry* registry, UUID uid);
		Entity(entt::registry* registry, entt::entity entityID);
		Entity(entt::registry* registry, entt::entity entityID, UUID id);

		template<typename Component, typename... Args>
		auto SetComponent(Args&&... args)
		{
			return m_Registry->emplace_or_replace<Component>(m_EnttID, std::forward<Args>(args)...);
		}

		template <typename Component>
		auto GetComponent() const
		{
			return m_Registry->get<Component>(m_EnttID);
		}

		template <typename Component>
		[[nodiscard]] bool HasComponent() const
		{
			auto component =  m_Registry->try_get<Component>();
			return component != nullptr;
		}

		template <typename Component>
		void RemoveComponent() const
		{
			m_Registry->remove<Component>(m_EnttID);
		}

		entt::entity m_EnttID;
		entt::registry* m_Registry;
		UUID m_ID;
	};
}
