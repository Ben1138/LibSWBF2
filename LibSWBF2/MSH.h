#pragma once
#include "BaseChunk.h"
#include "SHVO.h"
#include "MSH2.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct MSH : public BaseChunk
	{
		LIBSWBF2_EXP static MSH* Create();
		LIBSWBF2_EXP static void Destroy(MSH* msh);

		SHVO m_SHVO;
		MSH2 m_MSH2;

	protected:
		MSH() = default;
		~MSH() = default;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}