#pragma once
#include "HeaderNames.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "Logger.h"
#include "Color.h"
#include "Vector4.h"

namespace LibSWBF2::Chunks
{
	using Logging::Logger;
	using Logging::ELogType;
	using Types::Color;
	using Types::Vector2;
	using Types::Vector3;
	using Types::Vector4;

	struct BaseChunk
	{
		LIBSWBF2_EXP bool WriteToFile(const string& Path);
		LIBSWBF2_EXP bool ReadFromFile(const string& Path);

	protected:
		BaseChunk() = default;
		~BaseChunk() = default;

		// These MUST be overridden in subclasses!
		virtual void RefreshSize();
		virtual void WriteToStream(FileWriter& stream);
		virtual void ReadFromStream(FileReader& stream);

		bool PositionInChunk(const size_t& CurrentPosition);
		bool SkipChunk(FileReader& stream, const bool& printWarn = true);
		void EnsureEnd(FileReader& stream);

		ChunkHeader GetHeader();
		ChunkSize GetSize();

		// since these variables are critical
		// we should keep them protected
		ChunkHeader m_Header;
		ChunkSize m_Size;
		size_t m_ChunkDataPosition;	// in File (for reading process)
	};
}