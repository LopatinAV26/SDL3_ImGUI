#pragma once

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <vector>
#include <string>

// Forward declaration
struct CoreData;

class GuiWindow {
public:
	GuiWindow(const CoreData& appData);

	void InitImGui();
	void ProcessEventsImGui(const SDL_Event* event);
	void UpdateImGui();
	void RenderImGui();
	void QuitImGui();

private:
	const CoreData* p_coreData;
};
