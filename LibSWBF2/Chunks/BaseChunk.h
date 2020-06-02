#pragma once
#include "HeaderNames.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "Logging\\Logger.h"
#include "Types\Color.h"
#include "Types\Vector4.h"
#include "Types\List.h"
#include "Types\LibString.h"

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
		void EnsureTrallingBytes(FileWriter& stream); // TODO
		void ForwardToNextHeader(FileReader& stream);

		ChunkHeader GetHeader() const;
		ChunkSize GetDataSize() const;		// just the size of the data (m_Size)
		ChunkSize GetAlignedSize() const;	// size of the data, including trailing bytes, exclude header
		ChunkSize GetFullSize() const;		// size of the whole chunk, including header and trailling bytes

	protected:
		// since these variables are critical
		// we should keep them protected
		ChunkHeader m_Header;
		ChunkSize m_Size = 0; // Data Size, no header, no trailling bytes
		size_t m_ChunkPosition = 0;	// pointing to the chunks header
	};
}