#pragma once
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Types
{
	struct Animation
	{
		static const int ANIMATION_NAME_STR_SIZE = 64;
		static const ChunkSize SIZE = ANIMATION_NAME_STR_SIZE + sizeof(float_t) + (sizeof(uint32_t) * 3);

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		string m_AnimationName;
		float_t m_FrameRate;
		uint32_t m_PlayStyle;
		uint32_t m_FirstFrame;
		uint32_t m_LastFrame;
	};
}