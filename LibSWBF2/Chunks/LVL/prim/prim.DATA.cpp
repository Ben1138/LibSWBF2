#include "stdafx.h"
#include "prim.DATA.h"
#include "InternalHelpers.h"
#include "FileReader.h"
#include "Types/Enums.h"
#include "Logging/Logger.h"


namespace LibSWBF2::Chunks::LVL::prim
{
	void DATA_PRIM::RefreshSize()
	{
		THROW("Not implemented!");
	}

	void DATA_PRIM::WriteToStream(FileWriter& stream)
	{
		THROW("Not implemented!");
	}

	void DATA_PRIM::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
        Check(stream);

        m_PrimitiveType = stream.ReadUInt32();

        m_Field1 = stream.ReadFloat();
        m_Field2 = stream.ReadFloat();
        m_Field3 = stream.ReadFloat();

        BaseChunk::EnsureEnd(stream);
	}

	Types::String DATA_PRIM::ToString()
	{
		String stringRep("");
		switch (m_PrimitiveType)
		{
			case 0:
			case 1:
				stringRep = stringRep + fmt::format(
											"PrimitiveType: Sphere, Radius: {}", 
											m_Field1).c_str();
				break;
			case 2:
				stringRep = stringRep + fmt::format(
											"PrimitiveType: Cylinder, Radius: {}, Height: {}",
											m_Field1, m_Field2).c_str();
				break;
			case 4:
				stringRep = stringRep + fmt::format(
											"PrimitiveType: Cube, x: {}, y: {}, z: {}",
											m_Field1, m_Field2, m_Field3).c_str();
				break;
			default:
				stringRep = String("Unknown primitive type");
		}

		return stringRep;
	}
}
