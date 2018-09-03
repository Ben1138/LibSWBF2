#include "stdafx.h"
#include "Color.h"
#include "Math.h"
#include "Logger.h"

namespace LibSWBF2
{
	Color::Color() : Color(0, 0, 0, 1) { }
	Color::Color(const float_t& r, const float_t& g, const float_t& b) : Color(r, g, b, 1) { }

	Color::Color(const float_t& r, const float_t& g, const float_t& b, const float_t& a) : 
		r(Math::Clamp01(r)), 
		g(Math::Clamp01(g)),
		b(Math::Clamp01(b)),
		a(Math::Clamp01(a))
	{
		
	}

	Color::~Color()
	{

	}

	void Color::WriteToStream(ofstream& stream)
	{
		stream << r << g << b << a;
	}

	void Color::ReadFromStream(ifstream& stream)
	{
		stream >> r >> g >> b >> a;
	}
}