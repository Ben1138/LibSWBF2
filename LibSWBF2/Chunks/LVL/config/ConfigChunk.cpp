#include "pch.h"
#include "ConfigChunk.h"
#include "InternalHelpers.h"
#include "FileReader.h"

#include "SCOP.h"
#include "DATA.h"

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
				DATA_CONFIG *data;
				GenericChunk<Header>::READ_CHILD(stream, data);
			}
			else if (next == "SCOP"_h)
			{
				SCOP *scop;
				GenericChunk<Header>::READ_CHILD(stream, scop);
			}
			else 
			{
				LOG_WARN("Irregular config chunk child found ({0:x})!", Header);
				BaseChunk::EnsureEnd(stream);
				//GenericChunk<Header>::READ_CHILD_GENERIC(stream);
			}
        }

		BaseChunk::EnsureEnd(stream);
	}

	template<uint32_t Header>
	String ConfigChunk<Header>::ToString() const
	{
		if (p_Hash != nullptr)
		{
			String name;
			return fmt::format(
				"Hash: 0x{0:x}\n"
				"Lookup Name: {1}",
				p_Hash -> m_Name,
				FNV::Lookup(p_Hash->m_Name, name) ? name.Buffer() : ""
			).c_str();
		}
		return "No Name";
	}


	template struct LIBSWBF2_API ConfigChunk<0>;
	template struct LIBSWBF2_API ConfigChunk<"lght"_m>;
	template struct LIBSWBF2_API ConfigChunk<"fx__"_m>;
	template struct LIBSWBF2_API ConfigChunk<"sky_"_m>;
	template struct LIBSWBF2_API ConfigChunk<"bnd_"_m>;
	template struct LIBSWBF2_API ConfigChunk<"prp_"_m>;
	template struct LIBSWBF2_API ConfigChunk<"path"_m>;
	template struct LIBSWBF2_API ConfigChunk<"comb"_m>;
}
