#pragma once
#include "Vector2.h"

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API Vector3
	{
		static const ChunkSize SIZE = sizeof(float_t) * 3;

		Vector3();
		Vector3(const float_t x, const float_t y, const float_t z);
		~Vector3();

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		float_t m_X = 0.0f;
		float_t m_Y = 0.0f;
		float_t m_Z = 0.0f;

		String ToString() const;
	};
}