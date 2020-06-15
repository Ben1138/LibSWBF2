#pragma once
#include "Types\LibString.h"

namespace LibSWBF2::Types
{
	class FileReader;
	class FileWriter;

	struct LIBSWBF2_API Animation
	{
		static const int ANIMATION_NAME_STR_SIZE = 64;
		static const ChunkSize SIZE = ANIMATION_NAME_STR_SIZE + sizeof(float_t) + (sizeof(uint32_t) * 3);

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		String m_AnimationName;
		float_t m_FrameRate = 0.0f;
		uint32_t m_PlayStyle = 0;
		uint32_t m_FirstFrame = 0;
		uint32_t m_LastFrame = 0;
	};
}