#pragma once

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

// Forward declaration
struct AppData;

class GuiWindow {
public:
	// онструктор принимает ссылку на данные приложени€
	GuiWindow(const AppData& appData);

	void InitImGui();
	void ProcessEventsImGui(const SDL_Event* event);
	void UpdateImGui();
	void RenderImGui();
	void QuitImGui();

	//ћетод дл€ обновлени€ данных
	void UpdateAppData(const AppData& newData);

private:
	const AppData* appData; //”казатель на данные приложени€
};
