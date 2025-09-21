#pragma once

#include <SDL3/SDL.h>
//#include <thread>

#include "gui.hpp"

class Core
{
public:
    Core() {};
    Core(const Core &) = delete;
    // Core operator=(const Core &);
    // Core(const Core &&);
    // Core operator=(const Core &&);
    //  ~Core() {};
    
    SDL_AppResult Init();
    SDL_AppResult Iterate();
    SDL_AppResult ProcessEvent(SDL_Event *event);
    void Update();
    void Render();
    void Quit(SDL_AppResult result);

    static SDL_Window *mainWindow;
    static SDL_Renderer *renderer;

private:
    int mainWindowWidth = 1920;
    int mainWindowHeight = 1080;
    SDL_WindowFlags mainWindowFlags = SDL_WINDOW_RESIZABLE;
    
    GuiWindow imWindow;
};