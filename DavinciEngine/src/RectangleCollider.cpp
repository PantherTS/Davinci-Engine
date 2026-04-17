#include "RectangleCollider.h"

using namespace DavinciEngine;

//Note: collision is centered
// so 0,0 is the center of the sprite
// unless you set an offset (position)

RectangleCollider::RectangleCollider(float width, float height, glm::vec2 offset)
	: Collider()
{
	this->offset	= offset;
	this->width		= width;
	this->height	= height;
}

// Copy Constructor
RectangleCollider::RectangleCollider(RectangleCollider const &other)
	: Collider()
{
	this->offset	= other.offset;
	this->width		= other.width;
	this->height	= other.height;
}

ColliderType RectangleCollider::GetColliderType()
{
	return CT_RECT;
}

bool RectangleCollider::IntersectsPoint(const glm::vec2& point, CollisionData *collisionData)
{
	//glm::vec2 ePos = GetObjectPosition();

	return (point.x > GetLeft() && point.y > GetTop() && point.x < GetRight() && point.y < GetBottom());
}

bool RectangleCollider::IntersectsLine(const glm::vec2& start, const glm::vec2& end, float lineRadius, CollisionData *collisionData)
{
	//TODO: Support line width!

	if (IntersectsPoint(start) || IntersectsPoint(end))
		return true;

	glm::vec2 pA = GetTopLeft();
	glm::vec2 pB = GetTopRight();
	glm::vec2 pC = GetBottomRight();
	glm::vec2 pD = GetBottomLeft();

	return (LinesIntersect(start, end, pA, pB) || LinesIntersect(start, end, pB, pC) || LinesIntersect(start, end, pC, pD) || LinesIntersect(start, end, pD, pA));
}

float RectangleCollider::GetRight(bool relativeToEntity)
{
	if (relativeToEntity)
		return offset.x + width*0.5f;
	else
		return GetObjectPosition().x + offset.x + width*0.5f;
}

float RectangleCollider::GetLeft(bool relativeToEntity)
{
	if (relativeToEntity)
		return offset.x - width*0.5f;		
	else
		return GetObjectPosition().x + offset.x - width*0.5f;
}

float RectangleCollider::GetTop(bool relativeToEntity)
{
	if (relativeToEntity)
		return offset.y - height*0.5f;
	else
		return GetObjectPosition().y + offset.y - height*0.5f;	
}

float RectangleCollider::GetBottom(bool relativeToEntity)
{
	if (relativeToEntity)
		return offset.y + height*0.5f;	
	else
		return GetObjectPosition().y + offset.y + height*0.5f;
}

glm::vec2 RectangleCollider::GetTopLeft(bool relativeToEntity)
{
	return glm::vec2(GetLeft(relativeToEntity), GetTop(relativeToEntity));
}

glm::vec2 RectangleCollider::GetTopRight(bool relativeToEntity)
{
	return glm::vec2(GetRight(relativeToEntity), GetTop(relativeToEntity));
}

glm::vec2 RectangleCollider::GetBottomLeft(bool relativeToEntity)
{
	return glm::vec2(GetLeft(relativeToEntity), GetBottom(relativeToEntity));
}

glm::vec2 RectangleCollider::GetBottomRight(bool relativeToEntity)
{
	return glm::vec2(GetRight(relativeToEntity), GetBottom(relativeToEntity));
}