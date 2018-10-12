#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct SEGM;

	struct NRML : public BaseChunk
	{
		NRML();
		~NRML();

		vector<Vector3> m_Normals;

	protected:
		friend SEGM;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}
