#pragma once
#include "./Core.h"
#include "../ECS/Context.h"
#include <SDL3/SDL.h>

namespace Aerial
{
	static Application* s_Instance = nullptr;

	struct ApplicationSettings
	{
		std::string Name = "Aerial Application";
		int Width = 1280;
		int Height = 720;
		SDL_WindowFlags WindowFlags = SDL_WINDOW_RESIZABLE;
	};

	class AERIAL_API Application
	{
	public:
		Application() { s_Instance = this; }
		~Application() { s_Instance = nullptr; }

		static Application* Get() { return s_Instance; }

		int Init(SDL_Window* window, SDL_Renderer* renderer);

		void Update(float deltaTime)
		{
			this->m_FrameDelta = FrameDelta(deltaTime);
			m_AppContext.Update();
		}

		[[nodiscard]] FrameDelta GetFrameDelta() const { return m_FrameDelta; }

	protected:
		bool m_Running = false;
		Context m_AppContext;
		FrameDelta m_FrameDelta;
	};

	ApplicationSettings CreateApplicationSettings();
	Application* CreateApplication();
}
