#include "./Context.h"

namespace aerial
{
	void ecs_context::run_systems_start()
	{
		for (auto system : m_systems_list)
		{
			system->on_start();
			system->m_has_run_on_start = true;
		}
	}

	void ecs_context::run_systems_update()
	{
		for (auto system : m_systems_list)
		{
			if (!system->m_has_run_on_start)
			{
				system->on_start();
				system->m_has_run_on_start = true;
			}
			system->on_update();
		}
	}

	void ecs_context::run_systems_end()
	{
		for (auto system : m_systems_list)
		{
			if (system->m_has_run_on_start)
			{
				system->on_end();
			}
		}
	}

}