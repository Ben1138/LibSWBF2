#pragma once
#include "BaseChunk.h"
#include "BoneFrames.h"

namespace LibSWBF2::Chunks::Mesh
{
	using LibSWBF2::Types::BoneFrames;

	struct ANM2;

	struct KFR3 : public BaseChunk
	{
		KFR3() = default;
		~KFR3() = default;

		vector<BoneFrames> m_BoneFrames;

	protected:
		friend ANM2;
		
		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}