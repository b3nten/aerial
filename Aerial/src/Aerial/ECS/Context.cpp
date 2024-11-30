#include "./Context.h"

namespace Aerial
{
	void Context::DestroyEntity(const Entity& entity)
	{
		m_Registry.destroy(entity.m_EnttID);
	}

	void Context::Create()
	{
		for (auto system : m_Systems)
		{
			system->OnCreate();
		}
	}

	void Context::Update()
	{
		for (auto system : m_Systems)
		{
			system->OnUpdate();
		}
	}
}