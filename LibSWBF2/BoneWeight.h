#pragma once
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Types
{
	struct BoneWeight
	{
		static const ChunkSize Size = sizeof(float_t) + sizeof(uint32_t);

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		uint32_t m_EnvelopeIndex;
		float_t m_WeightValue;		// 0.0-1.0
	};
}