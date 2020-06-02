#include "stdafx.h"
#include "STR.h"

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
		m_Text = stream.ReadString(GenericChunk<Header>::m_Size);
		BaseChunk::EnsureEnd(stream);
	}

	template<uint32_t Header>
	String STR<Header>::ToString()
	{
		return m_Text;
	}
}


namespace LibSWBF2::Chunks
{
	template LIBSWBF2_EXP struct STR<"NAME"_m>;
	template LIBSWBF2_EXP struct STR<"TX0D"_m>;
	template LIBSWBF2_EXP struct STR<"TX1D"_m>;
	template LIBSWBF2_EXP struct STR<"TX2D"_m>;
	template LIBSWBF2_EXP struct STR<"TX3D"_m>;
	template LIBSWBF2_EXP struct STR<"PRNT"_m>;
}