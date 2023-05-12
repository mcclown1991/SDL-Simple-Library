#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <SDL/SDL.h>


class SDLCore {
private:
	SDLCore();
	~SDLCore();

	void Update();

	static SDLCore m_EngineInstance;
	bool m_QuitRaised;
	SDL_Event m_Event;
	std::shared_ptr<SDL_Window> p_Window;

public:
	static SDLCore* GetSDLCore() { return &m_EngineInstance; }

	// inits
	void SystemInit();
	void SystemInit(std::string_view window_title);
	void SystemInit(std::string_view window_title, int w, int h);
	void SystemInit(std::string_view window_title, int x, int y, int w, int h);
	void SystemInit(std::string_view window_title, int x, int y, int w, int h, Uint32 flags);

	void SystemRun();
	void SystemExit();
};