#ifndef SYSTEMTYPES_H
#define SYSTEMTYPES_H

#include <math.h>

namespace DavinciEngine{

#define _W(t) L ## t

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary> A rectangle definition. </summary>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	struct Rect
	{
		Rect(float lx, float ly, float rx, float ry) noexcept : lx(lx), ly(ly), rx(rx), ry(ry) {}
		Rect() noexcept : lx(0.0f), ly(0.0f), rx(0.0f), ry(0.0f) {}

		void operator=(const Rect& other) noexcept {lx=other.lx;ly=other.ly;rx=other.rx;ry=other.ry;}

		float lx;
		float ly;
		float rx;
		float ry;
	};
};

#endif