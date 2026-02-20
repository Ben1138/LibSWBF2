#pragma once
#include <LibSWBF2/Types/TranslationFrame.h>
#include <LibSWBF2/Types/RotationFrame.h>
#include <LibSWBF2/Types/List.h>

namespace LibSWBF2
{
	class FileReader;
	class FileWriter;
}

namespace LibSWBF2::Types
{
	struct LIBSWBF2_API BoneFrames
	{
		uint32_t GetDataSize();
		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		CRCChecksum m_CRCchecksum = 0;		// The Bone this refers to
		uint32_t m_KeyFrameType = 0;

		List<TranslationFrame> m_TranslationFrames;
		List<RotationFrame> m_RotationFrames;
	};
}