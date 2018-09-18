#include "stdafx.h"
#include "BBOX.h"

namespace LibSWBF2::Chunks::Mesh
{
	BBOX::BBOX()
	{

	}

	BBOX::~BBOX()
	{

	}

	void BBOX::RefreshSize()
	{
		m_Size = Vector4::Size + Vector3::Size + Vector3::Size + sizeof(float_t);
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
	}
}