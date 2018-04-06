#include "Vector4.h"

namespace LibSWBF2
{
	namespace Types
	{
		Vector4::Vector4() : Vector3()
		{
			this->w = 0;
		}

		Vector4::Vector4(const float &x, const float &y, const float &z, const float &w) : Vector3(x, y, z)
		{
			this->w = w;
		}
	}
}