#include "stdafx.h"
#include "NAME.h"

namespace LibSWBF2::Chunks::MSH
{
	NAME::NAME()
	{

	}

	NAME::~NAME()
	{

	}

	void NAME::WriteToStream(ofstream& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream << Text;

		// string needs to be a zero terminated c-string
		// size must be a multiple of 4
		// remaining bytes should be filled with 0x00
		int remaining = Text.size() % 4;
		const char* empty = new char[remaining];
		stream.write(empty, remaining);
		delete[] empty;
	}

	void NAME::ReadFromStream(ifstream& stream)
	{
		BaseChunk::ReadFromStream(stream);
		stream >> Text;
	}
}