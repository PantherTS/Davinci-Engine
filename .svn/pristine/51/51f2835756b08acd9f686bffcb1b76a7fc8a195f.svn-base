#include "RectangleCollider.h"

using namespace DavinciEngine;

//Note: collision is centered
// so 0,0 is the center of the sprite
// unless you set an offset (position)

RectangleCollider::RectangleCollider(float width, float height, Vec2D offset)
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

bool RectangleCollider::IntersectsPoint(const Vec2D& point, CollisionData *collisionData)
{
	//Vec2D ePos = GetObjectPosition();

	return (point.x > GetLeft() && point.y > GetTop() && point.x < GetRight() && point.y < GetBottom());
}

bool RectangleCollider::IntersectsLine(const Vec2D& start, const Vec2D& end, float lineRadius, CollisionData *collisionData)
{
	//TODO: Support line width!

	if (IntersectsPoint(start) || IntersectsPoint(end))
		return true;

	Vec2D pA = GetTopLeft();
	Vec2D pB = GetTopRight();
	Vec2D pC = GetBottomRight();
	Vec2D pD = GetBottomLeft();

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

Vec2D RectangleCollider::GetTopLeft(bool relativeToEntity)
{
	return Vec2D(GetLeft(relativeToEntity), GetTop(relativeToEntity));
}

Vec2D RectangleCollider::GetTopRight(bool relativeToEntity)
{
	return Vec2D(GetRight(relativeToEntity), GetTop(relativeToEntity));
}

Vec2D RectangleCollider::GetBottomLeft(bool relativeToEntity)
{
	return Vec2D(GetLeft(relativeToEntity), GetBottom(relativeToEntity));
}

Vec2D RectangleCollider::GetBottomRight(bool relativeToEntity)
{
	return Vec2D(GetRight(relativeToEntity), GetBottom(relativeToEntity));
}