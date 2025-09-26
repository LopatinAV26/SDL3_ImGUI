#include "gui.hpp"
#include "core.hpp"

GuiWindow::GuiWindow(const AppData& appData) : appData(&appData) {}

void GuiWindow::InitImGui()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	//Setup scaling
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(appData->mainScale);
	style.FontScaleDpi = appData->mainScale;

	// Setup Platform/Renderer backends
	ImGui_ImplSDL3_InitForSDLRenderer(appData->window, appData->renderer);
	ImGui_ImplSDLRenderer3_Init(appData->renderer);
}

void GuiWindow::ProcessEventsImGui(const SDL_Event* event)
{
	ImGui_ImplSDL3_ProcessEvent(event);
}

void GuiWindow::UpdateImGui()
{
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGui::Begin("Statistics");
		ImGui::Text("API %s", SDL_GetRendererName(appData->renderer));
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
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), appData->renderer);
}

void GuiWindow::QuitImGui()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
	appData = nullptr;
}

void GuiWindow::UpdateAppData(const AppData& newData) {
	appData = &newData;
}
