#pragma once
#include "Vector4.h"

namespace LibSWBF2::Types
{
	class FileWriter;
	class FileReader;

	struct LIBSWBF2_API RotationFrame
	{
		static const ChunkSize SIZE = sizeof(uint32_t) + Vector4::SIZE;

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		uint32_t m_FrameIndex = 0;
		Vector4 m_Rotation;
	};
}