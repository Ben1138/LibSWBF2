#pragma once
#include "Chunks/GenericChunk.h"
#include "Chunks/STR.h"
#include "Types/Enums.h"

namespace LibSWBF2::Chunks::LVL::modl::segment
{
	struct LIBSWBF2_API INFO : public GenericChunk<"INFO"_m>
	{
	public:
		ETopology m_Topology;
		uint32_t m_VertexCount;
		uint32_t m_PrimitiveCount;

		EModelPurpose GetPurpose();

	public:
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		String ToString() override;
	};
}