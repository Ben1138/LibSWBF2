#pragma once
#include "Vector3.h"

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API Vector4
	{
		static const ChunkSize SIZE = sizeof(float_t) * 4;

		Vector4();
		Vector4(const float_t x, const float_t y, const float_t z, const float_t w);
		~Vector4();

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		float_t m_X = 0;
		float_t m_Y = 0;
		float_t m_Z = 0;
		float_t m_W = 0;

		String ToString();
	}__attribute__((aligned(4), packed));
}