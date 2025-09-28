#include "core.hpp"

SDL_AppResult Core::Init()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	coreData.mainScale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

	coreData.window = SDL_CreateWindow("SDL3 ImGui",
									   static_cast<int>(coreData.windowWidth * coreData.mainScale),
									   static_cast<int>(coreData.windowHeight * coreData.mainScale),
									   coreData.windowFlags);
	if (!coreData.window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	coreData.renderer = SDL_CreateRenderer(coreData.window, NULL);
	if (!coreData.renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	// SDL_SetRenderVSync(coreData.renderer, 1);

	imWindow = new GuiWindow(coreData);
	imWindow->InitImGui();

	return SDL_APP_CONTINUE;
}

SDL_AppResult Core::Iterate()
{
	imWindow->IterateImGui();
	SDL_SetRenderDrawColor(coreData.renderer, 64, 64, 64, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(coreData.renderer);

	// Update();
	// Render();

	imWindow->RenderImGui();
	SDL_RenderPresent(coreData.renderer);

	return SDL_APP_CONTINUE;
}

SDL_AppResult Core::ProcessEvent(SDL_Event *event)
{
	imWindow->ProcessEventImGui(event);

	switch (event->type)
	{
	case SDL_EVENT_QUIT:
		return SDL_APP_SUCCESS;
		break;
	}

	return SDL_APP_CONTINUE;
}

Core::~Core()
{
	delete imWindow;
	SDL_DestroyRenderer(coreData.renderer);
	SDL_DestroyWindow(coreData.window);
	SDL_Log("SDL shutdown complete.");
}