#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"

namespace LibSWBF2::Chunks::LVL::modl
{
	// Texture Name
	struct LIBSWBF2_API TNAM : public GenericChunk<"TNAM"_m>
	{
	public:
		uint32_t m_Index;
		String m_Name;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}