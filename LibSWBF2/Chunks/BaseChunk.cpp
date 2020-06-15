#include "stdafx.h"
#include "BaseChunk.h"
#include "Exceptions.h"
#include "FileWriter.h"
#include "FileReader.h"
#include <string>

namespace LibSWBF2::Chunks
{
	void BaseChunk::RefreshSize()
	{
		// must be overwritten by inheriting classes!
	}

	void BaseChunk::WriteToStream(FileWriter& stream)
	{
		RefreshSize();
		stream.WriteChunkHeader(m_Header);
		stream.WriteChunkSize(m_Size);
	}

	void BaseChunk::ReadFromStream(FileReader& stream)
	{
		m_ChunkPosition = stream.GetPosition();
		m_Header = stream.ReadChunkHeader(false);
		m_Size = stream.ReadChunkSize();

		LOG("Header: " + std::string(m_Header.ToString().Buffer()), ELogType::Info);
		LOG("Size: " + std::to_string(m_Size), ELogType::Info);

		if (!IsValidHeader(m_Header) || m_Size < 0)
		{
			LOG("Invalid Chunk: " + std::string(m_Header.ToString().Buffer()) + " Size: " + std::to_string(m_Size) + " At Position: " + std::to_string(stream.GetPosition()) + " with File Size of: " + std::to_string(stream.GetFileSize()), ELogType::Error);
			throw InvalidHeaderException(m_Header);
		}

		if (stream.GetPosition() + m_Size > stream.GetFileSize())
		{
			LOG("Chunk is too big and will end up out of file! Chunk: " + std::string(m_Header.ToString().Buffer()) + " Size: " + std::to_string(m_Size) + " At Position: " + std::to_string(stream.GetPosition()) + " with File Size of: " + std::to_string(stream.GetFileSize()), ELogType::Error);
			throw InvalidSizeException(m_Size);
		}
	}

	bool BaseChunk::WriteToFile(const String& Path)
	{
		FileWriter writer;
		if (writer.Open(Path))
		{
			try
			{
				WriteToStream(writer);
				writer.Close();
			}
			catch (InvalidChunkException& e)
			{
				LOG(e.what(), ELogType::Error);
				LOG("Aborting write process...", ELogType::Error);
				return false;
			}
			LOG("Successfully finished writing process!", ELogType::Info);
			return true;
		}
		LOG("Could not write to File " + std::string(Path.Buffer()) + "!", ELogType::Warning);
		return false;
	}

	bool BaseChunk::ReadFromFile(const String& Path)
	{
		FileReader reader;
		if (reader.Open(Path))
		{
			try
			{
				ReadFromStream(reader);
				reader.Close();
			}
			catch (std::runtime_error& e)
			{
				LOG(e.what(), ELogType::Error);
				LOG("Aborting read process...", ELogType::Error);
				reader.Close();
				return false;
			}
			LOG("Successfully finished reading process!", ELogType::Info);
			return true;
		}
		LOG("Could not open File "+std::string(Path.Buffer())+"! Non existent?", ELogType::Warning);
		return false;
	}

	ChunkHeader BaseChunk::GetHeader() const
	{
		return m_Header;
	}

	ChunkSize BaseChunk::GetDataSize() const
	{
		return m_Size;
	}

	ChunkSize BaseChunk::GetAlignedSize() const
	{
		return (ChunkSize)ceil(m_Size / 4.0f) * 4;
	}

	ChunkSize BaseChunk::GetFullSize() const
	{
		return GetAlignedSize() + sizeof(ChunkHeader) + sizeof(ChunkSize);
	}
	
	size_t BaseChunk::GetPosition() const
	{
		return m_ChunkPosition;
	}

	size_t BaseChunk::GetDataPosition() const
	{
		return m_ChunkPosition + sizeof(ChunkHeader) + sizeof(ChunkSize);
	}

	bool BaseChunk::PositionInChunk(const size_t& CurrentPosition)
	{
		size_t dataPosition = GetDataPosition();
		return CurrentPosition >= dataPosition && CurrentPosition < dataPosition + m_Size;
	}

	bool BaseChunk::SkipChunk(FileReader& stream, const bool& printWarn)
	{
		if (stream.GetPosition() == stream.GetFileSize())
		{
			LOG("Cannot skip chunk from end position: " + std::to_string(stream.GetPosition()), ELogType::Warning);
			return false;
		}

		ChunkHeader head = stream.ReadChunkHeader(false);
		ChunkSize alignedSize = (ChunkSize)ceil(stream.ReadChunkSize() / 4.0f) * 4;

		if (printWarn)
		{
			LOG("["+std::string(m_Header.ToString().Buffer())+"] Unexpected Chunk found: " + head.ToString().Buffer() + " at position " + std::to_string(stream.GetPosition()) + ". Skipping " + std::to_string(alignedSize) + " Bytes...", ELogType::Warning);
		}

		return stream.SkipBytes(alignedSize);
	}

	void BaseChunk::EnsureEnd(FileReader& stream)
	{
		if (stream.GetPosition() == stream.GetFileSize())
			return;

		size_t endPos = GetDataPosition() + GetAlignedSize();
		if (stream.GetPosition() < endPos)
		{
			//LOG("[" + Chunks::"GetH"_headerString(m_Header) + "] We did not end up at the Chunks end position ("+std::to_string(endPos)+")! Instead we are here: "+std::to_string(stream.GetPosition())+"! Moving Position to Chunks end position...", ELogType::Warning);
			stream.SetPosition(endPos);
		}
		else
		{
			// if we've got trailing bytes, skip them too
			//ForwardToNextHeader(stream);
		}
	}

	void BaseChunk::ForwardToNextHeader(FileReader& stream)
	{
		// if we've got any trailing bytes, skip them too
		while (stream.GetFileSize() - stream.GetPosition() >= 4 && !IsKnownHeader(stream.ReadChunkHeader(true)))
		{
			stream.SetPosition(stream.GetPosition() + 1);
			LOG("[" + std::string(m_Header.ToString().Buffer()) + "] Could not find next valid header, skipping to position: " + std::to_string(stream.GetPosition()), ELogType::Warning);
		}
	}
}