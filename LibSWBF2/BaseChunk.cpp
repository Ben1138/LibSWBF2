#include "stdafx.h"
#include "BaseChunk.h"

namespace LibSWBF2
{
	BaseChunk::BaseChunk()
	{
		
	}

	BaseChunk::~BaseChunk()
	{

	}

	void BaseChunk::WriteToStream(ofstream& stream)
	{
		stream << Header << Size;
	}

	void BaseChunk::ReadFromStream(ifstream& stream)
	{
		stream >> Header >> Size;
	}

	int32_t BaseChunk::PeekHeader(ifstream& stream)
	{
		auto pos = stream.tellg();

		int32_t head;
		stream >> head;
		stream.seekg(pos);

		return head;
	}
}