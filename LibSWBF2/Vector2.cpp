#include "Vector2.h"

namespace LibSWBF2
{
	namespace Types
	{
		Vector2::Vector2()
		{
			this->x = 0;
			this->y = 0;
		}

		Vector2::Vector2(const float &x, const float &y)
		{
			this->x = x;
			this->y = y;
		}
	}
}