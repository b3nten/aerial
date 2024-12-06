#include "./Context.h"

namespace Aerial
{
	void Context::Start()
	{
		for (auto system : m_Systems)
		{
			system->OnStart();
			system->m_HasRunOnStart = true;
		}
	}

	void Context::Update()
	{
		for (auto system : m_Systems)
		{
			if (!system->m_HasRunOnStart)
			{
				system->OnStart();
				system->m_HasRunOnStart = true;
			}
			system->OnUpdate();
		}
	}

	void Context::End()
	{
		for (auto system : m_Systems)
		{
			if (system->m_HasRunOnStart)
			{
				system->OnEnd();
			}
		}
	}

}