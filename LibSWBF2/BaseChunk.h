#pragma once
#include "HeaderNames.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "Logger.h"
#include "Color.h"
#include "Vector4.h"
#include "List.h"
#include "LibString.h"

namespace LibSWBF2::Chunks
{
	using Logging::Logger;
	using Logging::ELogType;
	using Types::Color;
	using Types::Vector2;
	using Types::Vector3;
	using Types::Vector4;
	using LibSWBF2::Types::List;
	using LibSWBF2::Types::String;

	struct LIBSWBF2_EXP BaseChunk
	{
		bool WriteToFile(const string& Path);
		bool ReadFromFile(const string& Path);

		BaseChunk() = default;
		~BaseChunk() = default;

		// These MUST be overridden in subclasses!
		virtual void RefreshSize();
		virtual void WriteToStream(FileWriter& stream);
		virtual void ReadFromStream(FileReader& stream);

		size_t GetPosition() const;
		size_t GetDataPosition() const;
		bool PositionInChunk(const size_t& CurrentPosition);
		bool SkipChunk(FileReader& stream, const bool& printWarn = true);
		void EnsureEnd(FileReader& stream);
		//void ForwardToNextHeader(FileReader& stream);

		ChunkHeader GetHeader() const;
		ChunkSize GetDataSize() const;		// just the size of the data
		ChunkSize GetAlignedSize() const;	// size of the data, including trailing bytes
		ChunkSize GetFullSize() const;		// size of the whole chunk, including complete header and trailling bytes

	protected:
		// since these variables are critical
		// we should keep them protected
		ChunkHeader m_Header = 0;
		ChunkSize m_Size = 0;
		size_t m_ChunkPosition = 0;	// pointing to the chunks header
	};
}