#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"

namespace LibSWBF2::Chunks::LVL::terrain
{
	struct LIBSWBF2_API INFO : public GenericChunk<"INFO"_m>
	{
	public:
		float_t m_GridUnitSize;
		float_t m_HeightScale;
		float_t m_HeightFloor;		// lowest Y value in all vertex buffers
		float_t m_HeightCeiling;	// heighest Y value in all vertex buffers
		uint16_t m_GridSize;
		uint16_t m_PatchEdgeSize;	// number of vertices per patch edge
		uint16_t m_TexturePatches;
		uint16_t m_TextureCount;
		uint16_t m_MaxTextureLayers;
		uint16_t m_Unknown;

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() const override;
	};
}