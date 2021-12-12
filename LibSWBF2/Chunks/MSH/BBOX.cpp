#include "pch.h"
#include "BBOX.h"
#include "FileReader.h"
#include "FileWriter.h"

namespace LibSWBF2::Chunks::MSH
{
	void BBOX::RefreshSize()
	{
		m_Size = Vector4::SIZE + Vector3::SIZE + Vector3::SIZE + sizeof(float_t);
	}

	void BBOX::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_Quaternion.WriteToStream(stream);
		m_Center.WriteToStream(stream);
		m_Extent.WriteToStream(stream);
		stream.WriteFloat(m_SphereRadius);
	}

	void BBOX::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_Quaternion.ReadFromStream(stream);
		m_Center.ReadFromStream(stream);
		m_Extent.ReadFromStream(stream);
		m_SphereRadius = stream.ReadFloat();
		BaseChunk::EnsureEnd(stream);
	}
}