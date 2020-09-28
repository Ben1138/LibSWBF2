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

        uint32_t rawUInt = stream.ReadUInt32();

        m_PrimitiveType = (ECollisionPrimitiveType) (rawUInt == 0 ? 0x1 : rawUInt);

        m_Field1 = stream.ReadFloat();
        m_Field2 = stream.ReadFloat();
        m_Field3 = stream.ReadFloat();

        BaseChunk::EnsureEnd(stream);
	}

	Types::String DATA_PRIM::ToString()
	{
		switch (m_PrimitiveType)
		{
			case ECollisionPrimitiveType::Sphere:
				return fmt::format("Type: Sphere, Radius: {}", 
									m_Field1).c_str();
			case ECollisionPrimitiveType::Cylinder:
				return fmt::format("Type: Cylinder, Radius: {}, Height: {}",
									m_Field1, m_Field2).c_str();
			case ECollisionPrimitiveType::Cube:
				return fmt::format("Type: Cube, x: {}, y: {}, z: {}",
									m_Field1, m_Field2, m_Field3).c_str();
			default:
				String unknown = CollisionPrimitiveTypeToString(m_PrimitiveType);
				return fmt::format("{}, field1: {}, field2: {}, field3: {}",
									unknown.Buffer(), m_Field1, m_Field2, m_Field3).c_str();
		}
	}
}
