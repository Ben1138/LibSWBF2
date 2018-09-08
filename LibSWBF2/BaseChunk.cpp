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

	// must be overwritten by inheriting classes!
	void BaseChunk::RefreshSize()
	{
		Size = 0;
		Logging::Log("RefreshSize() of BaseChunk called! This should never happen!", ELogType::Error);
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