#include "stdafx.h"
#include "GenericChunk.h"

namespace LibSWBF2::Chunks
{
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
			ChunkHeader head = stream.ReadChunkHeader(true);
			if (HeaderNames::IsKnownHeader(head))
			{
				/* NOTE: Apparently DATA chunks contain trailing bytes.
				 * Most of the time it's 3 bytes, but also encountered other numbers...
				 */


				try
				{
					GenericChunk unkChunk;
					unkChunk.ReadFromStream(stream);
					m_children.emplace_back(unkChunk);
					LOG("Adding Child '"+unkChunk.GetHeaderName()+"' to '"+GetHeaderName()+"'", ELogType::Info);
				}
				catch (int& e)
				{
					LOG("Skipping illegal Chunk: '" + HeaderNames::GetHeaderString(head) + "' at pos: " + std::to_string(stream.GetPosition()), ELogType::Error);
					ForwardToNextHeader(stream);
				}
			}
			else
			{
				// this log is just for research purposes and should be removed when done
				if (HeaderNames::IsValidHeader(head))
				{
					LOG("Skipping unknown Chunk: '" + HeaderNames::GetHeaderString(head) + "' at pos: " + std::to_string(stream.GetPosition()), ELogType::Error);
				}
				stream.SkipBytes(m_Size);

				// if we've got trailing bytes, skip them too
				ForwardToNextHeader(stream);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}

	string GenericChunk::GetHeaderName() const
	{
		return HeaderNames::GetHeaderString(m_Header);
	}

	const vector<GenericChunk>& GenericChunk::GetChildren() const
	{
		return m_children;
	}
}