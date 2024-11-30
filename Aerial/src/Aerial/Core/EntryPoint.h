#pragma once
#define SDL_MAIN_USE_CALLBACKS
#include "Application.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cmath>

inline extern Aerial::ApplicationSettings Aerial::CreateApplicationSettings();
inline extern Aerial::Application* Aerial::CreateApplication();

struct AppContext
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_AppResult app_quit = SDL_APP_CONTINUE;
	Aerial::Application* aerialApplication;
};

SDL_AppResult SDL_Fail()
{
	AERIAL_LOG_ERROR("Error %s", SDL_GetError());
	return SDL_APP_FAILURE;
}

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{

	Aerial::ApplicationSettings settings = Aerial::CreateApplicationSettings();

	// init the library, here we make a window so we only need the Video capabilities.
	if (not SDL_Init(SDL_INIT_VIDEO))
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

	SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
	if (not renderer)
	{
		AERIAL_LOG_ERROR("Could not create renderer.");
		return SDL_Fail();
	}

	bool windowShown = SDL_ShowWindow(window);
	if(!windowShown)
	{
		AERIAL_LOG_ERROR("Could not show window");
		return SDL_Fail();
	}

	// initialize our application, setting up application systems here;
	Aerial::Application* app = Aerial::CreateApplication();

	// set up the application data
	*appstate = new AppContext{
		window,
		renderer,
		SDL_APP_CONTINUE,
		app,
	};

	AERIAL_LOG_INFO("Aerial application started successfully!");

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	auto* app = (AppContext*)appstate;

	if (event->type == SDL_EVENT_QUIT)
	{
		app->app_quit = SDL_APP_SUCCESS;
	}

	// dispatch event to application;

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
	auto* app = (AppContext*)appstate;

	// draw a color
	auto time = SDL_GetTicks() / 1000.f;
	auto red = (std::sin(time) + 1) / 2.0 * 255;
	auto green = (std::sin(time / 2) + 1) / 2.0 * 255;
	auto blue = (std::sin(time) * 2 + 1) / 2.0 * 255;

	SDL_SetRenderDrawColor(app->renderer, red, green, blue, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(app->renderer);
	SDL_RenderPresent(app->renderer);

	app->aerialApplication->Update(time);

	return app->app_quit;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	auto* app = (AppContext*)appstate;
	if (app)
	{
		delete app->aerialApplication;
		SDL_DestroyRenderer(app->renderer);
		SDL_DestroyWindow(app->window);
		delete app;
	}

	AERIAL_LOG_INFO("Aerial application quit successfully!");
}
