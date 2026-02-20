#pragma once
#include <LibSWBF2/Types/Vector3.h>

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API Vector4
	{
		static const ChunkSize SIZE = sizeof(float) * 4;

		Vector4();
		Vector4(const float x, const float y, const float z, const float w);
		~Vector4();

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		float m_X = 0;
		float m_Y = 0;
		float m_Z = 0;
		float m_W = 0;

		String ToString() const;
	};
}