#pragma once
#include "FileWriter.h"
#include "FileReader.h"
#include "Vector4.h"

namespace LibSWBF2::Types
{
	struct LIBSWBF2_EXP RotationFrame
	{
		static const ChunkSize SIZE = sizeof(uint32_t) + Vector4::SIZE;

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		uint32_t m_FrameIndex = 0;
		Vector4 m_Rotation;
	};
}