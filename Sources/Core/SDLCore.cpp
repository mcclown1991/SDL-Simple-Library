#include "SDLCore.h"

SDLCore SDLCore::m_EngineInstance;

SDLCore::SDLCore() : m_QuitRaised(false) {
	SDL_Init(SDL_INIT_EVERYTHING);
}

SDLCore::~SDLCore() {
	
}

void SDLCore::SystemInit() {
	p_Window = std::shared_ptr<SDL_Window>(SDL_CreateWindow("SDL Simple Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 360, SDL_WINDOW_OPENGL), [](auto* ptr){});
}

void SDLCore::SystemInit(std::string_view window_title) {
	p_Window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(window_title.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 360, SDL_WINDOW_OPENGL), [](auto* ptr) {});
}

void SDLCore::SystemInit(std::string_view window_title, int w, int h) {
	p_Window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(window_title.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_OPENGL), [](auto* ptr) {});
}

void SDLCore::SystemInit(std::string_view window_title, int x, int y, int w, int h) {
	p_Window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(window_title.data(), x, y, w, h, SDL_WINDOW_OPENGL), [](auto* ptr) {});
}

void SDLCore::SystemInit(std::string_view window_title, int x, int y, int w, int h, Uint32 flags) {
	p_Window = std::shared_ptr<SDL_Window>(SDL_CreateWindow(window_title.data(), x, y, w, h, flags), [](auto* ptr) {});
}

void SDLCore::SystemRun() {
	while(!m_QuitRaised) {
		Update();
	}
}

void SDLCore::SystemExit() {
	m_QuitRaised = true;
	SDL_DestroyWindow(p_Window.get());
	p_Window.reset();
	SDL_Quit();
}

void SDLCore::Update() {
	SDL_PollEvent(&m_Event);
	if (m_Event.type == SDL_WINDOWEVENT && m_Event.window.event == SDL_WINDOWEVENT_CLOSE) {
		SystemExit();
	}
}
