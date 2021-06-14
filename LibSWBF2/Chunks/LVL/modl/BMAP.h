#pragma once
#include "Chunks/GenericChunk.h"

namespace LibSWBF2::Chunks::LVL::modl
{
	// This chunk maps local Bone indices to "global" ones,
	// indexing a bone in the skeleton (skel) chunk.

	// IDK why the hell they did this, instead of just putting the
	// indices directly into the SKIN chunk and get rid of this mapper
	// entirely...

	struct LIBSWBF2_API BMAP : public GenericChunk<"BMAP"_m>
	{
	public:
		uint32_t m_IndexCount;

		// maps local bone indices from SKIN to bones
		// indices in the skeleton (skel) chunk
		List<uint8_t> m_IndexMap;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}
