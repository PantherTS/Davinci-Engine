#include "GUI.h"
#include "DavinciEngine.h"
#include "CommandConsole.h"
#include "LowLevelSystem.h"
#include "LUAModule.h"
#include "Window.h"
#//include "LuaInterface.h"

using namespace DavinciEngine;

GUI *GUI::m_GUI = nullptr;

GUI *GUI::GetInstance ( void )
{
	if ( !m_GUI ) {
		m_GUI = new GUI();
	}
	return m_GUI;
}

void GUI::Destroy()
{
	if(m_GUI){
		delete m_GUI;
		m_GUI = nullptr;
	}
}

GUI::GUI() : m_pInput( nullptr )
{
	// Retrieve a pointer to the Input class
	this->m_pInput = Input::GetInstance();

	//temp = new Button();
}

// GUI Input Functions for SDL
void GUI::OnExit()
{
	Davinci::Engine_GetInstance()->SetGameMode(0);
}

// Render the GUI
void GUI::GUI_Render( void )
{
	//temp->Render(glm::mat4(1.0f));
}

void GUI::GUI_GrabTextures( void )
{
	//renderer->grabTextures();
}

void GUI::GUI_RestoreTextures( void )
{
	//renderer->restoreTextures();
}

void GUI::GUI_SetDisplaySize( int width, int height )
{
	//renderer->setDisplaySize(Sizef(static_cast<float>(width), static_cast<float>(height)));
}