#pragma once

#include <string_view>
#include <memory>
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

struct ApplicationData
{
	SDL_Window *window{nullptr};
	SDL_Renderer *renderer{nullptr};
	int windowWidth{1280};
	int windowHeight{720};
	SDL_WindowFlags windowFlags{SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY};
	float mainScale{1.25};
	std::string_view driver;
	std::string fontName{"resources/fonts/ShareTechMonoRegular.ttf"};
	float fontSize{13.0f};

	bool isWindowFocused{true};
	bool isWindowMinimized{false};
};

class Gui;
class Core
{
public:
	Core();
	Core(const Core &) = delete;
	Core &operator=(const Core &) = delete;
	Core(Core &&) = delete;
	Core &operator=(Core &&) = delete;
	~Core();

	SDL_AppResult Init();
	SDL_AppResult Iterate();
	SDL_AppResult ProcessEvent(const SDL_Event *event);

private:
	std::shared_ptr<ApplicationData> appData = std::make_shared<ApplicationData>();
	std::unique_ptr<Gui> imWindow;
};
