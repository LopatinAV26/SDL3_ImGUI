#include "gui.hpp"

#include <iostream>

#include "imgui.h"
#include "imgui_internal.h"
#include <SDL3/SDL.h>

#include "core.hpp"
#include "protocolVMC.hpp"

Gui::Gui(const CoreData *appData)
	: p_coreData(appData)
{
}

void Gui::InitImGui()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	[[maybe_unused]] ImGuiIO &io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

	// Загружаем и настраиваем шрифт
	ImFontConfig font_config;
	font_config.OversampleH = 2;	// Включаем горизонтальный оверсэмплинг для лучшего рендеринга
	font_config.OversampleV = 2;	// Включаем вертикальный оверсэмплинг
	font_config.PixelSnapH = false; // Отключаем привязку к пикселям для лучшего дробного масштабирования

	
	//!!!Реализовать проверку наличия файла шрифта средствами SDL3, либо написать загрузчик ресурсов
	// и грузить шрифт из ресурсов
	io.Fonts->AddFontFromFileTTF("resources/fonts/ShareTechMonoRegular.ttf",
								 13.0f * 1.5 /* p_coreData->mainScale */,
								 &font_config);
	
	// ImGui::StyleColorsDark();
	// ImGui::StyleColorsLight();
	ImGui::StyleColorsClassic();

	// Setup scaling
	ImGuiStyle &style = ImGui::GetStyle();
	style.ScaleAllSizes(p_coreData->mainScale);
	style.FontScaleDpi = p_coreData->mainScale;
	// style.WindowRounding = 5.0f;

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

	// Логика для создания и удаления ProtocolBase///////////////////////
	if (showProtocolVMC)
	{
		p_protocolVMC->CreateProtocol(showProtocolVMC);
	}
	else if (!showProtocolVMC && p_protocolVMC != nullptr)
	{
		p_protocolVMC.reset();
		SDL_Log("ProtocolVMC deleted.");
	}
	/////////////////////////////////////////////////////////////////////////

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

	ImGui::Text("API %s", SDL_GetRendererName(p_coreData->renderer));

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

	ImGui::End();
}

void Gui::FullscreenWindow()
{
	ImGuiViewport *viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);

	ImGuiWindowFlags window_flags = // ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoSavedSettings |
		ImGuiWindowFlags_NoBringToFrontOnFocus;

	ImGui::Begin("Main Window", &showFullscreenWindow, window_flags);

	// Логика в главном окне-------------------------------------------------------------------------
	if (ImGui::Button("Создать заключение ВИК"))
	{
		showProtocolVMC = true;
		if (p_protocolVMC == nullptr)
		{
			p_protocolVMC = std::make_unique<ProtocolVMC>();
			SDL_Log("ProtocolVMC created.");
		}
	}

	if (ImGui::Button("Нормативная документация"))
	{
		// Действие для кнопки 2
	}
	//---------------------------------------------------------------------------------------------

	ImGui::End();
}

Gui::~Gui()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
	p_coreData = nullptr;
	SDL_Log("ImGui shutdown complete.");
}
