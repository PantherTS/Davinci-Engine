#include "ModeManager.h"
#include "windows.h"

using namespace DavinciEngine;

ModeManager *ModeManager::m_ModeManager = nullptr;

int ModeManager::gameMode = 1;

// Class constructor.
ModeManager::ModeManager()
{
}

// Class destructor.
ModeManager::~ModeManager()
{
}

/************************************************************
* ModeManager::Destroy()									*
*		Deletes the instance of the class.					*
************************************************************/
void ModeManager::Destroy( void )
{
	if(m_ModeManager){
		delete m_ModeManager;
		m_ModeManager = nullptr;
	}
}

// Class Singleton reference
ModeManager *ModeManager::GetInstance( void ){

	if (!m_ModeManager) {
		m_ModeManager = new ModeManager();
	}

	return m_ModeManager;
}