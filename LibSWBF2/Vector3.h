#pragma once
#include "Vector2.h"

namespace LibSWBF2
{
	class Vector3 : public Vector2
	{
	public:
		float z;

		Vector3();
		Vector3(const float &x, const float &y, const float &z);
	};
}