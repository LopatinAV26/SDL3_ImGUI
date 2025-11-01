#include "core.hpp"

#include "gui.hpp"

Core::Core()
//: coreData{new CoreData}
{
}

SDL_AppResult Core::Init()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	// coreData->mainScale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

	coreData->window = SDL_CreateWindow("NDT",
										(coreData->windowWidth * coreData->mainScale),
										(coreData->windowHeight * coreData->mainScale),
										coreData->windowFlags);
	if (!coreData->window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	coreData->renderer = SDL_CreateRenderer(coreData->window, NULL); // openGL; vulkan; software
	if (!coreData->renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_Log("SDL initialized successfully.");
	coreData->driver = SDL_GetCurrentVideoDriver();

	// SDL_SetRenderVSync(coreData->renderer, SDL_RENDERER_VSYNC_ADAPTIVE);

	imWindow = std::make_unique<Gui>(coreData);
	imWindow->InitImGui();

	return SDL_APP_CONTINUE;
}

SDL_AppResult Core::Iterate()
{
	// Если окно свёрнуто или не в фокусе - приостанавливаем основной цикл
	if (coreData->isWindowMinimized || !coreData->isWindowFocused)
	{
		SDL_Delay(100); // Задержка 100мс для снижения нагрузки на CPU
		return SDL_APP_CONTINUE;
	}

	imWindow->IterateImGui();
	SDL_SetRenderDrawColor(coreData->renderer, 64, 64, 64, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(coreData->renderer);

	// Update();
	// Render();

	imWindow->RenderImGui();
	SDL_RenderPresent(coreData->renderer);

	return SDL_APP_CONTINUE;
}

SDL_AppResult Core::ProcessEvent(const SDL_Event *event)
{
	imWindow->ProcessEventImGui(event);

	switch (event->type)
	{
	case SDL_EVENT_QUIT:
		return SDL_APP_SUCCESS;

	case SDL_EVENT_WINDOW_MINIMIZED:
		coreData->isWindowMinimized = true;
		break;

	case SDL_EVENT_WINDOW_RESTORED:
		coreData->isWindowMinimized = false;
		break;

	case SDL_EVENT_WINDOW_FOCUS_GAINED:
		coreData->isWindowFocused = true;
		break;

	case SDL_EVENT_WINDOW_FOCUS_LOST:
		coreData->isWindowFocused = false;
		break;
	}

	return SDL_APP_CONTINUE;
}

Core::~Core()
{
	// imWindow.reset();
	SDL_DestroyRenderer(coreData->renderer);
	SDL_DestroyWindow(coreData->window);
	delete coreData;
	coreData = nullptr;
	SDL_Log("SDL shutdown complete.");
}