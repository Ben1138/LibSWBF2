#pragma once
#include "Chunks\BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct SEGM;

	struct LIBSWBF2_EXP UV0L : public BaseChunk
	{
		UV0L() = default;
		~UV0L() = default;

		List<Vector2> m_UVs;

	protected:
		friend SEGM;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}
