#pragma once
#include <memory>
#include <SDL3/SDL.h>
//#include <thread>

#include "gui.hpp"

struct AppData {
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };
	int windowWidth{ 1600 };
	int windowHeight{ 900 };
	SDL_WindowFlags windowFlags{ SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY };
	float mainScale{ 1.f };

	float deltaTime{ 0.f };
};

class Core
{
public:
	//Core() {};
	//Core(const Core &) = delete;
	// Core operator=(const Core &);
	// Core(const Core &&);
	// Core operator=(const Core &&);
	//  ~Core() {};

	SDL_AppResult Init();
	SDL_AppResult Iterate();
	SDL_AppResult ProcessEvent(SDL_Event* event);
	void Update();
	void Render();
	void Quit(SDL_AppResult result);

private:
	AppData appData;

	std::unique_ptr<GuiWindow>imWindow;
};