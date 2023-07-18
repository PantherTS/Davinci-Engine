#ifndef COLLIDER_H
#define COLLIDER_H

#include "Vec2D.h"
#include "FileNode.h"
#include "tinyxml2.h"
#include <stdio.h>

class tinyxml2::XMLDocument;
class tinyxml2::XMLElement;

namespace DavinciEngine{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Values that represent ColliderType. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	enum ColliderType
	{
		CT_RECT=0,
		CT_CIRCLE,
		CT_POLYGON,
		CT_PATH
	};

	class RectangleCollider;
	class Object;
	class CollisionData;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> Collider objects are assigned to objects that can collide with others. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Collider{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Default constructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Collider();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Destructor.</summary>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		~Collider();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Saves the Collider object and its properties to an external XML file.</summary>
		///
		/// <param name="document"> [in,out] If non-null, the tinyxml2::XMLDocument * to save.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void Save(tinyxml2::XMLDocument *document);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Loads the Collider object and its properties from an external XML file.</summary>
		///
		/// <param name="element"> [in,out] If non-null, the tinyxml2::XMLElement * to load.</param>
		///
		/// <returns> null if it fails, else.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static Collider *Load(tinyxml2::XMLElement *element);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Sets the Object that the Collider is associated with.</summary>
		///
		/// <param name="object"> [in,out] If non-null, the object.</param>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		void SetObject(Object *object);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Gets the Object that the Collider is associated with.</summary>
		///
		/// <returns> null if it fails, else the object.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Object *GetObject();

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Gets the object position.</summary>
		///
		/// <returns> The object position.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Vec2D GetObjectPosition();

		/// <summary> The offset of the collider object </summary>
		Vec2D offset;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Makes a deep copy of this object.</summary>
		///
		/// <returns> null if it fails, else a copy of this object.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual Collider *Clone() const = 0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Gets the collider type.</summary>
		///
		/// <returns> The collider type.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual ColliderType GetColliderType() = 0;

		//virtual bool IntersectsPoint(const Vec2D& point, CollisionData *collisionData=NULL)=0;
		//virtual bool IntersectsLine(const Vec2D& start, const Vec2D& end, float lineRadius = 0.0f, CollisionData *collisionData=NULL)=0;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Tests for collision between two Collider objects. Sets a CollisionData object
		/// 		  with information about the collision if one occurs.</summary>
		///
		/// <param name="a">			 [in,out] If non-null, a.</param>
		/// <param name="b">			 [in,out] If non-null, the b.</param>
		/// <param name="collisionData"> (optional) [in,out] If non-null, information describing the
		/// 							 collision.</param>
		///
		/// <returns> true if it succeeds, false if it fails.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static bool Collide(Collider *a, Collider *b, CollisionData *collisionData = NULL);

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Tests if two lines intersect.</summary>
		///
		/// <param name="aStart"> The start.</param>
		/// <param name="aEnd">   The end.</param>
		/// <param name="bStart"> The start.</param>
		/// <param name="bEnd">   The end.</param>
		///
		/// <returns> true if it succeeds, false if it fails.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static bool LinesIntersect(const Vec2D& aStart, const Vec2D& aEnd, const Vec2D& bStart, const Vec2D& bEnd);

	private:

		/// <summary> Pointer to the collider's associated Object </summary>
		Object *m_pObject;

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary> Tests if two rectangles have collided and sets a CollisionData object with
		/// 		  the results of the collision.</summary>
		///
		/// <param name="a">			 [in,out] If non-null, a.</param>
		/// <param name="b">			 [in,out] If non-null, the b.</param>
		/// <param name="collisionData"> [in,out] If non-null, information describing the collision.</param>
		///
		/// <returns> true if it succeeds, false if it fails.</returns>
		////////////////////////////////////////////////////////////////////////////////////////////////////
		static bool CollideRectRect(RectangleCollider *a, RectangleCollider *b, CollisionData *collisionData);

		//static bool CollideCircleCircle(CircleCollider *a, CircleCollider *b, CollisionData *collisionData);
		//static bool CollidePolygonPolygon(PolygonCollider *a, PolygonCollider *b, CollisionData *collisionData);

		//static bool CollideRectCircle(RectangleCollider *a, CircleCollider *b, CollisionData *collisionData);
		//static bool CollideRectPolygon(RectangleCollider *a, PolygonCollider *b, CollisionData *collisionData);
		//static bool CollideCirclePolygon(CircleCollider *a, PolygonCollider *b, CollisionData *collisionData);

		//static bool CollideCirclePath(CircleCollider *a, PathCollider *b, CollisionData *collisionData);
	};
}
#endif