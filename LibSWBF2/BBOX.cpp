#include "stdafx.h"
#include "BBOX.h"

namespace LibSWBF2::Chunks::MSH
{
	BBOX::BBOX()
	{

	}

	BBOX::~BBOX()
	{

	}

	void BBOX::RefreshSize()
	{
		Size = Vector4::Size + Vector3::Size + Vector3::Size + sizeof(float_t);
	}

	void BBOX::WriteToStream(ofstream& stream)
	{
		BaseChunk::WriteToStream(stream);
		Quaternion.WriteToStream(stream);
		Center.WriteToStream(stream);
		Extent.WriteToStream(stream);
		stream << SphereRadius;
	}

	void BBOX::ReadFromStream(ifstream& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Quaternion.ReadFromStream(stream);
		Center.ReadFromStream(stream);
		Extent.ReadFromStream(stream);
		stream >> SphereRadius;
	}
}