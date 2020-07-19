#pragma once
#include "Chunks/GenericChunk.h"

namespace LibSWBF2::Chunks::LVL::modl
{
	// The indices specified in here do NOT point to the actual Bone index
	// in the skeleton (skel chunk), but to an index in the Bone Map
	// (BMAP) chunk. The resulting index from BMAP then points to the
	// actual Bone indexy in the skeleton (skel chunk)
	struct LIBSWBF2_API SKIN : public GenericChunk<"SKIN"_m>
	{
	public:
		uint32_t m_VertexCount;
		uint32_t m_Type;		// num skins? or stride size? or a type?

		// Size of Vertex Count, stores the bone index
		// a particular vertex is attached to
		List<uint8_t> m_BoneIndices;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}