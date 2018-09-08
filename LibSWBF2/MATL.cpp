#include "stdafx.h"
#include "MATL.h"

namespace LibSWBF2::Chunks::MSH
{
	MATL::MATL()
	{

	}

	MATL::~MATL()
	{
		
	}

	void MATL::RefreshSize()
	{
		ChunkSize matChunksSize = 0;
		for (int i = 0; i < matl.size(); ++i)
		{
			matl[i].RefreshSize();
			matChunksSize += matl[i].GetSize();
		}

		Size = sizeof(uint32_t) + matChunksSize;
	}

	void MATL::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32((uint32_t)matl.size());

		for (size_t i = 0; i < matl.size(); ++i)
		{
			matl[i].WriteToStream(stream);
		}
	}

	void MATL::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		uint32_t MaterialsSize = stream.ReadUInt32();

		matl.clear();
		matl.reserve(MaterialsSize);

		for (uint32_t i = 0; i < MaterialsSize; ++i)
		{
			matl.emplace_back(MATD());
			matl[matl.size() - 1].ReadFromStream(stream);
		}
	}
}