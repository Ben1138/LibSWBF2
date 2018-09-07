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
		for (int i = 0; i < Materials.size(); ++i)
		{
			Materials[i].RefreshSize();
			matChunksSize += Materials[i].GetSize();
		}

		Size = sizeof(int32_t) + matChunksSize;
	}

	void MATL::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteInt32((int32_t)Materials.size());

		for (int i = 0; i < Materials.size(); ++i)
		{
			Materials[i].WriteToStream(stream);
		}
	}

	void MATL::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		auto MaterialsSize = stream.ReadInt32();

		Materials.clear();
		Materials.reserve(MaterialsSize);

		for (int i = 0; i < MaterialsSize; ++i)
		{
			Materials.emplace_back(MATD());
			Materials[Materials.size() - 1].ReadFromStream(stream);
		}
	}
}