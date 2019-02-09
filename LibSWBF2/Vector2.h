#pragma once
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Types
{
	struct LIBSWBF2_EXP Vector2
	{
		static const ChunkSize SIZE = sizeof(float_t) * 2;

		Vector2();
		Vector2(const float_t& x, const float_t& y);
		~Vector2();

		virtual void WriteToStream(FileWriter& stream);
		virtual void ReadFromStream(FileReader& stream);

		float_t m_X = 0;
		float_t m_Y = 0;
	};
}