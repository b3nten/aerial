#pragma once
#include "Application.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cmath>
#include "Aerial/Core/Profiler.h"

inline extern aerial::application_settings aerial::create_application_settings();
inline extern aerial::application* aerial::create_application();

SDL_AppResult SDL_Fail()
{
	AERIAL_LOG_ERROR("Error %s", SDL_GetError());
	return SDL_APP_FAILURE;
}

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	aerial::application_settings settings = aerial::create_application_settings();

	// init the library, here we make a window so we only need the Video capabilities.
	if (not SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD))
	{
		return SDL_Fail();
	}

	// create a window
	SDL_Window* window = SDL_CreateWindow(settings.name.c_str(), settings.width, settings.height, settings.window_flags);
	if (not window)
	{
		AERIAL_LOG_ERROR("Could not create window.");
		return SDL_Fail();
	}
	aerial::application::s_sdl_window = window;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	if (not renderer)
	{
		AERIAL_LOG_ERROR("Could not create renderer.");
		return SDL_Fail();
	}
	aerial::application::s_sdl_renderer = renderer;

	if(not SDL_ShowWindow(window))
	{
		AERIAL_LOG_ERROR("Could not show window.");
		return SDL_Fail();
	}

	if (aerial::create_application() == nullptr)
	{
		AERIAL_LOG_ERROR("Could not create application.");
		return SDL_APP_FAILURE;
	}

	AERIAL_LOG_INFO("Aerial application started successfully!");
	return Aerial::application::s_sdl_app_result = SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT)
	{
		Aerial::application::s_sdl_app_result = SDL_APP_SUCCESS;
	}

	Aerial::application::events.push<Aerial::sdl_event>({ .Type = event->type, .Event = *event });

	return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void* appstate)
{
	auto time = SDL_GetTicks() / 1000.f;

	Aerial::application::Get()->update(time);

	SDL_FlushEvents(SDL_EVENT_FIRST, SDL_EVENT_LAST);

	return Aerial::application::s_sdl_app_result;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	if (Aerial::application::Get())
	{
		delete Aerial::application::Get();
		SDL_DestroyRenderer(Aerial::application::s_sdl_renderer);
		SDL_DestroyWindow(Aerial::application::s_sdl_window);
		SDL_Quit();
	}

	AERIAL_LOG_INFO("Aerial application quit successfully!");
}
