#include "gui.hpp"
#include "core.hpp"
#include "imgui.h"
#include "imgui_internal.h"

GuiWindow::GuiWindow(const CoreData &appData) : p_coreData(&appData) {}

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

	// Setup scaling
	ImGuiStyle &style = ImGui::GetStyle();
	style.ScaleAllSizes(p_coreData->mainScale);
	style.FontScaleDpi = p_coreData->mainScale;

	// Setup Platform/Renderer backends
	ImGui_ImplSDL3_InitForSDLRenderer(p_coreData->window, p_coreData->renderer);
	ImGui_ImplSDLRenderer3_Init(p_coreData->renderer);
}

void GuiWindow::ProcessEventsImGui(const SDL_Event *event)
{
	ImGui_ImplSDL3_ProcessEvent(event);
}

// Добавить в начало основного цикла
void GuiWindow::UpdateImGui()
{
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	// Create fullscreen window
	{
		ImGuiIO &io = ImGui::GetIO();

		ImGui::Begin("MainWindow", nullptr);

		ImGui::Text("API %s", SDL_GetRendererName(p_coreData->renderer));
		ImGui::Text("Application average %.2f ms/frame (%.0f FPS)", 1000.0f / io.Framerate, io.Framerate);
		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
		else
			ImGui::Text("Mouse pos: <INVALID>");

		if(ImGui::Button("Создать заключение")){

		}

		ImGui::End();
	}
}

// Добавить в конец основного цикла
void GuiWindow::RenderImGui()
{
	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), p_coreData->renderer);
}

void GuiWindow::QuitImGui()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
	p_coreData = nullptr;
}