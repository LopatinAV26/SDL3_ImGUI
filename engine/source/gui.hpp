#pragma once

#include <memory>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include "imgui_stdlib.h"
//#include "imgui_internal.h"
#include "implot.h"
#include "implot_internal.h"

#include "protocolVMC.hpp"
#include "nomogram.hpp"

struct CoreData;
//class ProtocolVMC;

class Gui
{
public:
	explicit Gui(const CoreData *appData);
	~Gui();

	void InitImGui();
	void ProcessEventImGui(const SDL_Event *event);
	void IterateImGui();
	void RenderImGui();

private:
	void FullscreenWindow();
	void DebugWindow();

	const CoreData *p_coreData{nullptr};
	std::unique_ptr<ProtocolVMC> p_protocolVMC;
	std::unique_ptr<Nomogram> p_nomogram;

	bool showFullscreenWindow{true};
	bool showDebugWindow{true};

	bool showProtocolVMC{false};
	bool showNomogram{false};

	float fpsUpdateTimer{0.f};
	float currentFrametime{0.f};
	float framerate{0.f};
};
