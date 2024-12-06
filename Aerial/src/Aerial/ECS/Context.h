#pragma once
#include <any>
#include <typeindex>
#include <typeinfo>
#include <utility>
#include <entt/entt.hpp>
#include "./System.h"
#include "../Core/UUID.h"

namespace Aerial
{
	template <typename T>
	concept DerivedFromSystem = std::is_base_of_v<System, T>;

	class AERIAL_API Context
	{
		friend class Application;

	public:

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
		void End();

		entt::registry* GetRegistry() { return &m_Registry; }

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
