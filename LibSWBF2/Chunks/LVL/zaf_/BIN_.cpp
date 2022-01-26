#include "pch.h"
#include "BIN_.h"
#include "LEKS.h"

#include "InternalHelpers.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::animation
{
	void ZAF_BIN_::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void ZAF_BIN_::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void ZAF_BIN_::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Check(stream);

		while (ThereIsAnother(stream))
		{
			ChunkHeader next = stream.ReadChunkHeader(true);

			if (next == "SREV"_h)
			{
				stream.SkipBytes(8);
				m_Version = stream.ReadUInt32();
				if (m_Version != 8)
				{
					LOG_WARN("Encountered zaf_(ZAF_BIN_) chunk with unusual (not 8) version: {}...", m_Version);
				}
			}
			else if (next == "LEKS"_h)
			{
				READ_CHILD(stream, p_Skeleton);
			}
			// Idk what any of these mean or why their implied meanings
			// would be relevant in this context.  They are probably just
			// leftovers from previous Pandemic games.

			//			    materials          joint sets          skins  
			else if (next == "SLTM"_h || next == "STSJ"_h || next == "SNKS"_h)
			{
				READ_CHILD_GENERIC(stream);
			}
			else 
			{
				// Anim related chunks are sketchy, not gonna assume all them
				// have proper size fields
				stream.SkipBytes(4);
			}
		}		

		BaseChunk::EnsureEnd(stream);
	}

	String ZAF_BIN_::ToString() const
	{
		return fmt::format(
			"Animation skeleton data of version {}\n",
			m_Version
		).c_str();
	}
}