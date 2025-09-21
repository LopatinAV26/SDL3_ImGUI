#pragma once

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

class GuiWindow{
    public:
    void InitImGui();
    void ProcessEventsImGui(const SDL_Event *event);
    void UpdateImGui();
    void RenderImGui();
    void QuitImGui();
};
