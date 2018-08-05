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

	int BaseChunk::PeekHeader(ifstream& stream)
	{
		auto pos = stream.tellg();

		int head;
		stream >> head;
		stream.seekg(pos);

		return head;
	}
}