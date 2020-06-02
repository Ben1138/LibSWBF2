#pragma once
#include "Chunks\BaseChunk.h"
#include "Types\Polygon.h"

namespace LibSWBF2::Chunks::Mesh
{
	using LibSWBF2::Types::Polygon;

	struct SEGM;

	struct LIBSWBF2_EXP STRP : public BaseChunk
	{
		STRP() = default;
		~STRP() = default;

		void CalcPolygons();

		// List of Triangle Strips. Each entry contains a vertex index (16 bit unsigned int)
		// Triangles are listed CW, CCW, CW, CCW, ...
		// The start of each Strip is indicated by two entries in a row where the high bit is set (0x8000)
		List<uint16_t> m_Triangles;

		// Converted Triangle Strips to Polygons. Each polygon consits of 3 vertex indices
		// Call CalcPolygons() beforehand!
		List<Polygon> m_Polygons;

	protected:
		friend SEGM;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}
