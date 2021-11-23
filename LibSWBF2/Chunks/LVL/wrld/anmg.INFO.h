#pragma once
#include "Chunks/GenericChunk.h"


namespace LibSWBF2::Chunks::LVL::wrld
{
	struct LIBSWBF2_API anmg_INFO : public GenericChunk<"INFO"_m>
	{
	public:

		String m_Name;
		
		uint8_t m_0;
		uint8_t m_1;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
		
		String ToString() const override;
	};
}