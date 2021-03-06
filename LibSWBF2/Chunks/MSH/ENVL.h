#pragma once
#include "Chunks/BaseChunk.h"

namespace LibSWBF2::Chunks::MSH
{
	struct GEOM;

	struct LIBSWBF2_API ENVL : public BaseChunk
	{
		ENVL() = default;
		~ENVL() = default;

		List<uint32_t> m_ModelIndices;

	protected:
		friend GEOM;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}