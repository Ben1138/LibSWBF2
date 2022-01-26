#include "pch.h"
#include "LEKS.h"
#include "TNOJ.h"
#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	void LEKS::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void LEKS::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void LEKS::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

        while (ThereIsAnother(stream))
        {
            ChunkHeader next = stream.ReadChunkHeader(true);

			if (next == "TNOJ"_h)
			{
				READ_CHILD(stream, m_Joints.Emplace());
			}
			else 
			{
				break;
			}
        }

		BaseChunk::EnsureEnd(stream);
	}


	String LEKS::ToString() const
	{
		return fmt::format(
			"Animation skeleton with {} joints\n",
			m_Joints.Size()
		).c_str();
	}
}