#pragma once
#include "Vector3.h"

namespace LibSWBF2
{
	struct Vector4 : public Vector3
	{
	public:
		float w;

		Vector4();
		Vector4(const float& x, const float& y, const float& z, const float& w);
		~Vector4();
	};
}