#pragma once
#include <vector>
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Types
{
	using std::vector;

	struct Polygon
	{
		Polygon() = default;
		~Polygon() = default;

		vector<uint16_t> m_VertexIndices;
	};
}