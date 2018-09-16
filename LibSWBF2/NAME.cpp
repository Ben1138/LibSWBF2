#include "stdafx.h"
#include "NAME.h"

namespace LibSWBF2::Chunks::Mesh
{
	NAME::NAME()
	{

	}

	NAME::~NAME()
	{

	}

	void NAME::RefreshSize()
	{
		// size must be a multiple of 4
		Size = (ChunkSize)Text.size();
		Size += 4 - (Size % 4);
	}

	void NAME::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteString(Text, Size);
	}

	void NAME::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Text = stream.ReadString(Size);
	}
}