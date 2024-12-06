#pragma once
#include "./Core.h"
#include "./FrameDelta.h"
#include "../ECS/Context.h"
#include <SDL3/SDL.h>

#include "Events.h"

namespace Aerial
{
	struct ApplicationSettings
	{
		std::string Name = "Aerial";
		int Width = 1280;
		int Height = 720;
		SDL_WindowFlags WindowFlags = SDL_WINDOW_RESIZABLE;
	};

	class AERIAL_API Application
	{
	public:
		static Application* Get() { return s_Instance; }
		inline static EventQueue Events;
		inline static SDL_Renderer* SDLRenderer;
		inline static SDL_Window* SDLWindow;
		inline static SDL_AppResult SDLAppResult;

		Application();
		virtual ~Application();
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		void Update(float deltaTime);
		[[nodiscard]] FrameDelta GetFrameDelta() const { return m_FrameDelta; }
	protected:
		inline static Application *s_Instance;

		bool m_Running = false;
		Context m_AppContext;
		FrameDelta m_FrameDelta;
	};

	// Userland functions
	ApplicationSettings CreateApplicationSettings();
	Application* CreateApplication();
}
