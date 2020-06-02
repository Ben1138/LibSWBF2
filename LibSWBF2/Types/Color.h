#pragma once
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Types
{
	struct LIBSWBF2_EXP Color
	{
		static const ChunkSize SIZE = sizeof(float_t) * 4;

		Color();
		Color(const float_t& Red, const float_t& Green, const float_t& Blue);
		Color(const float_t& Red, const float_t& Green, const float_t& Blue, const float_t& Alpha);
		~Color();

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		float_t m_Red = 0.0f;
		float_t m_Green = 0.0f;
		float_t m_Blue = 0.0f;
		float_t m_Alpha = 0.0f;
	};
}