#pragma once
#include "Chunks/BaseChunk.h"
#include "MATD.h"

namespace LibSWBF2::Chunks::MSH
{
	struct MSH2;

	struct LIBSWBF2_API MATL : public BaseChunk
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