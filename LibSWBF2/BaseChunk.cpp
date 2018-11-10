#include "stdafx.h"
#include "BaseChunk.h"

namespace LibSWBF2::Chunks
{
	// must be overwritten by inheriting classes!
	void BaseChunk::RefreshSize()
	{
		m_Size = 0;
		LOG("RefreshSize() of BaseChunk called! This should never happen!", ELogType::Error);
		throw 666;
	}

	void BaseChunk::WriteToStream(FileWriter& stream)
	{
		RefreshSize();
		stream.WriteChunkHeader(m_Header);
		stream.WriteChunkSize(m_Size);
	}

	void BaseChunk::ReadFromStream(FileReader& stream)
	{
		m_Header = stream.ReadChunkHeader(false);
		m_Size = stream.ReadChunkSize();
		m_ChunkDataPosition = stream.GetPosition();

		LOG("Header: " + HeaderNames::GetHeaderString(m_Header), ELogType::Info);
		LOG("Size: " + std::to_string(m_Size), ELogType::Info);

		if (m_Header == HeaderNames::EMPTY || m_Size <= 0)
		{
			LOG("Invalid Chunk: " + HeaderNames::GetHeaderString(m_Header) + " Size: " + std::to_string(m_Size) + " At Position: " + std::to_string(stream.GetPosition()) + " with File Size of: " + std::to_string(stream.GetFileSize()), ELogType::Error);
			throw 666;
		}

		if (stream.GetPosition() + m_Size > stream.GetFileSize())
		{
			LOG("Chunk is too big and will end up out of file! Chunk: " + HeaderNames::GetHeaderString(m_Header) + " Size: " + std::to_string(m_Size) + " At Position: " + std::to_string(stream.GetPosition()) + " with File Size of: " + std::to_string(stream.GetFileSize()), ELogType::Error);
			throw 666;
		}
	}

	bool BaseChunk::WriteToFile(const string& Path)
	{
		FileWriter writer;
		if (writer.Open(Path))
		{
			try
			{
				WriteToStream(writer);
				writer.Close();
			}
			catch (int& e)
			{
				e; // avoid C4101 warning
				LOG("Aborting write process...", ELogType::Error);
				return false;
			}
			LOG("Successfully finished writing process!", ELogType::Info);
			return true;
		}
		LOG("Could not write to File " + Path + "!", ELogType::Warning);
		return false;
	}

	bool BaseChunk::ReadFromFile(const string& Path)
	{
		FileReader reader;
		if (reader.Open(Path))
		{
			try
			{
				ReadFromStream(reader);
				reader.Close();
			}
			catch (int& e)
			{
				e; // avoid C4101 warning
				LOG("Aborting read process...", ELogType::Error);
				return false;
			}
			LOG("Successfully finished reading process!", ELogType::Info);
			return true;
		}
		LOG("Could not open File "+Path+"! Non existent?", ELogType::Warning);
		return false;
	}

	ChunkHeader BaseChunk::GetHeader()
	{
		return m_Header;
	}

	ChunkSize BaseChunk::GetSize()
	{
		return m_Size;
	}

	bool BaseChunk::PositionInChunk(const size_t& CurrentPosition)
	{
		return CurrentPosition >= m_ChunkDataPosition && CurrentPosition < m_ChunkDataPosition + m_Size;
	}

	bool BaseChunk::SkipChunk(FileReader& stream, const bool& printWarn)
	{
		ChunkHeader head = stream.ReadChunkHeader(false);
		ChunkSize size = stream.ReadChunkSize();

		if (printWarn)
		{
			LOG("["+Chunks::HeaderNames::GetHeaderString(m_Header)+"] Unexpected Chunk found: " + HeaderNames::GetHeaderString(head) + " at position " + std::to_string(stream.GetPosition()) + ". Skipping " + std::to_string(size) + " (Data Block Size) Bytes...", ELogType::Warning);
		}

		return stream.SkipBytes(size);
	}

	void BaseChunk::EnsureEnd(FileReader& stream)
	{
		size_t endPos = m_ChunkDataPosition + m_Size;
		if (stream.GetPosition() != endPos)
		{
			LOG("[" + Chunks::HeaderNames::GetHeaderString(m_Header) + "] We did not end up at the Chunks end position ("+std::to_string(endPos)+")! Instead we are here: "+std::to_string(stream.GetPosition())+"! Moving Position to Chunks end position...", ELogType::Warning);
			stream.SetPosition(endPos);
		}
	}
}