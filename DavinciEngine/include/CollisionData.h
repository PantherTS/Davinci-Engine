#pragma once

#include "Vec2D.h"
#include "Collider.h"

namespace DavinciEngine
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Describes the result of a collision. Used to resolve collisions.</summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class CollisionData
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Default constructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		CollisionData();

		/// <summary> The position where the collision occurred </summary>
		Vec2D hitPoint;

		/// <summary> The normal of the collision </summary>
		Vec2D normal;

		/// <summary> The penetration of the collider (how far into the collider we've moved) </summary>
		float penetration;
		
		/// <summary> The collider that was hit </summary>
		Collider *collider;
	};
}