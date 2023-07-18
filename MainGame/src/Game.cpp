#include "Game.h"

using namespace DavinciEngine;

Game* Game::m_WitchDoctor = nullptr;

Game* Game::GetInstance( void )
{
	if(!m_WitchDoctor){
		m_WitchDoctor = new Game();
		m_WitchDoctor->m_menuLoaded = false;
	}
	return m_WitchDoctor;
}

void Game::Run()
{
	// Main Game Loop
	while(dengine()->GetGameMode() != 0){

		if(dengine()->GetGameMode() == 1){
			if(m_WitchDoctor->LoadMainMenu())
			{
				dengine()->Engine_Update();
			}
			else{
				dengine()->SetGameMode(0);
			}
		}
		else if(dengine()->GetGameMode() == 2){
			dengine()->Engine_Update();
		}
	}
	delete m_WitchDoctor;
	m_WitchDoctor = nullptr;
}

bool Game::LoadMainMenu()
{
	if(m_menuLoaded)
	{
		return true;
	}

	else{
		if(dengine()->RunScript("gui_init.lua")){
			if(dengine()->RunScript("gui_mainmenu.lua")){
				dengine()->Engine_Log("Main Menu Loaded Successfully.");
				m_menuLoaded = true;
			}
		}
		else{
			dengine()->Engine_Log("Main Menu Failed to Load!");
			m_menuLoaded = false;
			return false;
		}
		return true;	// The MainMenu loaded successfully.
	}
}