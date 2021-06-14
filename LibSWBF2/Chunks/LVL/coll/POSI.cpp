#include "stdafx.h"
#include "POSI.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"


namespace LibSWBF2::Chunks::LVL::coll
{
	void POSI::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void POSI::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void POSI::ReadFromStream(FileReader& stream)
	{       
        BaseChunk::ReadFromStream(stream);
        Check(stream);

        Vector3 tmp;
        while (ThereIsAnother(stream))
        {
            tmp.ReadFromStream(stream);
            m_Verts.Add(tmp);
        }

		BaseChunk::EnsureEnd(stream);
	}

    Types::String POSI::ToString() const
    {
        String stringRep("");

        for (int i  = 0; i < m_Verts.Size(); i++)
        {
            stringRep = stringRep + m_Verts[i].ToString() + "\n";
        }

        return stringRep;
    }
}
