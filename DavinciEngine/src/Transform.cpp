#include "Transform.h"
#include "FileNode.h"
#include "Vec2D.h"

using namespace DavinciEngine;

Transform::Transform() : position(Vec2D::zero), rotation(0.0f), scale(Vec2D::one), m_iLayer(NULL)
{
}

Transform::Transform(const Transform &transform) : position(transform.position), rotation(transform.rotation), scale(transform.scale), m_iLayer(NULL)
{
}

Transform::~Transform()
{
}

void Transform::Save(FileNode *fileNode)
{
	if (fileNode)
	{
		if (position != Vec2D::zero)
			fileNode->Write("position", position);
		if (rotation != 0)
			fileNode->Write("rotation", rotation);
		if (scale != Vec2D::one)
			fileNode->Write("scale", scale);
	}
}

void Transform::Load(FileNode *fileNode)
{
	if (fileNode)
	{
		fileNode->Read("position", position);
		fileNode->Read("rotation", rotation);
		fileNode->Read("scale", scale);
	}
}