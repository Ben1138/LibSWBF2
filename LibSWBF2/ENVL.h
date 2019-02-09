#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct GEOM;

	struct ENVL : public BaseChunk
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