#pragma once
#include "HeaderNames.h"
#include "FileWriter.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks
{
	struct BaseChunk
	{
		BaseChunk();
		~BaseChunk();

		// These MUST be overridden in subclasses!
		virtual void RefreshSize();
		virtual void WriteToStream(FileWriter& stream);
		virtual void ReadFromStream(FileReader& stream);

		ChunkHeader GetHeader();
		ChunkSize GetSize();

	protected:
		// since these variables are critical
		// we should keep them protected
		ChunkHeader Header;
		ChunkSize Size;
	};
}