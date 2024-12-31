#pragma once
#include "../Core/Core.h"
#include "./ecs_system.h"

namespace aerial
{
	class AERIAL_API ecs_system
	{
		friend class ecs_context;
	public:
		ecs_system() = default;
		virtual ~ecs_system() = default;

	protected:
		virtual void on_start(){}
		virtual void on_update(){}
		virtual void on_end(){}
		ecs_context* m_ecs_context;

	private:
		bool m_has_run_on_start = false;
	};
}
