#include "Collision.h"

#include "Object.h"
#include <list>

#ifdef WIN32
	#undef GetObject
#endif

using namespace DavinciEngine;

Collision* Collision::m_pCollision = nullptr;

Collision::Collision() : m_iRefCount(0)
{
}

Collision* Collision::GetInstance()
{
	if(!m_pCollision){
		m_pCollision = new Collision();
	}
	return m_pCollision;
}

void Collision::Destroy()
{
	RemoveReference();
	if(m_iRefCount == 0){
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}

void Collision::RegisterColliderWithObject(Collider *collider, Object *object)
{
	collider->SetObject(object);
	AddReference();
	m_pCollision->colliders.push_back(collider);
}

void Collision::AddReference()
{
	m_iRefCount++;
}

void Collision::RemoveReference()
{
	m_iRefCount--;
}

void Collision::RemoveCollider(Collider *collider)
{
	m_pCollision->colliders.remove(collider);
}

Collider* Collision::Collide(Object *object, const std::string &tag, CollisionData *collisionData)
{
	Collider *passedCollider = object->GetCollider();
	if (passedCollider != nullptr)
	{
		for (std::list<Collider*>::iterator i = m_pCollision->colliders.begin(); i != m_pCollision->colliders.end(); ++i)
		{
			Object* otherObject = (*i)->GetObject();
			if (otherObject != nullptr && otherObject != object)
			{
				Collider* otherCollider = otherObject->GetCollider();
				if (otherCollider != nullptr && otherObject->HasTag(tag))
				{
					if (Collider::Collide(passedCollider, otherCollider, collisionData))
					{
						return otherCollider;
					}
				}
			}
		}
	}
	return nullptr;
}