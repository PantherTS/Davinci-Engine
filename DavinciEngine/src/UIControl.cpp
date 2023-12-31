#include "UIControl.h"
#include "Graphic.h"
#include "FileNode.h"
#include "XMLFileNode.h"
#include "GL/glew.h"

using namespace DavinciEngine;

UIControl::UIControl() : Transform(), m_pInput(nullptr), m_pGraphic(nullptr), m_bIsEnabled(false)
{
}

UIControl::~UIControl()
{
}

void UIControl::Update()
{
	// Virtual function
}

void UIControl::Render()
{
	if (this->m_bIsEnabled) {
		glPushMatrix();
		glTranslatef(position.x, position.y, 0.0);
		glColor3f(1.0f, 0.0f, 0.0f);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
		glVertex2f(-100, 100);
		glVertex2f(-100, -100);
		glVertex2f(100, -100);
		glVertex2f(100, 100);
		glEnd();
		glEnable(GL_TEXTURE_2D);
		glColor3f(1.0f, 1.0f, 1.0f);
		/*if (m_pGraphic != nullptr)
		{
			//Graphics::SetColor(color);
			m_pGraphic->Render();
		}*/

		glPopMatrix();
	}
}

void UIControl::InputChecks()
{
	// Virtual function
}

const bool UIControl::IsEnabled()
{
	return this->m_bIsEnabled;
}