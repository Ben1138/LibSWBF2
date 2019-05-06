#pragma once
#include "BaseChunk.h"
#include "SHVO.h"
#include "MSH2.h"
#include "ANM2.h"

namespace LibSWBF2::Chunks::Mesh
{
	struct LIBSWBF2_EXP MSH : public BaseChunk
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