#pragma once
#include <LibSWBF2/Chunks/BaseChunk.h>
#include <LibSWBF2/Chunks/MSH/SHVO.h>
#include <LibSWBF2/Chunks/MSH/MSH2.h>
#include <LibSWBF2/Chunks/MSH/ANM2.h>

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