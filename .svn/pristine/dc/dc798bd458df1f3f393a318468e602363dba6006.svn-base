#include "Graphic.h"
#include "Framework.h"
#include "TextureAsset.h"

#include "gl/glew.h"

using namespace DavinciEngine;

OpenGLFunctions::OpenGLFunctions()
{
}

OpenGLFunctions::~OpenGLFunctions()
{
}

void OpenGLFunctions::SetBlend(BlendType blend)
{
	switch (blend)
	{
	case BLEND_ALPHA:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		break;
	case BLEND_ADDITIVE:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		break;
	case BLEND_MULTIPLY:
		glBlendFunc(GL_ZERO, GL_SRC_COLOR);
		break;
	default:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}

void OpenGLFunctions::MakeQuad(float width, float height, const Vec2D &textureOffset, const Vec2D &textureScale, const Vec2D &position)
{
	const float halfWidth = width*0.5f;
	const float halfHeight = height*0.5f;

	glBegin(GL_QUADS);
	//Top Left
	glTexCoord2f(textureOffset.x, textureOffset.y);
	glVertex3f(halfWidth + position.x, halfHeight + position.y, 0.0f);

	//Bottom Left
	glTexCoord2f(textureOffset.x + textureScale.x, textureOffset.y);
	glVertex3f(-halfWidth + position.x, halfHeight + position.y, 0.0f);

	//Bottom Right
	glTexCoord2f(textureOffset.x + textureScale.x, textureOffset.y + textureScale.y);
	glVertex3f(-halfWidth + position.x, -halfHeight + position.y, 0.0f);

	//Top Right
	glTexCoord2f(textureOffset.x, textureOffset.y + textureScale.y);
	glVertex3f(halfWidth + position.x, -halfHeight + position.y, 0.0f);
	glEnd();
}