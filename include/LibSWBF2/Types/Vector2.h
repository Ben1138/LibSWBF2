#pragma once
#include <LibSWBF2/req.h>

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
		static const ChunkSize SIZE = sizeof(float) * 2;

		Vector2();
		Vector2(const float x, const float y);
		~Vector2();

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		float m_X = 0.0f;
		float m_Y = 0.0f;

		Types::String ToString() const;
	};
}