#include "stdafx.h"
#include "LVL.h"

namespace LibSWBF2::Chunks::LVL
{
	LVL* LVL::Create()
	{
		return new LVL();
	}

	void LVL::Destroy(LVL* msh)
	{
		delete msh;
	}

	void LVL::RefreshSize()
	{
		// TODO
		m_Size = 0;
	}

	void LVL::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		//TODO
		//we're probably not going to implement this now
	}

	void LVL::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		if (m_Header != HeaderNames::LVLHeader)
		{
			LOG("This is not a valid LVL file!", ELogType::Error);
		}

		while (PositionInChunk(stream.GetPosition()))
		{
			ChunkHeader head = stream.ReadChunkHeader(true);

			// sadly, switch-case is not possible here (Error C2051)
			if (head == HeaderNames::NAME)
			{
				//TODO
			}
			else if (head == HeaderNames::INFO)
			{
				//TODO
			}
			else if (head == HeaderNames::BODY)
			{
				//TODO
			}
			else
			{
				//SkipChunk(stream);

				BaseChunk unkChunk;
				unkChunk.ReadFromStream(stream);
				unkChunk.EnsureEnd(stream);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}
}