#pragma once
#include <SDL3/SDL.h>

#include "../ECS/ecs_system.h"

namespace aerial::core_systems {

	class render_system : public ecs_system
	{
	public:
		render_system();
		~render_system();
	protected:
		void on_start() override;
		void on_update() override;
		void on_end() override;

		// SDL_GPUDevice m_Device;
	};

}