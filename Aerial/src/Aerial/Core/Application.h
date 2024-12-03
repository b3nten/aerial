#pragma once
#include "./Core.h"
#include "./FrameDelta.h"
#include "../ECS/Context.h"
#include <SDL3/SDL.h>

namespace Aerial
{
	struct ApplicationSettings
	{
		std::string Name = "Aerial";
		int Width = 1280;
		int Height = 720;
		SDL_WindowFlags WindowFlags = SDL_WINDOW_RESIZABLE;
	};

	// Allows systems to access the underlying SDL context
	struct SDLContext
	{
		SDL_Window* Window = nullptr;
		SDL_Renderer* Renderer = nullptr;
		void** AppState = nullptr;
	};

	class AERIAL_API Application
	{
	public:
		static void SetSDLContext(SDLContext ctx) { m_SDLContext = ctx; }
		static SDLContext GetSDLContext() { return m_SDLContext; }
		static Application* Get() { return s_Instance; }

		Application();
		virtual ~Application();
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		void Update(float deltaTime);
		[[nodiscard]] FrameDelta GetFrameDelta() const { return m_FrameDelta; }

		inline static SDL_Renderer* SDLRenderer;
		inline static SDL_Window* SDLWindow;
		inline static SDL_AppResult SDLAppResult;

	protected:
		inline static Application *s_Instance;
		inline static SDLContext m_SDLContext;

		bool m_Running = false;
		Context m_AppContext;
		FrameDelta m_FrameDelta;
	};

	// Userland functions
	ApplicationSettings CreateApplicationSettings();
	Application* CreateApplication();
}
