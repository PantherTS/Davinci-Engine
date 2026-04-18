#include "Framework.h"
#include "Timer.h"
#include "ModeManager.h"
#include "Window.h"
#include <filesystem>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace DavinciEngine;

Framework* Framework::m_pFramework;

Framework::Framework()
{
	//m_pCommandConsole = NULL;
}

Framework::~Framework()
{
	//if(m_pCommandConsole){
	//	m_pCommandConsole->Destroy();
	//}
}

Framework* Framework::GetInstance() {
	if (!m_pFramework) {
		m_pFramework = new Framework();
	}
	return m_pFramework;
}

void Framework::Destroy() {
	if (m_pFramework) {
		delete m_pFramework;
		m_pFramework = nullptr;
	}
}

std::string Framework::GetDefaultContentPath() noexcept
{
#ifdef _WIN32
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);

	return (std::filesystem::path(buffer).parent_path() / "./").string();
#else
	return "./";
#endif
}

void Framework::Update() {

	//if(!m_pCommandConsole){
	//	m_pCommandConsole = cCommandConsole::GetInstance();
	//}

	SDL_Event event;
	SDL_PollEvent(&event);

	float x = 0;
	float y = 0;

	SDL_GetMouseState(&x, &y);
	m_v2dMousePosition.x = x;
	m_v2dMousePosition.y = y;

	Uint8 uiMouseState = SDL_GetRelativeMouseState(nullptr, nullptr);

	m_bMouseButtons[0] = (uiMouseState & SDL_BUTTON_MASK(SDL_BUTTON_LEFT)) != 0 ? true : false;
	m_bMouseButtons[1] = (uiMouseState & SDL_BUTTON_MASK(SDL_BUTTON_RIGHT)) != 0 ? true : false;
	m_bMouseButtons[2] = (uiMouseState & SDL_BUTTON_MASK(SDL_BUTTON_MIDDLE)) != 0 ? true : false;
	m_bMouseButtons[3] = (uiMouseState & SDL_BUTTON_MASK(SDL_BUTTON_X1)) != 0 ? true : false;
	m_bMouseButtons[4] = (uiMouseState & SDL_BUTTON_MASK(SDL_BUTTON_X2)) != 0 ? true : false;

	memcpy(m_bKeys, SDL_GetKeyboardState(nullptr), KEY_MAX);

	switch (event.type)
	{
	case SDL_EVENT_WINDOW_FOCUS_GAINED: {
		// We've regained focus of the game window so we unpause the engine.
		Timer::GetInstance()->Unpause();
		break;
	}
	case SDL_EVENT_WINDOW_FOCUS_LOST: {
		// We've lost focus of the game window so we pause the engine.
		Timer::GetInstance()->Pause();
		break;
	}
	case SDL_EVENT_QUIT: {
		// User has clicked close on the game window. Shutdown gracefully.
		ModeManager::GetInstance()->SetMode(0);
		break;
	}
	case SDL_EVENT_KEY_DOWN: {

		if (event.key.key != 0)
		{
			if (event.key.key == 96)
			{
				// Command console toggle key has been pressed. Toggle the command console.
			}
		}

		switch (event.key.key) {
		case SDLK_LEFT:
			break;
		case SDLK_RIGHT:
			break;
		case SDLK_UP:
			break;
		case SDLK_DOWN:
			break;
		default:
			break;
		}
		break;
	}
	case SDL_EVENT_KEY_UP: {
		break;
	}
	}
}