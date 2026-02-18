#pragma once
#include <LibSWBF2/Types/List.h>
#include <vector>

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API Polygon
	{
		Polygon() = default;
		~Polygon() = default;

		List<uint16_t> m_VertexIndices;
	};
}
