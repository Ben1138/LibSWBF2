#pragma once

namespace LibSWBF2
{
	struct Color
	{
	public:
		float r;
		float g;
		float b;
		float a;

		Color();
		Color(const float &r, const float &g, const float &b);
		Color(const float &r, const float &g, const float &b, const float&a);
		~Color();
	};
}