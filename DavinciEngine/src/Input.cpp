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

glm::vec2 Input::GetMousePosition() const{
	return m_pFramework->m_v2dMousePosition;
}

bool Input::IsMouseButtonHeld(MouseButton mouseButton) const{
	return (m_pFramework->m_bMouseButtons[mouseButton]) ? true:false;
}

bool Input::IsMouseButtonReleased(MouseButton mouseButton) const{
	return !(currentMouseButtons[mouseButton]) ? true:false;
}

bool Input::IsMouseButtonPressed(MouseButton mouseButton) const{
	return (currentMouseButtons[mouseButton]) ? true:false;
}

bool Input::IsKeyPressed(const SDL_KeyboardEvent& KeyCode) const{
	return currentKeys[KeyCode.key] && !previousKeys[KeyCode.key];
}

bool Input::IsKeyReleased(const SDL_KeyboardEvent& KeyCode) const{
	return !currentKeys[KeyCode.key] && previousKeys[KeyCode.key];
}

bool Input::IsKeyHeld(const SDL_KeyboardEvent& KeyCode) const{
	return currentKeys[KeyCode.key];
}

void Input::OnEvent(){

}