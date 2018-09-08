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

		Size = sizeof(int32_t) + matChunksSize;
	}

	void MATL::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteInt32((int32_t)matl.size());

		for (int i = 0; i < matl.size(); ++i)
		{
			matl[i].WriteToStream(stream);
		}
	}

	void MATL::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		auto MaterialsSize = stream.ReadInt32();

		matl.clear();
		matl.reserve(MaterialsSize);

		for (int i = 0; i < MaterialsSize; ++i)
		{
			matl.emplace_back(MATD());
			matl[matl.size() - 1].ReadFromStream(stream);
		}
	}
}