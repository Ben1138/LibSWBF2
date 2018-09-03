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

	int32_t BaseChunk::PeekHeader(ifstream& stream)
	{
		auto pos = stream.tellg();

		int32_t head;
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

	int32_t BaseChunk::GetHeader()
	{
		return Header;
	}

	int32_t BaseChunk::GetSize()
	{
		return Size;
	}
}