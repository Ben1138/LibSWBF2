#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/RawData.h"
#include "Chunks/LVL/common/DATA.h"
#include "Types/Enums.h"


using namespace LibSWBF2::Chunks::LVL::common;

namespace LibSWBF2::Chunks::LVL::lght
{
	struct LIBSWBF2_API DATA_STRING : public DATA
	{
		uint32_t m_Tag;
		String m_String;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}
