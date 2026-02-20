#include <LibSWBF2/pch.h>
#include <LibSWBF2/Chunks/LVL/coll/POSI.h>
#include "InternalHelpers.h"
#include <LibSWBF2/IO/FileReader.h>
#include <LibSWBF2/Types/Enums.h>
#include <LibSWBF2/Logging/Logger.h>


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
