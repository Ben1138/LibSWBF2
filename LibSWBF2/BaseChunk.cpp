#include "stdafx.h"
#include "BaseChunk.h"

namespace LibSWBF2::Chunks
{
	BaseChunk::BaseChunk()
	{
		
	}

	BaseChunk::~BaseChunk()
	{

	}

	void BaseChunk::RefreshSize()
	{
		Size = 0;
	}

	void BaseChunk::WriteToStream(FileWriter& stream)
	{
		RefreshSize();
		stream.WriteChunkHeader(Header);
		stream.WriteChunkSize(Size);
	}

	void BaseChunk::ReadFromStream(FileReader& stream)
	{
		Header = stream.ReadChunkHeader(false);
		Size = stream.ReadChunkSize();
	}

	ChunkHeader BaseChunk::GetHeader()
	{
		return Header;
	}

	ChunkSize BaseChunk::GetSize()
	{
		return Size;
	}
}