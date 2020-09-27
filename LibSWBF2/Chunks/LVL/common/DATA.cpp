#include "stdafx.h"
#include "DATA.h"
#include "FileReader.h"

namespace LibSWBF2::Chunks::LVL::common
{
	uint32_t DATA::PeekDATATag(FileReader& stream)
	{
		stream.SkipBytes(8);
		uint32_t result = stream.ReadUInt32();
		stream.SetPosition(stream.GetPosition() - 12);
		return result;
	}
}