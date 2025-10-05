#pragma once
#include <SDL3/SDL.h>
#include "gui.hpp"

struct CoreData
{
	SDL_Window *window{nullptr};
	SDL_Renderer *renderer{nullptr};
	int windowWidth{1280};
	int windowHeight{720};
	SDL_WindowFlags windowFlags{SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY};
	float mainScale{1.f};
	float deltaTime{0.f};

	// Флаги состояния окна
	bool isWindowFocused{true};
	bool isWindowMinimized{false};
};

class Core
{
public:
	Core() = default;
	Core(const Core &) = delete;
	Core &operator=(const Core &) = delete;
	Core(Core &&) = delete;
	Core &operator=(Core &&) = delete;
	~Core();

	SDL_AppResult Init();
	SDL_AppResult Iterate();
	SDL_AppResult ProcessEvent(const SDL_Event *event);

private:
	CoreData *coreData = new CoreData();
	Gui *imWindow{nullptr};
};