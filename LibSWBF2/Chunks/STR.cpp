#include "stdafx.h"
#include "STR.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "Hashing.h"

namespace LibSWBF2::Chunks
{
	template<uint32_t Header>
	void STR<Header>::RefreshSize()
	{
		GenericChunk<Header>::m_Size = (ChunkSize)m_Text.Length();
	}

	template<uint32_t Header>
	void STR<Header>::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteString(m_Text, true);
	}

	template<uint32_t Header>
	void STR<Header>::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		GenericChunk<Header>::Check(stream);

		m_Text = stream.ReadString(GenericChunk<Header>::m_Size);
		const char* buffer = m_Text.Buffer();

		// if all these conditions apply, we're probably
		// not dealing with a string, but with a hash
		if (m_Text.Length() == 4 &&
				(!IsValidStringChar(buffer[0]) ||
				 !IsValidStringChar(buffer[1]) ||
				 !IsValidStringChar(buffer[2]) ||
				 !IsValidStringChar(buffer[3]))
			)
		{
			String output;
			FNVHash hash = *((FNVHash*)buffer);
			if (LibSWBF2::FNV::Lookup(hash, output))
			{
				m_Text = output;
			}
		}
		
		BaseChunk::EnsureEnd(stream);
	}

	template<uint32_t Header>
	String STR<Header>::ToString()
	{
		return m_Text;
	}

	template<uint32_t Header>
	inline bool STR<Header>::IsValidStringChar(char c)
	{
		// see ascii table for reference
		return c >= 32 && c <= 126;
	}


}


namespace LibSWBF2::Chunks
{
	template LIBSWBF2_API struct STR<"NAME"_m>;
	template LIBSWBF2_API struct STR<"TYPE"_m>;
	template LIBSWBF2_API struct STR<"TX0D"_m>;
	template LIBSWBF2_API struct STR<"TX1D"_m>;
	template LIBSWBF2_API struct STR<"TX2D"_m>;
	template LIBSWBF2_API struct STR<"TX3D"_m>;
	template LIBSWBF2_API struct STR<"PRNT"_m>;
	template LIBSWBF2_API struct STR<"NODE"_m>;
	template LIBSWBF2_API struct STR<"RTYP"_m>;
	template LIBSWBF2_API struct STR<"BNAM"_m>;
	template LIBSWBF2_API struct STR<"TNAM"_m>;
	template LIBSWBF2_API struct STR<"SNAM"_m>;
	template LIBSWBF2_API struct STR<"DTLX"_m>;
}