#include "LowLevelSystem.h"
#include "Framework.h"
#include "AssetManager.h"
#include "Window.h"
#include "Graphic.h"
#include "Timer.h"
#include "ModeManager.h"
#include "XmlSettings.h"
#include "Scene.h"
#include "LUAModule.h"
#include "GUI.h"
#include "Input.h"
#include "DavinciEngine.h"
#include "SDL/SDL.h"
#include "Actor.h"
#include <string>

using namespace DavinciEngine;

Davinci *Davinci::m_pDavinci = nullptr;
Scene *m_pScene = nullptr;						// Pointer to the Scene Singleton.
GUI *m_pGUI = nullptr;							// Pointer to the Graphical User Interface Singleton.
Input *m_pInput = nullptr;						// Pointer to the Input Singleton.
ModeManager *m_pModeManager = nullptr;			// Pointer to the ModeManager Singleton.
XmlSettings *m_pXMLSettings = nullptr;			// Pointer to the XmlSettings Singleton.
Timer *m_pTimer = nullptr;						// Pointer to the Timer Singleton.
Window *m_pWindow = nullptr;					// Pointer to the Window Class;
Framework *m_pFramework = nullptr;				// Pointer to the Framework Singleton.
AssetManager *m_pAssetManager = nullptr;		// Pointer to the AssetManager Singleton.
LUAModule *m_pLUAModule = nullptr;

// Class constructor
Davinci::Davinci()
{
}

// Class destructor
Davinci::~Davinci()
{
}

/************************************************************
* void Davinci::Destroy()									*
*		Deletes the instance of the class.					*
************************************************************/
void Davinci::Engine_Destroy()
{
	Log("Engine Shutting Down...");
	m_pScene->Destroy();
	m_pInput->Destroy();
	m_pGUI->Destroy();
	m_pLUAModule->Destroy();
	m_pModeManager->Destroy();
	m_pXMLSettings->Destroy();
	m_pTimer->Destroy();
	m_pAssetManager->Destroy();
	Log("Engine Resources Have Been Unloaded Successfully. Goodbye!");
	m_pFramework->Destroy();
	m_pWindow->Destroy();
	delete m_pDavinci;

	m_pScene = nullptr;
	m_pInput = nullptr;
	m_pGUI = nullptr;
	m_pLUAModule = nullptr;
	m_pModeManager = nullptr;
	m_pXMLSettings = nullptr;
	m_pTimer = nullptr;
	m_pAssetManager = nullptr;
	m_pFramework = nullptr;
	m_pWindow = nullptr;
	m_pDavinci = nullptr;
}

// Class Singleton reference
Davinci *Davinci::Engine_GetInstance ( void ) {
	if (!m_pDavinci) {
		m_pDavinci = new Davinci();
	}
	return m_pDavinci;
}

/************************************************************
* bool Davinci::Init()										*
*		Initialize the window and the OpenGL properties. It	*
*	also creates an instance of the XMLSettings object,		*
*	determines if a settings file exists (creates one if it	*
*	doesn't), and loads the settings for runtime. Returns	*
*	TRUE if all initializations completed successfully.		*
************************************************************/
bool Davinci::Engine_Init()
{
	Log("Engine Starting Up...");
	m_pFramework = Framework::GetInstance();
	m_pAssetManager = AssetManager::GetInstance();
	m_pModeManager = ModeManager::GetInstance();
	m_pXMLSettings = XmlSettings::GetInstance();
	m_pTimer = Timer::GetInstance();
	m_pXMLSettings->LoadSettings();
	
	m_pWindow = Window::NewWindow(m_pXMLSettings->GetTitle(),m_pXMLSettings->GetWidth(),
		m_pXMLSettings->GetHeight(),m_pXMLSettings->GetBPP(),m_pXMLSettings->GetFS());
	if(m_pWindow == nullptr)
	{
		return false;
	}

	m_pLUAModule = LUAModule::GetInstance();
	m_pInput = Input::GetInstance();
	m_pGUI = GUI::GetInstance();
	Log("Engine Initialized Successfully.");

	// REMOVE THIS ONCE LEVEL LOADING IS IMPLEMENTED!!!!
	m_pScene = Scene::GetInstance();

	return true;
}

/************************************************************
* void Davinci::TimerStart()								*
*		Starts the engine's internal timer. The timer is 	*
*	used to determine proper game speed across all systems.	*
************************************************************/
void Davinci::TimerStart()
{
	m_pTimer->start();
}

/************************************************************
* void Davinci::TimerPause()								*
*		Pauses the engine's internal timer. The timer is 	*
*	used to determine proper game speed across all systems.	*
************************************************************/
void Davinci::TimerPause()
{
	Log("Game Timer Paused.");
	m_pTimer->pause();
}

/************************************************************
* float Davinci::TimerGetTicks()							*
*		Returns the current ticks of the engine timer.		*
************************************************************/
float Davinci::TimerGetTicks()
{
	return static_cast<float>(m_pTimer->GetTicks());
}

/************************************************************
* int Davinci::GetGameMode()								*
*		Returns the current game mode:						*
*			0: Exiting Game									*
*			1: Main Menu									*
*			2: Gameplay										*
************************************************************/
int Davinci::GetGameMode()
{
	return m_pModeManager->GetMode();
}

/************************************************************
* void Davinci::SetGameMode()								*
*		Sets the current game mode:							*
*			0: Exiting Game									*
*			1: Main Menu									*
*			2: Gameplay										*
************************************************************/
void Davinci::SetGameMode(int mode)
{
	Log("Setting Game Mode to %d", mode);
	m_pModeManager->SetMode(mode);
}

// Engine Update Routine
void Davinci::Engine_Update()
{
	m_pFramework->Update();
	m_pTimer->Update();
	m_pInput->Update();
	m_pScene->Update();
	m_pScene->Render();
	m_pGUI->GUI_Render();
	m_pTimer->SetPreviousTicks();
}

bool Davinci::RunScript(const char *scriptFile)
{
	std::string scriptPath = Framework::GetInstance()->GetDefaultContentPath();
	scriptPath.append("data/lua_scripts/");
	scriptPath.append(scriptFile);
	if(Verify_Exists(scriptPath.c_str(),false)){
		return m_pLUAModule->RunScript(scriptPath.c_str());
	}
	else{
		Error("LUA Script not found! Missing File: %s", scriptPath);
		return false;
	}
	return true;
}

void Davinci::Engine_Log(const char *message)
{
	Log(message);
}

void Davinci::Engine_Warning(const char *warning)
{
	Warning(warning);
}

void Davinci::Engine_Error(const char *error)
{
	Error(error);
}
void Davinci::Engine_FatalError(const char *fatal_error)
{
	FatalError(fatal_error);
}

void Davinci::SetResolution(int windowWidth, int windowHeight)
{
	Log("Switching Resolution to %d x %d.",windowWidth,windowHeight);
	m_pTimer->pause();
	m_pGUI->GUI_GrabTextures();
	m_pWindow->SetSize(windowWidth,windowHeight,m_pXMLSettings->GetFS());
	m_pGUI->GUI_RestoreTextures();
	m_pGUI->GUI_SetDisplaySize(windowWidth, windowHeight);
	m_pTimer->unpause();
}

void Davinci::SetFullscreen(bool fullscreen)
{
	if(fullscreen)
		Log("Switching to Fullscreen Mode.");
	else
		Log("Switching to Windowed Mode.");

	m_pTimer->pause();
	m_pGUI->GUI_GrabTextures();
	m_pWindow->SetSize(m_pXMLSettings->GetWidth(),m_pXMLSettings->GetHeight(),fullscreen);
	m_pGUI->GUI_RestoreTextures();
	m_pGUI->GUI_SetDisplaySize(m_pXMLSettings->GetWidth(),m_pXMLSettings->GetHeight());
	m_pTimer->unpause();
}

bool Davinci::IsFullscreen()
{
	return m_pXMLSettings->GetFS();
}

int Davinci::GetWindowHeight()
{
	int const height = m_pWindow->GetHeight();
	Log("Window Width: " + height);
	return height;
}

int Davinci::GetWindowWidth()
{
	int const width = m_pWindow->GetWidth();
	Log("Window Width: " + width);
	return width;
}

//////////////////////////////////////////////////////////////////////////
// MOVE THE FOLLOWING TO LUA SCRIPT GENERATED BY GAME EDITOR
//////////////////////////////////////////////////////////////////////////

// Engine Objects Functions
void Davinci::ClearScene()
{
	Log("Destroying all objects.");
	m_pScene->ClearScene();
}

bool Davinci::LoadActor(const char *type, float xPos, float yPos)
{
	if(Actor::LoadActor(type,xPos,yPos)){
		return true;
	}
	else{
		Error("Unable to load Actor Type %s. Check Log.",type);
		return false;
	}
}