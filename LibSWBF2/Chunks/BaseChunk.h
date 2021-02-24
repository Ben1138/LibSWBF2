#pragma once
#include "HeaderNames.h"
#include "Types/Color4u8.h"
#include "Types/Vector4.h"
#include "Types/Vector3u8.h"
#include "Types/List.h"
#include "Types/LibString.h"

#include <chrono>

namespace LibSWBF2 
{ 
	class FileReader;
	class FileWriter; 
}

namespace LibSWBF2::Chunks
{
	using Types::Color4u8;
	using Types::Vector2;
	using Types::Vector3;
	using Types::Vector3u8;
	using Types::Vector4;
	using Types::List;
	using Types::String;

	struct LIBSWBF2_API BaseChunk
	{
		bool WriteToFile(const String& Path);
		bool ReadFromFile(const String& Path);

		BaseChunk();
		virtual ~BaseChunk();

		// These MUST be overridden in subclasses!
		virtual void RefreshSize();
		virtual void WriteToStream(FileWriter& stream);
		virtual void ReadFromStream(FileReader& stream);

		size_t GetPosition() const;
		size_t GetDataPosition() const;
		bool PositionInChunk(const size_t& CurrentPosition);
		bool ThereIsAnother(FileReader& stream);
		bool SkipChunk(FileReader& stream, const bool& printWarn = true);
		void EnsureEnd(FileReader& stream);
		void ForwardToNextHeader(FileReader& stream);

		ChunkHeader GetHeader() const;
		ChunkSize GetDataSize() const;		// just the size of the data (m_Size)
		ChunkSize GetAlignedSize() const;	// size of the data, including trailing bytes, exclude header
		ChunkSize GetFullSize() const;		// size of the whole chunk, including header, data and trailling bytes

		// thread safe call
		float_t GetReadingProgress();

	protected:
		// since these variables are critical
		// we should keep them protected
		ChunkHeader m_Header;
		ChunkSize m_Size = 0; // Data Size, no header, no trailling bytes
		size_t m_ChunkPosition = 0;	// pointing to the chunks header


	private:
		class MultiThreadHandling* m_ThreadHandling = nullptr;
	};
}