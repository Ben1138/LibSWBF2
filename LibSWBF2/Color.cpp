#include "stdafx.h"
#include "Color.h"
#include "Math.h"
#include "Logger.h"

namespace LibSWBF2
{
	Color::Color() : Color(0, 0, 0, 1) { }
	Color::Color(const float& r, const float& g, const float& b) : Color(r, g, b, 1) { }

	Color::Color(const float& r, const float& g, const float& b, const float& a) : 
		r(Math::Clamp01(r)), 
		g(Math::Clamp01(g)),
		b(Math::Clamp01(b)),
		a(Math::Clamp01(a))
	{
		
	}

	Color::~Color()
	{

	}
}