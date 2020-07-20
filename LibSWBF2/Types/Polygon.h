#pragma once
#include <vector>
#include "List.h"

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API Polygon
	{
		Polygon() = default;
		~Polygon() = default;

		List<uint16_t> m_VertexIndices;
	};
}