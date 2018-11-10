#pragma once
#include "BaseChunk.h"
#include "BoneWeight.h"

namespace LibSWBF2::Chunks::Mesh
{
	using LibSWBF2::Types::BoneWeight;

	struct SEGM;

	struct WGHT : public BaseChunk
	{
		WGHT() = default;
		~WGHT() = default;

		// there are 4 weights for each vertex
		vector<array<BoneWeight, 4>> m_Weights;

	protected:
		friend SEGM;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}