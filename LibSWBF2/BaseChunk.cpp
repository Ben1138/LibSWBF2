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
}