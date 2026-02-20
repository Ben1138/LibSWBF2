#pragma once
#include <LibSWBF2/Chunks/GenericChunk.h>
#include <LibSWBF2/Chunks/RawData.h>
#include <LibSWBF2/Chunks/LVL/config/DATA.h>
#include <LibSWBF2/Types/Enums.h>


namespace LibSWBF2::Chunks::LVL::config
{
	struct LIBSWBF2_API DATA_FLOAT : public DATA_CONFIG
	{
		List<float> m_Floats;
	
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	
		String ToString() const override;
	};
}
