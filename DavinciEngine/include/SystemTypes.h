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
        float lx;
        float ly;
        float rx;
        float ry;

        Rect(float lx, float ly, float rx, float ry) noexcept : lx(lx), ly(ly), rx(rx), ry(ry) {}
        Rect() noexcept : lx(0.0f), ly(0.0f), rx(0.0f), ry(0.0f) {}

        Rect& operator=(const Rect& other) = delete;

        bool operator==(const Rect& other) const = default;

        Rect(const Rect&) = default;
        Rect(Rect&&) = default;
        ~Rect() = default;
    };
};

#endif