#pragma once

namespace LibSWBF2::Types
{
	class FileReader;
	class FileWriter;

	struct LIBSWBF2_API BoneWeight
	{
		static const ChunkSize SIZE = sizeof(float_t) + sizeof(uint32_t);

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		uint32_t m_EnvelopeIndex = 0;
		float_t m_WeightValue = 0.0f;		// 0.0-1.0
	};

	struct LIBSWBF2_API VertexWeights
	{
		static const uint8_t NUM_OF_WEIGHTS = 4;
		static const ChunkSize SIZE = sizeof(BoneWeight) * NUM_OF_WEIGHTS;

		void WriteToStream(FileWriter& stream);
		void ReadFromStream(FileReader& stream);

		// there are always 4 weights for each vertex
		BoneWeight m_BoneWeights[NUM_OF_WEIGHTS];
	};
}