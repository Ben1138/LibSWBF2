#include "stdafx.h"
#include "GenericChunk.h"
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
		// TODO
	}

	void GenericChunk::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		//TODO
		//we're probably not going to implement this now
		LOG("NOT IMPLEMENTED", ELogType::Error);
	}

	void GenericChunk::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		while (stream.GetFileSize() - stream.GetPosition() >= 4 && PositionInChunk(stream.GetPosition()))
		{
			ChunkHeader nextHead = stream.ReadChunkHeader(true);
			//if (HeaderNames::IsKnownHeader(nextHead))
			if (HeaderNames::IsValidHeader(nextHead))
			{
				GenericChunk* chunk = nullptr;
				try
				{
					if (nextHead == HeaderNames::tex_)
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
					LOG("Adding Child '" + chunk->GetHeaderName() + "' to '" + GetHeaderName() + "'", ELogType::Info);
				}
				catch (int& e)
				{
					e; // avoid C4101 warning

					if (chunk != nullptr)
					{
						delete chunk;
					}

					LOG("Skipping invalid Chunk: '" + HeaderNames::GetHeaderString(nextHead) + "' at pos: " + std::to_string(stream.GetPosition()), ELogType::Error);
					//ForwardToNextHeader(stream);
					stream.SetPosition(stream.GetPosition() - (sizeof(ChunkHeader)*2) - (sizeof(ChunkSize)*2));
					SkipChunk(stream, false);
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
				//throw 666;
				//stream.SetPosition(stream.GetPosition() - sizeof(ChunkHeader) - sizeof(ChunkSize));
				//SkipChunk(stream, false);
				//ForwardToNextHeader(stream);
				break;
			}
		}

		BaseChunk::EnsureEnd(stream);
	}

	string GenericChunk::GetHeaderName() const
	{
		return HeaderNames::GetHeaderString(m_Header);
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