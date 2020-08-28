#include "stdafx.h"
#include "lght.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"


namespace LibSWBF2::Chunks::LVL::lght
{
	void DATA_LIGHTTYPE::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void DATA_LIGHTTYPE::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void DATA_LIGHTTYPE::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
        Check(stream);

        stream.SkipBytes(5);
        m_LightType = stream.ReadFloat();

        BaseChunk::EnsureEnd(stream);
	}

	String DATA_LIGHTTYPE::ToString()
	{
		return ELightTypeToString((ELightType) m_LightType);
	}
}
