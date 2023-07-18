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

	temp = new Button();

	//SDL_Window* m_pMainWindow = DavinciEngine::Window::GetWindow("Davinci Engine")->m_pScreen;
	
	// Start the OpenGL rendering system
	//renderer = &CEGUI::OpenGL3Renderer::create();

	// Create the LUA binds to the CEGUI system
	//script_module = &CEGUI::LuaScriptModule::create(LUAModule::GetInstance()->GetLuaState());

	// Create the LUA binds to the engine itself
	//lua_State *luaState = script_module->getLuaState();
	//tolua_LuaInterface_open(luaState);

	// Create the CEGUI System object
	//CEGUI::System::create (*renderer,0,0,0,script_module);

	// Create the default resource group paths
	//CEGUI::DefaultResourceProvider *rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
	//rp->setResourceGroupDirectory("schemes", "../gui/schemes/"); 
	//rp->setResourceGroupDirectory("layouts", "../gui/layouts/");
	//rp->setResourceGroupDirectory("looknfeels", "../gui/looknfeel/");
	//rp->setResourceGroupDirectory("imagesets", "../gui/imagesets/");
	//rp->setResourceGroupDirectory("fonts", "../gui/fonts/");
	//rp->setResourceGroupDirectory("schemas", "../gui/xml_schemas/"); 
	//rp->setResourceGroupDirectory("lua_scripts", "../data/lua_scripts/");

	// Set the default resource groups to be used
	//CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
	//CEGUI::Font::setDefaultResourceGroup("fonts");
	//CEGUI::Scheme::setDefaultResourceGroup("schemes");
	//CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	//CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	//CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");	

	// Setup default group for validation schemas
	//CEGUI::XMLParser *parser = CEGUI::System::getSingleton().getXMLParser();
	//if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
	//	parser->setProperty("SchemaDefaultResourceGroup", "schemas");
}

// GUI Input Functions for SDL
void GUI::OnExit()
{
	Davinci::Engine_GetInstance()->SetGameMode(0);
}

// Render the GUI
void GUI::GUI_Render( void )
{
	temp->Render();
	//CEGUI::System::getSingleton().renderAllGUIContexts();
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
	//CEGUI::System::getSingleton().notifyDisplaySizeChanged(Sizef(static_cast<float>(width), static_cast<float>(height)));
}