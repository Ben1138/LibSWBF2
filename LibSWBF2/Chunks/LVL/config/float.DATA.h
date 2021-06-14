#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/RawData.h"
#include "DATA.h"
#include "Types/Enums.h"


namespace LibSWBF2::Chunks::LVL::config
{
	struct LIBSWBF2_API DATA_FLOAT : public DATA_CONFIG
	{
		List<float_t> m_Floats;
	
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	
		String ToString() const override;
	};
}
