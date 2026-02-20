#pragma once
#include <LibSWBF2/Types/Vector2.h>

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API Vector3
	{
		static const ChunkSize SIZE = sizeof(float) * 3;

		Vector3();
		Vector3(const float x, const float y, const float z);
		~Vector3();

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		float m_X = 0.0f;
		float m_Y = 0.0f;
		float m_Z = 0.0f;

		String ToString() const;
	};
}