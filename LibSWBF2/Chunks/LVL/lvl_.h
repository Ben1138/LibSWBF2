#pragma once
#include "Chunks\GenericChunk.h"
#include "Chunks\STR.h"

namespace LibSWBF2::Chunks::LVL
{
	struct LIBSWBF2_API lvl_ : public GenericChunk<"lvl_"_m>
	{
	public:
		uint32_t m_NameHash;
		uint32_t m_SizeLeft;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}