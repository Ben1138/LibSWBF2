#pragma once
#include "Types/LibString.h"

namespace LibSWBF2
{
	class FileWriter;
	class FileReader;
}

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API Vector3u8
	{
		static const ChunkSize SIZE = sizeof(uint8_t) * 3;

		Vector3u8();
		Vector3u8(const uint8_t x, const uint8_t y, const uint8_t z);
		~Vector3u8();

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		uint8_t m_X = 0;
		uint8_t m_Y = 0;
		uint8_t m_Z = 0;

		String ToString() const;
	};
}