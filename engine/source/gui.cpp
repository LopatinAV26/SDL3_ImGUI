#include "gui.hpp"

#include <SDL3/SDL.h>

#include "core.hpp"

Gui::Gui(const CoreData *appData)
	: p_coreData{appData}
{
}

void Gui::InitImGui()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	[[maybe_unused]] ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

	// Загружаем и настраиваем шрифт
	ImFontConfig font_config;
	font_config.OversampleH = 2;	// Включаем горизонтальный оверсэмплинг для лучшего рендеринга
	font_config.OversampleV = 2;	// Включаем вертикальный оверсэмплинг
	font_config.PixelSnapH = false; // Отключаем привязку к пикселям для лучшего дробного масштабирования

	io.Fonts->AddFontFromFileTTF("resources/fonts/ShareTechMonoRegular.ttf",
								 13.0f,
								 &font_config);

	// ImGui::StyleColorsDark();
	// ImGui::StyleColorsLight();
	ImGui::StyleColorsClassic();

	// Setup scaling
	ImGuiStyle &style = ImGui::GetStyle();
	style.ScaleAllSizes(p_coreData->mainScale);
	style.FontScaleDpi = p_coreData->mainScale;
	style.WindowRounding = 4.0f;

	ImGui_ImplSDL3_InitForSDLRenderer(p_coreData->window, p_coreData->renderer);
	ImGui_ImplSDLRenderer3_Init(p_coreData->renderer);

	SDL_Log("ImGui initialized successfully.");
}

void Gui::ProcessEventImGui(const SDL_Event *event)
{
	ImGui_ImplSDL3_ProcessEvent(event);
}

// Добавить в начало SDL_AppIterate
void Gui::IterateImGui()
{
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	// ImGui::ShowMetricsWindow();
	// ImGui::ShowDemoWindow();

	//---------------------------------
	if (showDebugWindow)
		DebugWindow();

	if (showFullscreenWindow)
		FullscreenWindow();

	if (showProtocolVMC)
		p_protocolVMC->WindowProtocol(showProtocolVMC);
	if (!showProtocolVMC && p_protocolVMC != nullptr)
	{
		SDL_Log("ProtocolVMC closed");
		p_protocolVMC.reset();
	}

	if (showNomogram)
		p_nomogram->NomogramWindow(showNomogram);
	if (!showNomogram && p_nomogram != nullptr)
	{
		SDL_Log("Nomogram closed");
		p_nomogram.reset();
	}
	//---------------------------------

	// Для работы с HiDPI
	ImGuiIO &io = ImGui::GetIO();
	SDL_SetRenderScale(p_coreData->renderer,
					   io.DisplayFramebufferScale.x,
					   io.DisplayFramebufferScale.y);
}

// Добавить перед SDL_RenderPresent
void Gui::RenderImGui()
{
	ImGui::Render();
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), p_coreData->renderer);
}

void Gui::DebugWindow()
{
	ImGuiIO &io = ImGui::GetIO();
	ImGui::Begin("DebugWindow", &showDebugWindow);
	{
		ImGui::Text("API: %s", SDL_GetRendererName(p_coreData->renderer));
		ImGui::Text("Driver: %s", p_coreData->driver.data());

		fpsUpdateTimer += io.DeltaTime;
		if (fpsUpdateTimer >= 0.5f)
		{
			currentFrametime = {1000.f / io.Framerate};
			framerate = {io.Framerate};
			fpsUpdateTimer = {0.f};
		}
		ImGui::Text("Application average %.2f ms/frame (%.0f FPS)", currentFrametime, framerate);

		if (ImGui::IsMousePosValid())
			ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
		else
			ImGui::Text("Mouse pos: <INVALID>");
	}
	ImGui::End();
}

void Gui::FullscreenWindow()
{
	/* ImGuiViewport *viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);

	ImGuiWindowFlags window_flags = // ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoBringToFrontOnFocus; */

	// Кнопка без окна///////////////////////////////////////////////
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration |
									// ImGuiWindowFlags_NoMove |
									ImGuiWindowFlags_AlwaysAutoResize |
									// ImGuiWindowFlags_NoSavedSettings |
									ImGuiWindowFlags_NoBringToFrontOnFocus |
									ImGuiWindowFlags_NoBackground;

	ImGui::Begin("Main Window", &showFullscreenWindow, window_flags);

	if (ImGui::Button("Создать заключение ВИК"))
	{
		showProtocolVMC = true;
		if (p_protocolVMC == nullptr)
			p_protocolVMC = std::make_unique<ProtocolVMC>();
	}

	if (ImGui::Button("Открыть номограмму РК"))
	{
		showNomogram = true;
		if (p_nomogram == nullptr)
			p_nomogram = std::make_unique<Nomogram>();
	}

	ImGui::End();
}

Gui::~Gui()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();
	p_coreData = nullptr;
	SDL_Log("ImGui shutdown complete.");
}
