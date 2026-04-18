#pragma once

#include <glm/glm.hpp>
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
		glm::vec2 hitPoint = glm::vec2(0.0f);

		/// <summary> The normal of the collision </summary>
		glm::vec2 normal = glm::vec2(0.0f);

		/// <summary> The penetration of the collider (how far into the collider we've moved) </summary>
		float penetration = 0.0f;
		
		/// <summary> The collider that was hit </summary>
		Collider *collider = nullptr;
	};
}