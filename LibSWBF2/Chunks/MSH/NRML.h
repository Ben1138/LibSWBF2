#pragma once
#include "Chunks\BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct SEGM;

	struct LIBSWBF2_EXP NRML : public BaseChunk
	{
		NRML() = default;
		~NRML() = default;

		List<Vector3> m_Normals;

	protected:
		friend SEGM;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}
