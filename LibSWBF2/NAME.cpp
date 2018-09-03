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

	void NAME::RefreshSize()
	{
		// TODO: proper implementation
		Size = 0;
	}

	void NAME::WriteToStream(ofstream& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream << Text;

		// string in chunk needs to be a zero terminated c-string
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

		// strings in chunks are filled up with 0x00's so the size matches up to a multiple of 4.
		// since the total size is stored in the header, just skip to the end of the NAME chunk.
		// we read our string, whatever the strings actual size was.

		long long end = stream.tellg();
		end += GetSize();
		stream >> Text;
		stream.seekg(end);
	}
}