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

	ChunkHeader BaseChunk::PeekHeader(ifstream& stream)
	{
		auto pos = stream.tellg();

		ChunkHeader head;
		stream >> head;
		stream.seekg(pos);

		return head;
	}

	void BaseChunk::RefreshSize()
	{
		Size = 0;
	}

	void BaseChunk::WriteToStream(ofstream& stream)
	{
		RefreshSize();
		stream << Header << Size;
	}

	void BaseChunk::ReadFromStream(ifstream& stream)
	{
		stream >> Header >> Size;
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