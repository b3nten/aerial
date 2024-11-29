#pragma once
#include <utility>
#include <entt/entt.hpp>
#include "./Entity.h"
#include "./System.h"
#include "../Core/UUID.h"

namespace Aerial
{
	class AERIAL_API Context
	{
		friend class Application;

	public:
		template <typename... Components, typename... Args>
		Entity CreateEntity(Args&&... args)
		{
			auto entity = Entity(&m_Registry);
			(entity.SetComponent<Components>(std::forward<Args>(args)...), ...);
			return entity;
		}

		void DestroyEntity(const Entity& entity);

		template<typename... Components>
		auto GetEntitiesByComponents()
		{
			return m_Registry.view<Components...>();
		}

		Context* AddSystem(const Arc<System>& system)
		{
			m_Systems.push_back(system);
			return this;
		}

		void RemoveSystem(const Arc<System>& system)
		{
			std::erase(m_Systems, system);
		}

		void Create() const;
		void Update() const;

	private:
		entt::registry m_Registry;
		std::vector<Arc<System>> m_Systems;
	};

	inline Context& operator<<(Context& context, const Arc<System>& system)
	{
		return *context.AddSystem(system);
	}

}
