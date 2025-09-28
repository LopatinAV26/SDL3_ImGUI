#pragma once

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"

// Forward declaration
struct CoreData;

class GuiWindow
{
public:
	GuiWindow(const CoreData &appData);
	~GuiWindow();

	void InitImGui();
	void IterateImGui();
	void ProcessEventImGui(const SDL_Event *event);
	void RenderImGui();

private:
	const CoreData *p_coreData;

	void DebugWindow();
	void FullscreenWindow();
	
	// Для обновления FPS
	float fps_update_timer{0.0f};
	float current_fps{0.0f};
	float current_frametime{0.0f};
};
