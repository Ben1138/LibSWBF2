#pragma once
#include "BaseChunk.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MSH;

	struct SHVO : public BaseChunk
	{
		SHVO();
		~SHVO();

		int32_t m_ShadowVolume;

	protected:
		friend MSH;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}