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

	void BBOX::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		Quaternion.WriteToStream(stream);
		Center.WriteToStream(stream);
		Extent.WriteToStream(stream);
		stream.WriteFloat(SphereRadius);
	}

	void BBOX::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Quaternion.ReadFromStream(stream);
		Center.ReadFromStream(stream);
		Extent.ReadFromStream(stream);
		SphereRadius = stream.ReadFloat();
	}
}