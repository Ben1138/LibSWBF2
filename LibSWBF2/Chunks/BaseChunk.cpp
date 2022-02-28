#include "pch.h"
#include "BaseChunk.h"
#include "InternalHelpers.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "Logging/Logger.h"
#include <string>
#include <mutex>

namespace LibSWBF2::Chunks
{
	class MultiThreadHandling
	{
	public:
		FileReader* m_CurrentReader = nullptr;
		std::mutex m_Lock;
	};


	BaseChunk::BaseChunk()
	{
		m_ThreadHandling = new MultiThreadHandling();
	}

	BaseChunk::~BaseChunk()
	{
		delete m_ThreadHandling;
		m_ThreadHandling = nullptr;
	}

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

		LOG_INFO("Position: {}", m_ChunkPosition);
		LOG_INFO("Header: {}", m_Header);
		LOG_INFO("Size: {:#x}", m_Size);

		if (stream.GetPosition() + m_Size > 8 + stream.GetFileSize())
		{
			THROW("Chunk is too big and will end up out of file! Chunk: '{}' Size: {:#x} At Position: {:#x} with File Size of: {:#x}", m_Header, m_Size, stream.GetPosition() - 8, stream.GetFileSize());
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
			catch (LibException e)
			{
				LOG_ERROR("{}", e.what());
				LOG_ERROR("Aborting write process...");
				return false;
			}
			LOG_INFO("Successfully finished writing process!");
			return true;
		}
		LOG_WARN("Could not write to File {}!", Path);
		return false;
	}

	bool BaseChunk::ReadFromFile(const String& Path)
	{
		FileReader reader;
		{
			LOCK(m_ThreadHandling->m_Lock);
			m_ThreadHandling->m_CurrentReader = &reader;
		}
		bool bSuccess = false;
		if (reader.Open(Path))
		{
			try
			{
				ReadFromStream(reader);
				LOCK(m_ThreadHandling->m_Lock);
				reader.Close();
				LOG_INFO("Successfully finished reading process!");
				bSuccess = true;
			}
			catch (LibException e)
			{
				LOG_ERROR("{}", e.what());
				LOG_ERROR("Aborting read process...");
				LOCK(m_ThreadHandling->m_Lock);
				reader.Close();
			}
		}
		else
		{
			LOG_WARN("Could not open File {}! Non existent?", Path);
		}
		{
			LOCK(m_ThreadHandling->m_Lock);
			m_ThreadHandling->m_CurrentReader = nullptr;
		}
		return bSuccess;
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

	bool BaseChunk::PositionInChunk(const size_t& PossiblePosition)
	{
		size_t dataPosition = GetDataPosition();
		return PossiblePosition >= dataPosition && PossiblePosition < dataPosition + m_Size;
	}

	bool BaseChunk::ThereIsAnother(FileReader& stream)
	{
		return stream.GetFileSize() - stream.GetPosition() >= 8 && PositionInChunk(stream.GetPosition() + 7);
	}

	bool BaseChunk::SkipChunk(FileReader& stream, const bool& printWarn)
	{
		if (stream.GetPosition() == stream.GetFileSize())
		{
			LOG_WARN("Cannot skip chunk from end position: {:#x}", stream.GetPosition());
			return false;
		}

		ChunkHeader head = stream.ReadChunkHeader(false);
		ChunkSize alignedSize = (ChunkSize)ceil(stream.ReadChunkSize() / 4.0f) * 4;

		if (printWarn)
		{
			LOG_WARN("[{}] Unexpected Chunk found: {} at position {:#x}. Skipping {:#x} Bytes...", m_Header, head, stream.GetPosition(), alignedSize);
		}

		return stream.SkipBytes(alignedSize);
	}

	void BaseChunk::EnsureEnd(FileReader& stream)
	{
		size_t currPos = stream.GetPosition();
		if (currPos == stream.GetFileSize())
			return;

		size_t endPos = GetDataPosition() + GetAlignedSize();
		if (currPos < endPos)
		{
			//LOG_WARN("[{}] We did not end up at the Chunks end position ({:#x})! Instead we are here:{:#x}! Moving Position to Chunks end position...", m_Header, endPos, stream.GetPosition());
			stream.SetPosition(endPos);
		}
		else if (currPos > endPos)
		{
			// This should NEVER happen!
			LOG_WARN("[{}] Ended up outside of current chunk (end is at: {:#x}, we are at: {:#x}! Too many bytes read: {}", m_Header, endPos, currPos, currPos - endPos);
			ForwardToNextHeader(stream);
		}
	}

	void BaseChunk::ForwardToNextHeader(FileReader& stream)
	{
		// if we've got any trailing bytes, skip them too
		size_t lastPos = stream.GetPosition();
		while (stream.GetFileSize() - stream.GetPosition() >= 4 && !IsKnownHeader(stream.ReadChunkHeader(true)))
		{
			stream.SetPosition(stream.GetPosition() + 1);
		}
		size_t skipped = stream.GetPosition() - lastPos;
		LOG_WARN("[{}] Forwarded to next header at {:#x}, skipped {} bytes!", m_Header, stream.GetPosition(), skipped);
	}

	float_t BaseChunk::GetReadingProgress()
	{
		LOCK(m_ThreadHandling->m_Lock);
		if (m_ThreadHandling->m_CurrentReader == nullptr)
		{
			return 1.0f;
		}

		return (float_t)m_ThreadHandling->m_CurrentReader->GetLatestChunkPosition() / (float_t)m_ThreadHandling->m_CurrentReader->GetFileSize();
	}
}
