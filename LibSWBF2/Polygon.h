#pragma once
#include <vector>
#include "FileWriter.h"
#include "FileReader.h"
#include "List.h"

namespace LibSWBF2::Types
{
	struct LIBSWBF2_EXP Polygon
	{
		Polygon() = default;
		~Polygon() = default;

		List<uint16_t> m_VertexIndices;
	};
}