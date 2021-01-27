#pragma once
#include "LibString.h"


namespace LibSWBF2
{
	class FileReader;
	class FileWriter;
}

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API Color4
	{
		static const ChunkSize SIZE = sizeof(float_t) * 4;

		Color4();
		Color4(const float_t Red, const float_t Green, const float_t Blue);
		Color4(const float_t Red, const float_t Green, const float_t Blue, const float_t Alpha);
		~Color4();

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

  		String ToString();

		float_t m_Red = 0.0f;
		float_t m_Green = 0.0f;
		float_t m_Blue = 0.0f;
		float_t m_Alpha = 0.0f;
	};
}