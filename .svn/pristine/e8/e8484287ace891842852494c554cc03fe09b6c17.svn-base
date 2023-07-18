#include "Camera.h"
#include "Graphic.h"

using namespace DavinciEngine;

Camera::Camera(const Camera& camera) : Transform(camera)
{
}

Camera::Camera() : Transform()
{
}

void Camera::ApplyMatrix()
{
	//OpenGLFunctions::GetInstance()->Scale(scale);
	glScalef(scale.x, scale.y, 1.0f);
	//OpenGLFunctions::GetInstance()->Translate(position * -1.0f);
	glTranslatef((position * -1.0f).x, (position * -1.0f).y, 0.0f);
	//OpenGLFunctions::GetInstance()->Rotate(rotation, 0, 0, 1);
	glRotatef(rotation, 0, 0, 1);
}