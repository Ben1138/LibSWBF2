#include "stdafx.h"
#include "Color.h"
#include "Math.h"
#include "Logger.h"

namespace LibSWBF2
{
	Color::Color() : Color(0, 0, 0, 0) { }
	Color::Color(const float &r, const float &g, const float &b) : Color(r, g, b, 0) { }

	Color::Color(const float &r, const float &g, const float &b, const float&a)
	{
		this->r = Math::Clamp01(r);
		this->g = Math::Clamp01(g);
		this->b = Math::Clamp01(b);
		this->a = Math::Clamp01(a);

		Logger::Add("New Color added!", ELogType::Info);
	}

	Color::~Color()
	{

	}
}