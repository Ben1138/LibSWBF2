#include "stdafx.h"
#include "Vector3.h"

namespace LibSWBF2
{
	Vector3::Vector3() : Vector2()
	{
		this->z = 0;
	}

	Vector3::Vector3(const float &x, const float &y, const float &z) : Vector2(x, y)
	{
		this->z = z;
	}
}