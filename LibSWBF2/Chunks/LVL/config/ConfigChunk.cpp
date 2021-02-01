#include "stdafx.h"
#include "ConfigChunk.h"
#include "InternalHelpers.h"
#include "FileReader.h"

#include "DATA.h"
#include "SCOP.h"

namespace LibSWBF2::Chunks::LVL::config
{
	template<uint32_t Header>
	void ConfigChunk<Header>::RefreshSize()
	{
		THROW("Not implemented!");
	}

	template<uint32_t Header>
	void ConfigChunk<Header>::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	template<uint32_t Header>
	void ConfigChunk<Header>::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		GenericChunk<Header>::Check(stream);
		
		
        while (GenericChunk<Header>::ThereIsAnother(stream))
        {
            ChunkHeader next = stream.ReadChunkHeader(true);
			if (next == "NAME"_h)
			{
				GenericChunk<Header>::READ_CHILD(stream, p_Hash);
			}
			else if (next == "DATA"_h)
			{
				DATA_CONFIG* data;
				GenericChunk<Header>::READ_CHILD(stream, data);
			}
			else if (next == "SCOP"_h)
			{
				SCOP* scop;
				GenericChunk<Header>::READ_CHILD(stream, scop);
			}
			else 
			{
				//GenericChunk<Header>::READ_CHILD_GENERIC(stream);
			}
        }

		BaseChunk::EnsureEnd(stream);
	}

	template<uint32_t Header>
	String ConfigChunk<Header>::ToString()
	{
		return fmt::format(
			"Hash: 0x{0:x}\n\n",
			p_Hash != nullptr ? p_Hash -> m_PropertyName : 0
		).c_str();
	}


	template struct LIBSWBF2_API ConfigChunk<"lght"_m>;
	template struct LIBSWBF2_API ConfigChunk<"fx__"_m>;
	template struct LIBSWBF2_API ConfigChunk<"sky_"_m>;
	template struct LIBSWBF2_API ConfigChunk<"bnd_"_m>;
	template struct LIBSWBF2_API ConfigChunk<"prp_"_m>;
}
