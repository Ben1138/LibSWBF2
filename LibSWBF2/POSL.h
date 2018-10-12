#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct SEGM;

	struct POSL : public BaseChunk
	{
		POSL() = default;
		~POSL() = default;

		vector<Vector3> m_Vertices;

	protected:
		friend SEGM;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}
