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

		LOG("Header: " + HeaderNames::GetHeaderString(m_Header), ELogType::Info);
		LOG("Size: " + std::to_string(m_Size), ELogType::Info);
	}

	bool BaseChunk::WriteToFile(const string& Path)
	{
		FileWriter writer;
		
		if (writer.Open(Path))
		{
			WriteToStream(writer);
			writer.Close();
			return true;
		}

		return false;
	}

	bool BaseChunk::ReadFromFile(const string& Path)
	{
		FileReader reader;

		if (reader.Open(Path))
		{
			ReadFromStream(reader);
			reader.Close();
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
}