#include "core.hpp"

SDL_AppResult Core::Init()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	coreData.mainScale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

	if (!SDL_CreateWindowAndRenderer("SDL3 ImGui", static_cast<int>(coreData.windowWidth * coreData.mainScale),
		static_cast<int>(coreData.windowHeight * coreData.mainScale), coreData.windowFlags, &coreData.window, &coreData.renderer))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	//SDL_SetRenderVSync(appData.renderer, 1);

	imWindow = std::make_unique<GuiWindow>(coreData);
	imWindow->InitImGui();

	return SDL_APP_CONTINUE;
}

SDL_AppResult Core::Iterate()
{
	Update();
	Render();

	return SDL_APP_CONTINUE;
}

SDL_AppResult Core::ProcessEvent(SDL_Event* event)
{
	imWindow->ProcessEventsImGui(event);

	switch (event->type)
	{
	case SDL_EVENT_QUIT:

		return SDL_APP_SUCCESS;
		break;
	}

	return SDL_APP_CONTINUE;
}

void Core::Update()
{
	imWindow->UpdateImGui();
}

void Core::Render()
{
	SDL_RenderClear(coreData.renderer);



	imWindow->RenderImGui();
	
	SDL_RenderPresent(coreData.renderer);
}

void Core::Quit(SDL_AppResult result)
{
	(void)result;   //чтобы компилятор не ругался на неиспользуемую переменную

	imWindow->QuitImGui();

	SDL_DestroyRenderer(coreData.renderer);
	SDL_DestroyWindow(coreData.window);
	SDL_Quit();
}