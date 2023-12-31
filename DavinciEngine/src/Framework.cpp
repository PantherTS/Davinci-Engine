#include "Framework.h"
#include "Timer.h"
#include "ModeManager.h"
#include "Window.h"

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

Framework* Framework::GetInstance(){
	if(!m_pFramework){
		m_pFramework = new Framework();
	}
	return m_pFramework;
}

void Framework::Destroy(){
	if(m_pFramework){
		delete m_pFramework;
		m_pFramework = nullptr;
	}
}

void Framework::Update(){

	//if(!m_pCommandConsole){
	//	m_pCommandConsole = cCommandConsole::GetInstance();
	//}

	SDL_Event event;
	SDL_PollEvent(&event);

	int x = 0;
	int y = 0;

	SDL_GetMouseState(&x,&y);
	m_v2dMousePosition.x = static_cast<float>(x);
	m_v2dMousePosition.y = static_cast<float>(Window::GetInstance()->GetHeight()-y);

	Uint8 uiMouseState = SDL_GetRelativeMouseState(nullptr,nullptr);

	m_bMouseButtons[0] = (uiMouseState & SDL_BUTTON(1)) != 0 ? true : false;
	m_bMouseButtons[1] = (uiMouseState & SDL_BUTTON(2)) != 0 ? true : false;;
	m_bMouseButtons[2] = (uiMouseState & SDL_BUTTON(3)) != 0 ? true : false;;
	m_bMouseButtons[3] = (uiMouseState & SDL_BUTTON(4)) != 0 ? true : false;;
	m_bMouseButtons[4] = (uiMouseState & SDL_BUTTON(5)) != 0 ? true : false;;

	memcpy(m_bKeys, SDL_GetKeyboardState(nullptr),KEY_MAX);

	switch (event.type)
	{
	case SDL_WINDOWEVENT: {
		switch (event.window.event) {
		case SDL_WINDOWEVENT_FOCUS_GAINED: {
			// We've regained focus of the game window so we unpause the engine.
			Timer::GetInstance()->unpause();
			break;
		}
		case SDL_WINDOWEVENT_FOCUS_LOST: {
			// We've lost focus of the game window so we pause the engine.
			Timer::GetInstance()->pause();
			break;
		}
		default:
			break;
		}
		break;
	}
	case SDL_QUIT: {
		// User has clicked close on the game window. Shutdown gracefully.
		ModeManager::GetInstance()->SetMode(0);
		break;
	}
	case SDL_KEYDOWN: {
		//CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyDown(toCEGUIKey(events.key.keysym.scancode));

		if (event.key.keysym.sym != 0)
		{
			//CEGUI::System::getSingleton().getDefaultGUIContext().injectChar(events.key.keysym.sym);
			if (event.key.keysym.sym == 96)
			{
				//m_pCommandConsole->Toggle();
			}
		}

		switch (event.key.keysym.sym) {
		case SDLK_LEFT:
			break;
		case SDLK_RIGHT:
			break;
		case SDLK_UP:
			//if (cCommandConsole::bConsoleOpen) { m_pCommandConsole->PopulateEntry(false); }
			break;
		case SDLK_DOWN:
			//if (cCommandConsole::bConsoleOpen) { m_pCommandConsole->PopulateEntry(true); }
			break;
		default:
			break;
		}
		break;
	}
	case SDL_KEYUP: {
		//CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp(toCEGUIKey(events.key.keysym.scancode));
		break;
	}
	}
}