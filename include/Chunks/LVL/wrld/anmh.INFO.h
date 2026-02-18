#pragma once
#include "Chunks/GenericChunk.h"


namespace LibSWBF2::Chunks::LVL::wrld
{
	struct LIBSWBF2_API anmh_INFO : public GenericChunk<"INFO"_m>
	{
	public:

		uint8_t m_NumStrings;

		String m_RootName;
		List<String> m_ChildNames;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
		
		String ToString() const override;
	};
}