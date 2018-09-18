#pragma once
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Types
{
	struct Color
	{
		static const ChunkSize Size = sizeof(float_t) * 4;

		Color();
		Color(const float_t& Red, const float_t& Green, const float_t& Blue);
		Color(const float_t& Red, const float_t& Green, const float_t& Blue, const float_t& Alpha);
		~Color();

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		float_t m_Red;
		float_t m_Green;
		float_t m_Blue;
		float_t m_Alpha;
	};
}