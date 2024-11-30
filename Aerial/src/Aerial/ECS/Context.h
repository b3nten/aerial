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

		void AddSystem(const Arc<System>& system)
		{
			m_Systems.push_back(system);
		}

		void RemoveSystem(const Arc<System>& system)
		{
			std::erase(m_Systems, system);
		}

		void Create();
		void Update();

		auto GetRegistry() { return &m_Registry; }

	private:
		entt::registry m_Registry;
		std::vector<Arc<System>> m_Systems;
	};

	// lolololololololololol
	inline Context& operator<<(Context& context, const Arc<System>& system)
	{
		context.AddSystem(system);
		return context;
	}
}
