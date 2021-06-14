#pragma once
#include "req.h"

namespace LibSWBF2
{
	class FileWriter;
	class FileReader;
}

namespace LibSWBF2::Types
{
	struct String;

	struct LIBSWBF2_API Vector2
	{
		static const ChunkSize SIZE = sizeof(float_t) * 2;

		Vector2();
		Vector2(const float_t x, const float_t y);
		~Vector2();

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		float_t m_X = 0.0f;
		float_t m_Y = 0.0f;

		Types::String ToString() const;
	};
}