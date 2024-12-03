#pragma once
#include <utility>
#include <entt/entt.hpp>
#include "./Entity.h"
#include "./System.h"
#include "../Core/UUID.h"
#include <any>
#include <typeindex>
#include <typeinfo>

namespace Aerial
{
	template <typename T>
	concept DerivedFromSystem = std::is_base_of_v<System, T>;

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

		void DestroyEntity(const Entity& entity)
		{
			m_Registry.destroy(entity.m_EnttID);
		}

		template<typename... Components>
		auto GetEntitiesByComponents()
		{
			return m_Registry.view<Components...>();
		}

		template <typename T, typename ...Args>
		auto SetSingletonComponent(Args&&... args)
		{
			m_SingletonComponents[typeid(T)] = CreateArc<T>(std::forward<Args>(args)...);
		}

		template <typename T>
		auto GetSingletonComponent()
		{
			return std::any_cast<Arc<T>>(m_SingletonComponents[typeid(T)]);
		}

		template <typename T>
		auto DeleteSingletonComponent()
		{
			m_SingletonComponents.erase(typeid(T));
		}

		void AddSystem(const Arc<System>& system)
		{
			const auto existing = GetSystem<System>();
			AERIAL_ASSERT(not existing, "System already exists in context");
			system->m_Context = this;
			m_Systems.push_back(system);
		}

		template <DerivedFromSystem T>
		Arc<T> GetSystem()
		{
			for (auto& system : m_Systems)
			{
				if (typeid(*system.get()) == typeid(T))
				{
					return std::static_pointer_cast<T>(system);
				}
			}
			return nullptr;
		}

		void RemoveSystem(const Arc<System>& system)
		{
			std::erase(m_Systems, system);
			system->OnEnd();
		}

		// optional; if not called, System::OnStart() will be called before the first System::OnUpdate()
		void Start();
		void Update();

		auto GetRegistry() { return &m_Registry; }

	private:
		entt::registry m_Registry;
		std::vector<Arc<System>> m_Systems;
		std::map<std::type_index, std::any> m_SingletonComponents;
	};

	// lolololololololololol
	inline Context& operator<<(Context& context, const Arc<System>& system)
	{
		context.AddSystem(system);
		return context;
	}
}
