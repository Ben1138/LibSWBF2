#pragma once
#include "Vector3.h"

namespace LibSWBF2
{
	struct Vector4 : public Vector3
	{
		Vector4();
		Vector4(const float_t& x, const float_t& y, const float_t& z, const float_t& w);
		~Vector4();

		float_t w;
	};
}