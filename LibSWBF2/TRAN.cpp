#include "stdafx.h"
#include "TRAN.h"

namespace LibSWBF2::Chunks::MSH
{
	TRAN::TRAN()
	{

	}

	TRAN::~TRAN()
	{

	}

	void TRAN::RefreshSize()
	{
		Size = Vector3::Size + Vector4::Size + Vector3::Size;
	}

	void TRAN::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		Scale.WriteToStream(stream);
		Rotation.WriteToStream(stream);
		Translation.WriteToStream(stream);
	}

	void TRAN::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Scale.ReadFromStream(stream);
		Rotation.ReadFromStream(stream);
		Translation.ReadFromStream(stream);
	}
}