#pragma once
#include "FileWriter.h"
#include "FileReader.h"
#include "TranslationFrame.h"
#include "RotationFrame.h"

namespace LibSWBF2::Types
{
	struct BoneFrames
	{
		uint32_t GetSize();
		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		uint32_t m_CRCchecksum;
		uint32_t m_KeyFrameType;

		vector<TranslationFrame> m_TranslationFrames;
		vector<RotationFrame> m_RotationFrames;
	};
}