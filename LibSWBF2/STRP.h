#pragma once
#include "BaseChunk.h"
#include "Polygon.h"

namespace LibSWBF2::Chunks::Mesh
{
	using LibSWBF2::Types::Polygon;

	struct SEGM;

	struct STRP : public BaseChunk
	{
		STRP() = default;
		~STRP() = default;

		LIBSWBF2_EXP void CalcPolygons();

		// List of Triangle Strips. Each entry contains a vertex index (16 bit unsigned int)
		// Triangles are listed CW, CCW, CW, CCW, ...
		// The start of each Strip is indicated by two entries in a row where the high bit is set (0x8000)
		vector<uint16_t> m_Triangles;

		// Converted Triangle Strips to Polygons.
		// Call CalcPolygons() beforehand!
		vector<Polygon> m_Polygons;

	protected:
		friend SEGM;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}
