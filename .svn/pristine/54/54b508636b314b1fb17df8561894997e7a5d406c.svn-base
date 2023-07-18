#include "XmlSettings.h"
#include "TXMLWrapper.h"

namespace DavinciEngine{

	XmlSettings* XmlSettings::m_XmlSettings = nullptr;

	/************************************************************
	* XmlSettings( void )										*
	*		Class constructor. Opens up the xml file we will be	*
	*	working with in this class.								*
	************************************************************/
	XmlSettings::XmlSettings ( void ) : xmlObj("settings.xml"){
	}

	/************************************************************
	* XmlSettings::~XmlSettings( void )							*
	*		Class destructor. Call Destroy() instead to			*
	*	properly delete and destroy the class.					*
	************************************************************/
	XmlSettings::~XmlSettings ( void ){
	}

	/************************************************************
	* GetInstance( void )										*
	*		Returns a reference to the class instance.			*
	************************************************************/
	XmlSettings* XmlSettings::GetInstance ( void ) {
		if (!m_XmlSettings) {
			if(!Verify_Exists("settings.xml",false)){
				XmlSettings::DefaultSettings();
			}

			m_XmlSettings = new XmlSettings();

			return m_XmlSettings;
		}
		else{
			return m_XmlSettings;
		}
	}

	/************************************************************
	* void XmlSettings::Destroy()								*
	*		Calls the class destructor.							*
	************************************************************/
	void XmlSettings::Destroy()
	{
		if(m_XmlSettings){
			delete m_XmlSettings;
			m_XmlSettings = nullptr;
		}
	}

	/************************************************************
	* void XmlSettings::DefaultSettings()						*
	*		Sets the default values for all settings and writes	*
	* the settings.xml file to the system directory.			*
	************************************************************/
	void XmlSettings::DefaultSettings(){
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLDeclaration* decl = doc.NewDeclaration();
		decl->SetValue("xml version=\"1.0\" encoding=""");
		doc.InsertEndChild(decl);
		tinyxml2::XMLNode* pRoot = doc.NewElement("settings");
		doc.InsertEndChild(pRoot);
		tinyxml2::XMLElement* window = doc.NewElement("window");
		window->SetAttribute("title","Davinci Engine");
		window->SetAttribute("width", 1024);
		window->SetAttribute("height", 768);
		window->SetAttribute("bpp", 32);
		window->SetAttribute("screen", 0);
		pRoot->InsertEndChild(window);
		doc.SaveFile( "settings.xml" );
	}

	//***********************************************************
	//* void XmlSettings::SetWidth()							*
	//*		Sets the width of the main game window in the 		*
	//*	settings.xml file to the integer parameter.				*
	//**********************************************************/
	void XmlSettings::SetWidth(int x){
		this->width = x;
	}

	//***********************************************************
	//* void XmlSettings::SetHeight()							*
	//*		Sets the height of the main game window in the 		*
	//*	settings.xml file to the integer parameter.				*
	//**********************************************************/
	void XmlSettings::SetHeight(int y){
		this->height = y;
	}

	//***********************************************************
	//* void XmlSettings::SetBPP()								*
	//*		Sets the static color depth variable.				*
	//**********************************************************/
	void XmlSettings::SetBPP(int colorDepth){
		this->bpp = colorDepth;
	}

	/************************************************************
	* void XmlSettings::SetFullscreen()							*
	*		Sets the static fullscreen variable.				*
	************************************************************/
	void XmlSettings::SetFullscreen(bool isFullscreen){
		this->fullscreen = isFullscreen;
	}

	/************************************************************
	* void XmlSettings::SaveSettings()							*
	*		Commits changes to the Settings.XML file in the 	*
	*	"system" directory.										*
	************************************************************/
	void XmlSettings::SaveSettings(){
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLDeclaration* decl = doc.NewDeclaration();
		decl->SetValue("xml version=\"1.0\" encoding=""");
		doc.InsertEndChild(decl);
		tinyxml2::XMLNode * pRoot = doc.NewElement( "settings" );
		doc.InsertEndChild(pRoot);
		tinyxml2::XMLElement * window = doc.NewElement( "window" );
		window->SetAttribute("title", this->title);
		window->SetAttribute("width", this->width);
		window->SetAttribute("height", this->height);
		window->SetAttribute("bpp", this->bpp);
		window->SetAttribute("screen", this->fullscreen);
		pRoot->InsertEndChild(window);
		doc.SaveFile( "settings.xml" );	
	}

	/************************************************************
	* void XmlSettings::LoadSettings()							*
	*		Gets the specs of the main game window from the		*
	*	settings.xml file.										*
	************************************************************/
	void XmlSettings::LoadSettings(){
		tinyxml2::XMLElement* pElem = nullptr;
		pElem = this->xmlObj.GetRoot()->FirstChild()->ToElement();

		pElem->QueryStringAttribute("title", &this->title);
		pElem->QueryIntAttribute("width", &this->width);
		pElem->QueryIntAttribute("height", &this->height);
		pElem->QueryIntAttribute("bpp", &this->bpp);
		pElem->QueryBoolAttribute("screen", &this->fullscreen);
	}
}