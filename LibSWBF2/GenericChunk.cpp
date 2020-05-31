#include "stdafx.h"
#include "GenericChunk.h"
#include "Exceptions.h"
#include "tex_.h"

namespace LibSWBF2::Chunks
{
	GenericChunk::~GenericChunk()
	{
		for (size_t i = 0; i < m_Children.Size(); ++i)
		{
			delete m_Children[i];
		}
	}

	void GenericChunk::RefreshSize()
	{
		throw std::runtime_error("Not implemented!");
	}

	void GenericChunk::WriteToStream(FileWriter& stream)
	{
		throw std::runtime_error("Not implemented!");
	}

	void GenericChunk::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		// check if current "chunk" exceeds parents data size
		if (m_Parent != nullptr && (stream.GetPosition() + m_Size) > (m_Parent->GetDataPosition() + m_Parent->GetDataSize()))
		{
			throw InvalidSizeException(m_Size);
		}

		while (stream.GetFileSize() - stream.GetPosition() >= 4 && PositionInChunk(stream.GetPosition()))
		{
			if (stream.GetPosition() == 19199604)
			{
				LOG("", ELogType::Info);
			}

			ChunkHeader nextHead = stream.ReadChunkHeader(true);
			if (HeaderNames::IsKnownHeader(nextHead))
			//if (HeaderNames::IsValidHeader(nextHead))
			{
				GenericChunk* chunk = nullptr;
				try
				{
					if (nextHead == HeaderNames::NAME)
					{
						STR* name = new STR();
						name->ReadFromStream(stream);
						chunk = name;
					}
					else if (nextHead == HeaderNames::tex_)
					{
						LVL::tex_* texture = new LVL::tex_();
						texture->ReadFromStream(stream);
						chunk = texture;
					}
					else
					{
						chunk = new GenericChunk();
						chunk->ReadFromStream(stream);
					}

					chunk->m_Parent = this;
					m_Children.Add(chunk);
					LOG(string("Adding Child '") + chunk->GetHeaderName().Buffer() + "' to '" + GetHeaderName().Buffer() + "'", ELogType::Info);
				}
				catch (InvalidSizeException& e)
				{
					e; // avoid C4101 warning

					if (chunk != nullptr)
					{
						delete chunk;
					}

					LOG("Skipping invalid Chunk: '" + HeaderNames::GetHeaderString(nextHead) + "' at pos: " + std::to_string(stream.GetPosition()), ELogType::Error);
					//ForwardToNextHeader(stream);
					//stream.SetPosition(stream.GetPosition() - (sizeof(ChunkHeader)*2) - (sizeof(ChunkSize)*2));
					//SkipChunk(stream, false);
					break;
				}
			}
			else
			{
				//stream.SkipBytes(m_Size);
				//SkipChunk(stream);

				//if (HeaderNames::IsValidHeader(nextHead))
				//{
				//	LOG("Unknwon Chunk '" + HeaderNames::GetHeaderString(nextHead) + "' at pos: " + std::to_string(stream.GetPosition()), ELogType::Warning);
				//}
				//throw std::runtime_error("NOPE");
				//stream.SetPosition(stream.GetPosition() - sizeof(ChunkHeader) - sizeof(ChunkSize));
				//SkipChunk(stream, false);
				//ForwardToNextHeader(stream);
				break;
			}
		}

		BaseChunk::EnsureEnd(stream);
	}

	String GenericChunk::GetHeaderName() const
	{
		return HeaderNames::GetHeaderString(m_Header).c_str();
	}

	GenericChunk* GenericChunk::GetParent() const
	{
		return m_Parent;
	}

	const List<GenericChunk*>& GenericChunk::GetChildren() const
	{
		return m_Children;
	}

	String GenericChunk::ToString()
	{
		return "No Info";
	}
}