#pragma once
#include "HeaderNames.h"

namespace LibSWBF2::Chunks
{
	struct BaseChunk
	{
		BaseChunk();
		~BaseChunk();
		static ChunkHeader PeekHeader(ifstream& stream);

		// These MUST be overridden in subclasses!
		virtual void RefreshSize();
		virtual void WriteToStream(ofstream& stream);
		virtual void ReadFromStream(ifstream& stream);

		ChunkHeader GetHeader();
		ChunkSize GetSize();

	protected:
		// since these variables are critical
		// we should keep them protected
		ChunkHeader Header;
		ChunkSize Size;
	};
}