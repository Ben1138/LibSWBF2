#pragma once
#include "stdafx.h"

namespace LibSWBF2
{
	struct Color
	{
		Color();
		Color(const float_t& r, const float_t& g, const float_t& b);
		Color(const float_t& r, const float_t& g, const float_t& b, const float_t& a);
		~Color();

		float_t r;
		float_t g;
		float_t b;
		float_t a;
	};
}