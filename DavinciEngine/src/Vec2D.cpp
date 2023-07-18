#include "Vec2D.h"
#include <math.h>

using namespace DavinciEngine;

Vec2D Vec2D::zero = Vec2D(0, 0);
Vec2D Vec2D::one = Vec2D(1, 1);
Vec2D Vec2D::up = Vec2D(0, -1);
Vec2D Vec2D::down = Vec2D(0, 1);
Vec2D Vec2D::left = Vec2D(-1, 0);
Vec2D Vec2D::right = Vec2D(1, 0);

Vec2D::Vec2D() : x(0.0f), y(0.0f)
{
}

Vec2D::Vec2D(float x, float y) : x(x), y(y)
{
}

Vec2D::Vec2D(const Vec2D &vec2d) : x(vec2d.x), y(vec2d.y)
{
}

float Vec2D::DistanceBetween(const Vec2D& other)
{
	return static_cast<float>( sqrt( ( ( static_cast<double>(other.x) - static_cast<double>(x) ) * ( static_cast<double>(other.x) - static_cast<double>(x) ) ) + ( ( static_cast<double>(other.y) - static_cast<double>(y) ) * ( static_cast<double>(other.y) - static_cast<double>(y) ) ) ) );
}

float Vec2D::operator[](int i)
{
	if (i <= 0)
	{
		return x;
	}
	else
	{
		return y;
	}
}

Vec2D& Vec2D::operator=(const Vec2D& rhs)
{
	if (&rhs != this)
	{
		x = rhs.x;
		y = rhs.y;
	}
	return *this;
}

bool Vec2D::operator==(const Vec2D& rhs)
{
	return ((x == rhs.x) && (y == rhs.y));
}

bool Vec2D::operator!=(const Vec2D& rhs)
{
	return ((x != rhs.x) || (y != rhs.y));
}

Vec2D& Vec2D::operator+=(const Vec2D& rhs)
{
	x = x + rhs.x;
	y = y + rhs.y;
	return *this;
}

Vec2D& Vec2D::operator-=(const Vec2D& rhs)
{
	x = x - rhs.x;
	y = y - rhs.y;
	return *this;
}

Vec2D& Vec2D::operator*=(float rhs)				// scalar multiplication
{
	x = x * rhs;
	y = y * rhs;
	return *this;
}

Vec2D& Vec2D::operator/=(float rhs)				// scalar inverse multiplication
{
	x = x / rhs;
	y = y / rhs;
	return *this;
}

Vec2D DavinciEngine::operator+(const Vec2D& lhs, const Vec2D& rhs)
{
	return Vec2D(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vec2D DavinciEngine::operator-(const Vec2D& lhs, const Vec2D& rhs)
{
	return Vec2D(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vec2D DavinciEngine::operator-(const Vec2D &rhs)
{
	return Vec2D(-rhs.x, -rhs.y);
}

Vec2D DavinciEngine::operator/(float lhs, const Vec2D &rhs)
{
	return Vec2D(lhs / rhs.x, lhs / rhs.y);
}

Vec2D DavinciEngine::operator/(const Vec2D& lhs, float rhs)		// right scalar inverse multiplication
{
	return Vec2D(lhs.x / rhs, lhs.y / rhs);
}

Vec2D DavinciEngine::operator*(float lhs, const Vec2D& rhs)
{
	return Vec2D(lhs * rhs.x, lhs * rhs.y);		// left scalar multiplication
}

Vec2D DavinciEngine::operator*(const Vec2D& lhs, float rhs)
{
	return Vec2D(lhs.x * rhs, lhs.y * rhs);		// right scalar multiplication
}

Vec2D DavinciEngine::operator*(const Vec2D& lhs, const Vec2D& rhs)
{
	return Vec2D(lhs.x * rhs.x, lhs.y * rhs.y);	// multiply components (scale)
}