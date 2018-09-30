#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct NRML : public BaseChunk
	{
		NRML();
		~NRML();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		vector<Vector3> m_Normals;
	};
}
