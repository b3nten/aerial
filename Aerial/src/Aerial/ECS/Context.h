#pragma once
#include <any>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <entt/entt.hpp>
#include "./ecs_system.h"
#include "../Core/uuid.h"

namespace aerial
{
	template <typename T>
	concept DerivedFromSystem = std::is_base_of_v<ecs_system, T>;

	class AERIAL_API ecs_context
	{
		friend class application;

	public:

		void add_system(const arc<ecs_system>& system)
		{
			const auto existing = get_system<ecs_system>();
			AERIAL_ASSERT(not existing, "System already exists in context");
			system->m_ecs_context = this;
			m_systems_list.push_back(system);
		}
		template <DerivedFromSystem T>
		arc<T> get_system()
		{
			for (auto& system : m_systems_list)
			{
				if (typeid(*system.get()) == typeid(T))
				{
					return std::static_pointer_cast<T>(system);
				}
			}
			return nullptr;
		}
		void remove_system(const arc<ecs_system>& system)
		{
			std::erase(m_systems_list, system);
			system->on_end();
		}

		// optional; if not called, System::OnStart() will be called before the first System::OnUpdate()
		void run_systems_start();
		void run_systems_update();
		void run_systems_end();

		entt::registry* get_registry() { return &m_internal_registry; }

	private:
		entt::registry m_internal_registry;
		std::vector<arc<ecs_system>> m_systems_list;
	};

	inline ecs_context& operator<<(ecs_context& context, const arc<ecs_system>& system)
	{
		context.add_system(system);
		return context;
	}
}
