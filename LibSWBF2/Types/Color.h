#pragma once
#include "LibString.h"
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API Color
	{
		static const ChunkSize SIZE = sizeof(uint8_t) * 4;

		Color();
		Color(const uint8_t Red, const uint8_t Green, const uint8_t Blue);
		Color(const uint8_t Red, const uint8_t Green, const uint8_t Blue, const uint8_t Alpha);
		~Color();

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		String ToString();

		uint8_t m_Red = 0;
		uint8_t m_Green = 0;
		uint8_t m_Blue = 0;
		uint8_t m_Alpha = 0;
	};
}