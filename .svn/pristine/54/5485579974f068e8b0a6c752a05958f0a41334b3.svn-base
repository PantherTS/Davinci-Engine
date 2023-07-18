#include "Collider.h"
#include "RectangleCollider.h"
#include "Object.h"
#include <stdio.h>
#include "CollisionData.h"
#include "XMLFileNode.h"

#ifdef WIN32
	#undef GetObject
#endif

using namespace DavinciEngine;

Collider::Collider() : m_pObject(NULL)
{

}

Collider::~Collider()
{

}

void Collider::Save(tinyxml2::XMLDocument *document)
{
	tinyxml2::XMLElement * xmlCollision = document->NewElement("Collision");
	XMLFileNode xmlFileNode(xmlCollision);

	int type = 0;
	int width = 0;
	int height = 0;
	int offsetx = 0;
	int offsety = 0;

	switch (GetColliderType())
	{
	case CT_RECT:
		type = 0;
		width = 0;
		height = 0;
		offsetx = 0;
		offsety = 0;
		break;
	}

	xmlFileNode.Write("type",type);
	xmlFileNode.Write("width",width);
	xmlFileNode.Write("height",height);
	xmlFileNode.Write("offsetx",offsetx);
	xmlFileNode.Write("offsety",offsety);
}

Collider* Collider::Load(tinyxml2::XMLElement* element)
{
	Collider* m_pCollider = nullptr;
	XMLFileNode XMLFileNode(element);

	int type = 0;
	int width = 0;
	int height = 0;
	int offsetx = 0;
	int offsety = 0;

	XMLFileNode.Read("type",type);
	XMLFileNode.Read("width",width);
	XMLFileNode.Read("height",height);
	XMLFileNode.Read("offsetx",offsetx);
	XMLFileNode.Read("offsety",offsety);
	
	Vec2D offset(static_cast<float>(offsetx),static_cast<float>(offsety));

	switch (type)
	{
	case 0 :

		if(width==0 || height==0){
			Error("Height and Width must be defined for Collision Type 0.");
			break;
		}

		m_pCollider = new RectangleCollider(static_cast<float>(width),static_cast<float>(height),offset);
		break;
	/*case 1 :
		m_pCollider = new CircleCollider();
		break;
	case 2 :
		m_pCollider = new PolygonCollider();
		break;
	case 3 :
		m_pCollider = new PathCollider();
		break;*/
	default :
		Log("Collision type definition issue in XML.");
	}
	return m_pCollider;
}

void Collider::SetObject(Object* object)
{
	m_pObject = object;
}

Object* Collider::GetObject()
{
	return m_pObject;
}

Vec2D Collider::GetObjectPosition()
{
	if(m_pObject != nullptr){
		return m_pObject->position;
	}
	else{
		return Vec2D();		
	}
}

bool Collider::Collide(Collider* a, Collider* b, CollisionData *collisionData)
{
	ColliderType typeA = a->GetColliderType();
	ColliderType typeB = b->GetColliderType();

	//Big nasty if/else for deciding which collision function to use
	if (typeA == CT_RECT && typeB == CT_RECT)									//Rectangle - Rectangle
		return CollideRectRect((RectangleCollider*)a, (RectangleCollider*)b, collisionData);

	//else if (typeA == CT_CIRCLE && typeB == CT_CIRCLE)							//Circle - Circle
	//	return CollideCircleCircle((CircleCollider*)a, (CircleCollider*)b, collisionData);

	//else if (typeA == CT_POLYGON && typeB == CT_POLYGON)						//Polygon - Polygon
	//	return CollidePolygonPolygon((PolygonCollider*)a, (PolygonCollider*)b, collisionData);

	//else if (typeA == CT_RECT && typeB == CT_CIRCLE)							//Rectangle - Circle
	//	return CollideRectCircle((RectangleCollider*)a, (CircleCollider*)b, collisionData);
	//else if (typeA == CT_CIRCLE && typeB == CT_RECT)
	//	return CollideRectCircle((RectangleCollider*)b, (CircleCollider*)a, collisionData);

	//else if (typeA == CT_RECT && typeB == CT_POLYGON)							//Rectangle - Polygon
	//	return CollideRectPolygon((RectangleCollider*)a, (PolygonCollider*)b, collisionData);
	//else if (typeA == CT_POLYGON && typeB == CT_RECT)
	//	return CollideRectPolygon((RectangleCollider*)b, (PolygonCollider*)a, collisionData);

	//else if (typeA == CT_CIRCLE && typeB == CT_POLYGON)							//Circle - Polygon
	//	return CollideCirclePolygon((CircleCollider*)a, (PolygonCollider*)b, collisionData);
	//else if (typeA == CT_POLYGON && typeB == CT_CIRCLE)
	//	return CollideCirclePolygon((CircleCollider*)b, (PolygonCollider*)a, collisionData);

	//else if (typeA == CT_CIRCLE && typeB == CT_PATH)
	//	return CollideCirclePath((CircleCollider*)a, (PathCollider*)b, collisionData);
	//else if (typeA == CT_PATH && typeB == CT_CIRCLE)
	//	return CollideCirclePath((CircleCollider*)b, (PathCollider*)a, collisionData);

	//else if ((typeA == CT_RECT && typeB == CT_PATH) || (typeA == CT_PATH && typeB == CT_RECT))
	//{
	//	Debug::Log("Warning: Collisions between Rectangle and Path not yet supported.");
	//}
	else
	{
		Warning("Unhandled collider pair.");
	}

	// Unhandled case
	return false;
}

bool Collider::LinesIntersect(const Vec2D& aStart, const Vec2D& aEnd, const Vec2D& bStart, const Vec2D& bEnd)
{
	float d = ((bEnd.y - bStart.y) * (aEnd.x - aStart.x)) - ((bEnd.x - bStart.x) * (aEnd.y - aStart.y));
	float nX = ((bEnd.x - bStart.x) * (aStart.y - bStart.y)) - ((bEnd.y - bStart.y) * (aStart.x - bStart.x));
	float nY = ((aEnd.x - aStart.x) * (aStart.y - bStart.y)) - ((aEnd.y - aStart.y) * (aStart.x - bStart.x));

	//Lines are parallel if d == 0, so check if they're coincident
	if (d == 0.0f)
	{
		if (nX == 0.0f && nY == 0.0f)
		{
			//Lines are coincident, now check if they overlap
			return ((aEnd.x > bStart.x && aStart.x < bEnd.x) || (aEnd.y > bStart.y && aStart.y < bEnd.y));
		}
		else
			return false;
	}

	float uX = nX / d;
	float uY = nY / d;

	return (uX >= 0.0f && uX <= 1.0f && uY >= 0.0f && uY <= 1.0f);
}

bool Collider::CollideRectRect(RectangleCollider* a, RectangleCollider* b, CollisionData *collisionData)
{
	//TODO: store data in collisionData!

	if (a->GetBottom() < b->GetTop())
		return false;

	if (a->GetTop() > b->GetBottom())
		return false;

	if (a->GetRight() < b->GetLeft())
		return false;

	if (a->GetLeft() > b->GetRight())
		return false;

	return true;
}