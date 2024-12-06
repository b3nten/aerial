#pragma once
#include "Application.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cmath>
#include "Aerial/Core/Profiler.h"

inline extern Aerial::ApplicationSettings Aerial::CreateApplicationSettings();
inline extern Aerial::Application* Aerial::CreateApplication();

SDL_AppResult SDL_Fail()
{
	AERIAL_LOG_ERROR("Error %s", SDL_GetError());
	return SDL_APP_FAILURE;
}

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
	Aerial::ApplicationSettings settings = Aerial::CreateApplicationSettings();

	// init the library, here we make a window so we only need the Video capabilities.
	if (not SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_GAMEPAD))
	{
		return SDL_Fail();
	}

	// create a window
	SDL_Window* window = SDL_CreateWindow(settings.Name.c_str(), settings.Width, settings.Height, settings.WindowFlags);
	if (not window)
	{
		AERIAL_LOG_ERROR("Could not create window.");
		return SDL_Fail();
	}
	Aerial::Application::SDLWindow = window;

	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	if (not renderer)
	{
		AERIAL_LOG_ERROR("Could not create renderer.");
		return SDL_Fail();
	}
	Aerial::Application::SDLRenderer = renderer;

	if(not SDL_ShowWindow(window))
	{
		AERIAL_LOG_ERROR("Could not show window.");
		return SDL_Fail();
	}

	if (Aerial::CreateApplication() == nullptr)
	{
		AERIAL_LOG_ERROR("Could not create application.");
		return SDL_APP_FAILURE;
	}

	AERIAL_LOG_INFO("Aerial application started successfully!");
	return Aerial::Application::SDLAppResult = SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	if (event->type == SDL_EVENT_QUIT)
	{
		Aerial::Application::SDLAppResult = SDL_APP_SUCCESS;
	}

	Aerial::Application::Events.Push<Aerial::SDLEvent>({ .Type = event->type, .Event = *event });

	return SDL_APP_CONTINUE;
}


SDL_AppResult SDL_AppIterate(void* appstate)
{
	auto time = SDL_GetTicks() / 1000.f;

	Aerial::Application::Get()->Update(time);

	SDL_FlushEvents(SDL_EVENT_FIRST, SDL_EVENT_LAST);

	return Aerial::Application::SDLAppResult;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	if (Aerial::Application::Get())
	{
		delete Aerial::Application::Get();
		SDL_DestroyRenderer(Aerial::Application::SDLRenderer);
		SDL_DestroyWindow(Aerial::Application::SDLWindow);
		SDL_Quit();
	}

	AERIAL_LOG_INFO("Aerial application quit successfully!");
}
