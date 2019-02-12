#pragma once
#include "BaseChunk.h"
#include "MATD.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MSH2;

	struct LIBSWBF2_EXP MATL : public BaseChunk
	{
		MATL() = default;
		~MATL() = default;

		List<MATD> m_Materials;

	protected:
		friend MSH2;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}