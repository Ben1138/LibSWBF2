#pragma once

namespace LibSWBF2
{
	struct Vector2
	{
		Vector2();
		Vector2(const float_t& x, const float_t& y);
		~Vector2();

		float_t x;
		float_t y;
	};
}