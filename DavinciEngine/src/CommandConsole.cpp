#include "LowLevelSystem.h"
#include "CommandConsole.h"
#include <Windows.h>

namespace DavinciEngine{

	cCommandConsole *cCommandConsole::m_pConsole;
	bool cCommandConsole::bConsoleOpen = false;
	std::deque<std::string>::iterator dqEnteredMessagesIt;

	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS
	//////////////////////////////////////////////////////////////////////////

	cCommandConsole::cCommandConsole() : bConsoleLoaded(false)
	{
	}

	cCommandConsole::~cCommandConsole()
	{
	}

	cCommandConsole *cCommandConsole::GetInstance( void )
	{
		if(!m_pConsole)
		{
			m_pConsole = new cCommandConsole();
			m_pConsole->CreateConsole();
		}
		return m_pConsole;
	}

	void cCommandConsole::Destroy()
	{
		if(m_pConsole){
			delete m_pConsole;
			m_pConsole = nullptr;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////

	void cCommandConsole::CreateConsole() {
		CEGUI::WindowManager& winMgr = CEGUI::WindowManager::getSingleton();
		m_pRootWindow = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

		CEGUI::FrameWindow *consoleFrame = static_cast<CEGUI::FrameWindow*>(winMgr.createWindow("TaharezLook/FrameWindow", "ConsoleFrame"));
		m_pRootWindow->addChild(consoleFrame);
		consoleFrame->setVisible(false);
		consoleFrame->setSize( CEGUI::USize( CEGUI::UDim( 1, 0 ), CEGUI::UDim( 0.32f, 0 ) ) );
		consoleFrame->setTitleBarEnabled( false );
		consoleFrame->setFrameEnabled( false );
		consoleFrame->setCloseButtonEnabled( false );
		consoleFrame->setAlpha( 0.6f );
		consoleFrame->setAlwaysOnTop( true );
		m_pRootWindow->addChild(consoleFrame);

		CEGUI::MultiLineEditbox *consoleWnd = static_cast<CEGUI::MultiLineEditbox*>(winMgr.createWindow("TaharezLook/MultiLineEditbox", "ConsoleOutput"));
		consoleWnd->setPosition( CEGUI::UVector2( CEGUI::UDim( 0, 0 ), CEGUI::UDim( 0, 0 ) ) );
		consoleWnd->setSize( CEGUI::USize( CEGUI::UDim( 1, 0 ), CEGUI::UDim( 0.8f, 0 ) ) );
		consoleWnd->setReadOnly( true );
		consoleWnd->setShowVertScrollbar( true );
		consoleWnd->setAlwaysOnTop( true );
		consoleFrame->addChild(consoleWnd);

		CEGUI::Editbox *consoleEntryWnd = static_cast<CEGUI::Editbox*>(winMgr.createWindow("TaharezLook/Editbox", "ConsoleInput"));
		consoleEntryWnd->setPosition( CEGUI::UVector2( CEGUI::UDim( 0, 0), CEGUI::UDim( 0.8f, 0) ) );
		consoleEntryWnd->setSize( CEGUI::USize( CEGUI::UDim( 1, 0 ), CEGUI::UDim( 0.2f, 0 ) ) );
		consoleEntryWnd->setAlwaysOnTop( true );
		consoleEntryWnd->subscribeEvent(CEGUI::Editbox::EventTextAccepted, CEGUI::Event::Subscriber( &cCommandConsole::CommandEntered,this ) );
		consoleFrame->addChild(consoleEntryWnd);

		// Setup the pointers for the rest of the class to use.
		m_pConsoleFrame = m_pRootWindow->getChild("ConsoleFrame");
		m_pConsoleOutput = m_pRootWindow->getChild("ConsoleOutput");
		m_pConsoleInput = m_pRootWindow->getChild("ConsoleInput");

		bConsoleLoaded = true;
	}

	void cCommandConsole::PopulateEntry(bool down) {
		if(dqEnteredMessages.empty())
			m_pConsoleInput->setText("");
		else {
			switch (down)
			{
			// User pressed the UP Arrow key in command console entry box.
			case false:
				if(!bCommandHistory) {
					bCommandHistory = true;
					break;
				}
				else if(dqEnteredMessagesIt != dqEnteredMessages.end()) {
					dqEnteredMessagesIt++;
					break;
				}
				else {
					dqEnteredMessagesIt--;
					break;
				}
			// User pressed the DOWN Arrow key in command console entry box.
			case true:
				if(dqEnteredMessagesIt != dqEnteredMessages.begin()) {
					dqEnteredMessagesIt--;
				}
				break;
			}

			if(dqEnteredMessagesIt == dqEnteredMessages.end())
				dqEnteredMessagesIt--;

			m_pConsoleInput->setText(std::string(*dqEnteredMessagesIt));
		}
	}

	void cCommandConsole::Toggle( void ) {
		if(!bConsoleLoaded){
			CreateConsole();
		}

		// Toggle the visibility of the console
		if(!m_pConsoleFrame->isVisible())
		{
			// Pause the game while the log is open.
			Timer::GetInstance()->pause();
			Log("Command Console Opened.");
			m_pConsoleFrame->setVisible(true);
			static_cast<CEGUI::Editbox*>(m_pConsoleInput)->hasInputFocus();
			static_cast<CEGUI::MultiLineEditbox*>(m_pConsoleOutput)->setCaretIndex((size_t)-1);
			bConsoleOpen = true;
		}
		else
		{
			// Un-pause the game while the console is not open.
			m_pConsoleFrame->setVisible(false);
			m_pConsoleInput->setText("");
			Timer::GetInstance()->unpause();
			bConsoleOpen = false;
		}
		
		// Reset the iterator for the command entry box to the beginning and the history boolean to false.
		dqEnteredMessagesIt = dqEnteredMessages.begin();
		bCommandHistory = false;
	}

	bool cCommandConsole::CommandEntered(const CEGUI::EventArgs &e)	{
		CEGUI::String engineShortcut = "DavinciEngine.Davinci:Engine_GetInstance():";

		CEGUI::String consoleCommand = static_cast<CEGUI::String>(m_pConsoleInput->getText());

		if(dqEnteredMessages.size() > 50) {
			dqEnteredMessages.pop_back();
		}
		dqEnteredMessages.push_front(consoleCommand.c_str());

		// Attempt to execute the command inside the engine.  If the command fails then catch the exception and write to the console window.
		std::string outputMsg = "Command ";

		try
		{
			CEGUI::System::getSingleton().executeScriptString(engineShortcut + consoleCommand);
			outputMsg += "Executed: ";
			outputMsg += consoleCommand.c_str();
			Log(outputMsg.c_str());
		}
		catch (CEGUI::Exception &exception)
		{
			outputMsg += "Not Found: ";
			outputMsg += consoleCommand.c_str();
			Log(outputMsg.c_str());
			Error("Command Exception: %s",exception.getMessage().c_str());
		}

		static_cast<CEGUI::MultiLineEditbox*>(m_pConsoleOutput)->setCaretIndex((size_t)-1);
		m_pConsoleOutput->appendText(outputMsg);
		m_pConsoleInput->setText("");

		// Reset the iterator for the command entry box to the beginning and the history boolean to false.
		dqEnteredMessagesIt = dqEnteredMessages.begin();
		bCommandHistory = false;

		return true;
	}
};