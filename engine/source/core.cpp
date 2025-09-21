#include "core.hpp"

SDL_Window *Core::mainWindow{};
SDL_Renderer* Core::renderer{};

SDL_AppResult Core::Init()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /* mainWindow = SDL_CreateWindow("SDL3 Window", mainWindowWidth, mainWindowHeight, mainWindowFlags);
    if (!mainWindow)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    renderer = SDL_CreateRenderer(mainWindow, NULL);
    if (!renderer)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error %s", SDL_GetError());
        return SDL_APP_FAILURE;
    } */

    if(!SDL_CreateWindowAndRenderer("SDL3 ImGui", mainWindowWidth, mainWindowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY, &mainWindow, &renderer)){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    //SDL_SetRenderVSync(renderer, 1);

    imWindow.InitImGui();

    return SDL_APP_CONTINUE;
}

SDL_AppResult Core::Iterate()
{
    Update();
    Render();

    return SDL_APP_CONTINUE;
}

SDL_AppResult Core::ProcessEvent(SDL_Event *event)
{
    imWindow.ProcessEventsImGui(event);

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
    imWindow.UpdateImGui();
}

void Core::Render()
{
    SDL_RenderClear(renderer);

    

    imWindow.RenderImGui();

    SDL_RenderPresent(renderer);
}

void Core::Quit(SDL_AppResult result)
{
    (void)result;   //чтобы компилятор не ругался на неиспользуемую переменную

    imWindow.QuitImGui();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(mainWindow);
    SDL_Quit();
}