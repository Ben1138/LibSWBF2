#pragma once
#include "Chunks/BaseChunk.h"
#include "Types/BoneWeight.h"

namespace LibSWBF2::Chunks::MSH
{
	using LibSWBF2::Types::BoneWeight;
	using LibSWBF2::Types::VertexWeights;

	struct SEGM;

	struct LIBSWBF2_API WGHT : public BaseChunk
	{
		WGHT() = default;
		~WGHT() = default;

		List<VertexWeights> m_Weights;

	protected:
		friend SEGM;

		void RefreshSize() override;
		void WriteToStream(FileWriter& stream) override;
		void ReadFromStream(FileReader& stream) override;
	};
}