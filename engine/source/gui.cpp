#include "gui.hpp"
#include "core.hpp"
#include "imgui.h"
#include "imgui_internal.h"
#include <SDL3/SDL.h>

GuiWindow::GuiWindow(const CoreData &appData) : p_coreData(&appData)
{
	current_fps = 0.0f;
	current_frametime = 0.0f;
	fps_update_timer = 0.0f;
}

void GuiWindow::InitImGui()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

	// Загружаем и настраиваем шрифт
	ImFontConfig font_config;
	font_config.OversampleH = 2;	// Включаем горизонтальный оверсэмплинг для лучшего рендеринга
	font_config.OversampleV = 2;	// Включаем вертикальный оверсэмплинг
	font_config.PixelSnapH = false; // Отключаем привязку к пикселям для лучшего дробного масштабирования

	// Загружаем основной шрифт
	io.Fonts->AddFontFromFileTTF("../../resources/fonts/ShareTechMonoRegular.ttf",
								 16.0f * p_coreData->mainScale,
								 &font_config,
								 io.Fonts->GetGlyphRangesCyrillic());

	// Setup Dear ImGui style
	// ImGui::StyleColorsDark();
	// ImGui::StyleColorsLight();
	ImGui::StyleColorsClassic();

	// Setup scaling
	ImGuiStyle &style = ImGui::GetStyle();
	style.ScaleAllSizes(p_coreData->mainScale);
	style.FontScaleDpi = p_coreData->mainScale;
	// style.WindowRounding = 5.0f;

	// Setup Platform/Renderer backends
	ImGui_ImplSDL3_InitForSDLRenderer(p_coreData->window, p_coreData->renderer);
	ImGui_ImplSDLRenderer3_Init(p_coreData->renderer);
}

void GuiWindow::ProcessEventImGui(const SDL_Event *event)
{
	ImGui_ImplSDL3_ProcessEvent(event);
}

// Добавить в начало SDL_AppIterate
void GuiWindow::IterateImGui()
{
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	FullscreenWindow();
	DebugWindow();

	ImGui::Render();

	// Для работы с HiDPI
	ImGuiIO &io = ImGui::GetIO();
	SDL_SetRenderScale(p_coreData->renderer,
					   io.DisplayFramebufferScale.x,
					   io.DisplayFramebufferScale.y);
}

// Добавить перед SDL_RenderPresent
void GuiWindow::RenderImGui()
{
	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), p_coreData->renderer);
}

GuiWindow::~GuiWindow()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
	p_coreData = nullptr;
	SDL_Log("ImGui shutdown complete.");
}

void GuiWindow::DebugWindow()
{
	ImGuiIO &io = ImGui::GetIO();
	ImGui::Begin("DebugWindow", nullptr);

	ImGui::Text("API %s", SDL_GetRendererName(p_coreData->renderer));

	// Обновляем значения FPS
	fps_update_timer += io.DeltaTime;
	if (fps_update_timer >= 0.5f)
	{
		current_fps = io.Framerate;
		current_frametime = 1000.0f / io.Framerate;
		fps_update_timer = 0.0f;
	}
	ImGui::Text("Application average %.2f ms/frame (%.0f FPS)", current_frametime, current_fps);
	if (ImGui::IsMousePosValid())
		ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
	else
		ImGui::Text("Mouse pos: <INVALID>");

	ImGui::End();
}

void GuiWindow::FullscreenWindow()
{
	ImGuiViewport *viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);

	ImGuiWindowFlags window_flags = //ImGuiWindowFlags_NoDecoration |
									ImGuiWindowFlags_NoMove |
									ImGuiWindowFlags_NoResize |
									ImGuiWindowFlags_NoSavedSettings |
									ImGuiWindowFlags_NoBringToFrontOnFocus;

	if (ImGui::Begin("Main Window", NULL, window_flags))
	{
		// Создаем центрированную группу кнопок
		float window_width = ImGui::GetWindowSize().x;
		float buttons_width = 120.0f * 2 + ImGui::GetStyle().ItemSpacing.x;
		ImGui::SetCursorPosX((window_width - buttons_width) * 0.5f);

		if (ImGui::Button("Кнопка 1", ImVec2(120, 0)))
		{
			// Действие для кнопки 1
		}

		ImGui::SameLine();

		if (ImGui::Button("Кнопка 2", ImVec2(120, 0)))
		{
			// Действие для кнопки 2
		}
	}
	ImGui::End();
}
