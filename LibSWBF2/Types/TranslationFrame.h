#pragma once
#include "Vector3.h"

namespace LibSWBF2
{
	class FileReader;
	class FileWriter;
}

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API TranslationFrame
	{
		static const ChunkSize SIZE = sizeof(uint32_t) + Vector3::SIZE;

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		uint32_t m_FrameIndex = 0;
		Vector3 m_Translation;
	};
}