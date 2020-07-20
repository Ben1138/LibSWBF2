#pragma once
#include "Chunks/GenericChunk.h"
#include "PTCH.h"

namespace LibSWBF2::Chunks::LVL::terrain
{
	struct LIBSWBF2_API PCHS : public GenericChunk<"PCHS"_m>
	{
	public:
		List<PTCH*> m_Patches;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}