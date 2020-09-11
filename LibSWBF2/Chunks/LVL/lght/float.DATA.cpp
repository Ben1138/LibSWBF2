#include "stdafx.h"
#include "lght.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"
#include "float.DATA.h"


namespace LibSWBF2::Chunks::LVL::lght
{
	void DATA_FLOAT::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void DATA_FLOAT::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void DATA_FLOAT::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
        Check(stream);

        stream.SkipBytes(5);
        m_Float = stream.ReadFloat();

        BaseChunk::EnsureEnd(stream);
	}

	String DATA_FLOAT::ToString()
	{
		return fmt::format("Float member: {}", m_Float).c_str();
	}
}
