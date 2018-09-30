#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct UV0L : public BaseChunk
	{
		UV0L();
		~UV0L();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		vector<Vector2> m_UVs;
	};
}
