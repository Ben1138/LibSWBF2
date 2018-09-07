#include "stdafx.h"
#include "ATRB.h"

namespace LibSWBF2::Chunks::MSH
{
	ATRB::ATRB()
	{

	}

	ATRB::~ATRB()
	{

	}

	void ATRB::RefreshSize()
	{
		Size = sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint8_t);
	}

	void ATRB::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteByte(RenderFlags);
		stream.WriteByte(RenderType);
		stream.WriteByte(Data0);
		stream.WriteByte(Data1);
	}

	void ATRB::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		RenderFlags = (ERenderFlags)stream.ReadByte();
		RenderType = (ERenderType)stream.ReadByte();
		Data0 = stream.ReadByte();
		Data1 = stream.ReadByte();
	}
}