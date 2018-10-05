#include "stdafx.h"
#include "BaseChunk.h"

namespace LibSWBF2::Chunks
{
	BaseChunk::BaseChunk()
	{
		
	}

	BaseChunk::~BaseChunk()
	{

	}

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
			return true;
		}
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
			return true;
		}
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

	bool BaseChunk::UnexpectedChunk(FileReader& stream)
	{
		ChunkHeader head = stream.ReadChunkHeader(false);
		ChunkSize size = stream.ReadChunkSize();

		LOG("["+Chunks::HeaderNames::GetHeaderString(m_Header)+"] Unexpected Chunk found: " + HeaderNames::GetHeaderString(head) + " at position " + std::to_string(stream.GetPosition()) + ". Skipping " + std::to_string(size) + " (Data Block Size) Bytes...", ELogType::Warning);
		return stream.SkipBytes(size);
	}
}