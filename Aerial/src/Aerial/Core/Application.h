#pragma once
#include "./Core.h"
#include "./FrameDelta.h"
#include "../ECS/Context.h"
#include <SDL3/SDL.h>

#include "Events.h"

namespace aerial {

	struct application_settings {
		std::string name = "Aerial";
		int width = 1280;
		int height = 720;
		SDL_WindowFlags window_flags = SDL_WINDOW_RESIZABLE;
	};

	class AERIAL_API application {
	public:
		static application* Get() { return s_instance; }
		inline static event_queue events;
		inline static SDL_Renderer* s_sdl_renderer;
		inline static SDL_Window* s_sdl_window;
		inline static SDL_AppResult s_sdl_app_result;

		application();
		virtual ~application();
		application(const application&) = delete;
		application& operator=(const application&) = delete;

		void update(float deltaTime);
		[[nodiscard]] FrameDelta get_frame_delta() const { return m_frame_delta; }

	protected:
		inline static application* s_instance;

		bool m_running = false;
		ecs_context m_app_context;
		FrameDelta m_frame_delta;
	};

	// Userland functions
	application_settings create_application_settings();
	application* create_application();
}
