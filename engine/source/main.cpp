#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <memory>

#include "core.hpp"

std::unique_ptr<Core>core = std::make_unique<Core>();

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv)
{
	//Логирование запуска
	SDL_Log("Starting Application...");
	SDL_Log("Arguments: ");
	for (int i = 0; i < argc; ++i) {
		SDL_Log(argv[i]);
	}

	SDL_AppResult result = core->Init();

	return result;
};

SDL_AppResult SDL_AppIterate(void* appstate)
{
	return core->Iterate();
};

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
	return core->ProcessEvent(event);
};

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
	core->Quit(result);
	SDL_Log("Application shutdown complete.");
};