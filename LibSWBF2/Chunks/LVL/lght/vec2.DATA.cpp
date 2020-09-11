#include "stdafx.h"
#include "vec3.DATA.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"
#include "vec2.DATA.h"


namespace LibSWBF2::Chunks::LVL::lght
{
	void DATA_VEC2::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void DATA_VEC2::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void DATA_VEC2::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
        Check(stream);

        stream.SkipBytes(5);
        m_Vec.ReadFromStream(stream);

        BaseChunk::EnsureEnd(stream);
	}

	String DATA_VEC2::ToString()
	{
		return m_Vec.ToString();
	}
}
