#include "Input.h"

using namespace DavinciEngine;

Input *Input::m_pInput = nullptr;
Framework *Input::m_pFramework = nullptr;

Input::Input(){
	for (int i = 0; i < static_cast<int>(KEY_MAX); i++){
		previousKeys[i] = false;
		currentKeys[i] = false;
	}

	for (int i = 0; i < MOUSE_BUTTON_MAX; i++){
		previousMouseButtons[i] = currentMouseButtons[i] = false;
	}

	m_pFramework = Framework::GetInstance();
}

Input::~Input(){
}

Input *Input::GetInstance(){
	if(!m_pInput){
		m_pInput = new Input();
	}
	return m_pInput;
}

void Input::Destroy(){
	if(m_pInput){
		delete m_pInput;
		m_pInput = nullptr;
	}
}

void Input::Update(){

	memcpy(previousKeys,currentKeys,KEY_MAX);
	memcpy(previousMouseButtons,currentMouseButtons,MOUSE_BUTTON_MAX);

	memcpy(currentKeys,m_pFramework->m_bKeys,KEY_MAX);
	memcpy(currentMouseButtons,m_pFramework->m_bMouseButtons,MOUSE_BUTTON_MAX);

	OnEvent();
}

Vec2D Input::GetMousePosition(){
	return m_pFramework->m_v2dMousePosition;
}

bool Input::IsMouseButtonHeld(MouseButton mouseButton){
	return (m_pFramework->m_bMouseButtons[mouseButton]) ? true:false;
}

bool Input::IsMouseButtonReleased(MouseButton mouseButton){
	return !(currentMouseButtons[mouseButton]) ? true:false;
}

bool Input::IsMouseButtonPressed(MouseButton mouseButton){
	return (currentMouseButtons[mouseButton]) ? true:false;
}

bool Input::IsKeyPressed(const SDL_KeyboardEvent& KeyCode){
	return currentKeys[KeyCode.keysym.sym] && !previousKeys[KeyCode.keysym.sym];
}

bool Input::IsKeyReleased(const SDL_KeyboardEvent& KeyCode){
	return !currentKeys[KeyCode.keysym.sym] && previousKeys[KeyCode.keysym.sym];
}

bool Input::IsKeyHeld(const SDL_KeyboardEvent& KeyCode)
{
	return currentKeys[KeyCode.keysym.sym];
}

void Input::OnEvent(){

	/*CEGUI::System::getSingleton().getDefaultGUIContext().injectMousePosition(static_cast<float>(m_pFramework->m_v2dMousePosition.x), static_cast<float>(m_pFramework->m_v2dMousePosition.y));

	if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::LeftButton);
	}
	if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::LeftButton);
	}

	if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::RightButton);
	}
	if(IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)){
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::RightButton);
	}

	if(IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)){
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(CEGUI::MiddleButton);
	}
	if(IsMouseButtonReleased(MOUSE_BUTTON_MIDDLE)){
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(CEGUI::MiddleButton);
	}

	if(IsMouseButtonPressed(MOUSE_BUTTON_WHEELUP)){
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseWheelChange( +1 );
	}
	if(IsMouseButtonPressed(MOUSE_BUTTON_WHEELDOWN)){
		CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseWheelChange( -1 );
	}*/
}