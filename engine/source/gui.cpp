#include "gui.hpp"

#include "core.hpp"

void GuiWindow::InitImGui()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(Core::mainWindow, Core::renderer);
    ImGui_ImplSDLRenderer3_Init(Core::renderer);
}

void GuiWindow::ProcessEventsImGui(const SDL_Event *event)
{
    ImGui_ImplSDL3_ProcessEvent(event);
}

void GuiWindow::UpdateImGui()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    {
        ImGuiIO &io = ImGui::GetIO();
        // io.FontGlobalScale = 1.5f;
        ImGui::Begin("Statistics");
        ImGui::Text("API %s", SDL_GetRendererName(Core::renderer));
        ImGui::Text("Application average %.2f ms/frame (%.0f FPS)", 1000.0f / io.Framerate, io.Framerate);
        if (ImGui::IsMousePosValid())
            ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
        else
            ImGui::Text("Mouse pos: <INVALID>");

        ImGui::End();
    }
}

void GuiWindow::RenderImGui()
{
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), Core::renderer);
}

void GuiWindow::QuitImGui()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}
