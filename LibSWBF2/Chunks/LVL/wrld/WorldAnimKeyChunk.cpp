#include "pch.h"
#include "WorldAnimKeyChunk.h"
#include "InternalHelpers.h"
#include "FileReader.h"


namespace LibSWBF2::Chunks::LVL::wrld
{
	template<uint32_t Header>
	void WorldAnimKeyChunk<Header>::RefreshSize()
	{
		THROW("Not implemented!");
	}

	template<uint32_t Header>
	void WorldAnimKeyChunk<Header>::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	template<uint32_t Header>
	void WorldAnimKeyChunk<Header>::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		GenericChunk<Header>::Check(stream);
			
    	m_Key.ReadFromStream(stream);

		BaseChunk::EnsureEnd(stream);
	}

	template<uint32_t Header>
	String WorldAnimKeyChunk<Header>::ToString() const
	{
		return m_Key.ToString();
	}


	template struct LIBSWBF2_API WorldAnimKeyChunk<0>;
	template struct LIBSWBF2_API WorldAnimKeyChunk<"POSK"_m>;
	template struct LIBSWBF2_API WorldAnimKeyChunk<"ROTK"_m>;
}
