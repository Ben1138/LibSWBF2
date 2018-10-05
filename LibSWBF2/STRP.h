#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct STRP : public BaseChunk
	{
		STRP();
		~STRP();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		// List of Triangle Strips. Each entry contains a vertex index (16 bit unsigned int)
		// Triangles are listed CW, CCW, CW, CCW, ...
		// The start of each Strip is indicated by two entries in a row where the high bit is set (0x8000)
		vector<uint16_t> m_Triangles;
	};
}