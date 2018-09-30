#pragma once
#include "BaseChunk.h"
#include "BoneWeight.h"

namespace LibSWBF2::Chunks::Mesh
{
	using LibSWBF2::Types::BoneWeight;

	struct WGHT : public BaseChunk
	{
		WGHT();
		~WGHT();

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;

		vector<BoneWeight> m_Weights;
	};
}