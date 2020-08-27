#include "stdafx.h"
#include "vec4.DATA.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"


namespace LibSWBF2::Chunks::LVL::lght
{

	void DATA_VEC4::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void DATA_VEC4::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void DATA_VEC4::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
        Check(stream);

        stream.SkipBytes(5);
        m_Vec.ReadFromStream(stream);

        BaseChunk::EnsureEnd(stream);
	}
}
