#pragma once

namespace LibSWBF2
{
	struct Color
	{
		Color();
		Color(const float& r, const float& g, const float& b);
		Color(const float& r, const float& g, const float& b, const float& a);
		~Color();

		float r;
		float g;
		float b;
		float a;
	};
}