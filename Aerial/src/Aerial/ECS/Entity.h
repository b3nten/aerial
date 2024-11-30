#pragma once
#include "../Core/Core.h"
#include <entt/entt.hpp>
#include "../Core/UUID.h"

namespace Aerial
{

	template<typename T, typename... Args>
	struct ComponentArgs {
		std::tuple<Args...> args;

		ComponentArgs(Args&&... params) : args(std::forward<Args>(params)...) {}
	};

	template<typename T, typename... Args>
	auto Component(Args&&... args) {
		return ComponentArgs<T, std::decay_t<Args>...>(std::forward<Args>(args)...);
	}

	class AERIAL_API Entity
	{
		friend class Context;

	public:
		explicit Entity(entt::registry* registry);
		Entity(entt::registry* registry, UUID uid);
		Entity(entt::registry* registry, entt::entity entityID);
		Entity(entt::registry* registry, entt::entity entityID, UUID id);

		template<typename Component, typename... Args>
		auto SetComponent(Args&&... args)
		{
			return m_Registry->emplace_or_replace<Component>(m_EnttID, std::forward<Args>(args)...);
		}

		// lolololololololololol
		template<typename T, typename... Args>
		Entity& operator<<(const ComponentArgs<T, Args...>& comp) {
			std::apply([this](auto&&... params) {
				this->SetComponent<T>(std::forward<decltype(params)>(params)...);
			}, comp.args);
			return *this;
		}

		template <typename Component>
		auto GetComponent() const
		{
			return m_Registry->get<Component>(m_EnttID);
		}

		[[nodiscard]] auto GetComponents() const
		{
			return m_Registry->get(m_EnttID);
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

		// to string overload
		explicit operator const char*() const
		{
			return "Entity";
		}

		entt::entity m_EnttID;
		entt::registry* m_Registry;
		UUID m_ID;
	};

}
