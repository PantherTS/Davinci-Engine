#ifndef VEC2D_H
#define VEC2D_H

namespace DavinciEngine{
	class Vec2D
	{
	public:
		float x,y;

		static Vec2D zero;
		static Vec2D one;
		static Vec2D down;
		static Vec2D up;
		static Vec2D left;
		static Vec2D right;

		Vec2D(const Vec2D &vector2);
		Vec2D();
		Vec2D(float x, float y);

		/************************************************************
		* void Object::Vec2D::DistanceBetween(const Vec2D& other)	*
		*		Return the distance between two Vec2D structures.	*
		************************************************************/
		float DistanceBetween(const Vec2D& other);

		float operator[](int i);

		Vec2D& operator=(const Vec2D& rhs);
		bool operator==(const Vec2D& rhs);
		bool operator!=(const Vec2D& rhs);

		Vec2D& operator+=(const Vec2D& rhs);
		Vec2D& operator-=(const Vec2D& rhs);
		Vec2D& operator*=(float rhs);				// scalar multiplication
		Vec2D& operator/=(float rhs);				// scalar inverse multiplication
	};

	Vec2D operator+(const Vec2D& lhs, const Vec2D& rhs);	
	Vec2D operator-(const Vec2D& lhs, const Vec2D& rhs);
	Vec2D operator-(const Vec2D &rhs);

	Vec2D operator*(float lhs, const Vec2D& rhs);		// left scalar multiplication
	Vec2D operator*(const Vec2D& lhs, float rhs);		// right scalar multiplication
	Vec2D operator/(const Vec2D& lhs, float rhs);		// right scalar inverse multiplication
	Vec2D operator/(float lhs, const Vec2D &rhs);

	Vec2D operator*(const Vec2D& lhs, const Vec2D& rhs);	// multiply components (scale)
}
#endif	