#include "stdafx.h"
#include "Color.h"
#include "Logger.h"

namespace LibSWBF2::Types
{
	Color::Color() : Color(0, 0, 0, 1) { }
	Color::Color(const float_t& r, const float_t& g, const float_t& b) : Color(r, g, b, 1) { }

	Color::Color(const float_t& r, const float_t& g, const float_t& b, const float_t& a) : 
		r(clamp(r, 0.0f, 1.0f)),
		g(clamp(g, 0.0f, 1.0f)),
		b(clamp(b, 0.0f, 1.0f)),
		a(clamp(a, 0.0f, 1.0f))
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