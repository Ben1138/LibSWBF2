#pragma once
#include "Chunks/GenericChunk.h"
#include "PTCH.VBUF.h"

namespace LibSWBF2::Chunks::LVL::terrain
{
	struct LIBSWBF2_API PTCH : public GenericChunk<"PTCH"_m>
	{
	public:
		List<VBUF*> m_Buffers;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}