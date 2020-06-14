#pragma once
#include "Chunks\BaseChunk.h"
#include "SHVO.h"
#include "MSH2.h"
#include "ANM2.h"

namespace LibSWBF2::Chunks::MSH
{
	struct LIBSWBF2_API MSH : public BaseChunk
	{
		static MSH* Create();
		static void Destroy(MSH* msh);

		SHVO m_ShadowVolume;
		MSH2 m_MeshBlock;
		ANM2 m_Animations;

	protected:
		MSH() = default;
		~MSH() = default;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}