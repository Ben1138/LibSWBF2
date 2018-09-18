#include "stdafx.h"
#include "TRAN.h"

namespace LibSWBF2::Chunks::Mesh
{
	TRAN::TRAN()
	{

	}

	TRAN::~TRAN()
	{

	}

	void TRAN::RefreshSize()
	{
		m_Size = Vector3::Size + Vector4::Size + Vector3::Size;
	}

	void TRAN::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_Scale.WriteToStream(stream);
		m_Rotation.WriteToStream(stream);
		m_Translation.WriteToStream(stream);
	}

	void TRAN::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_Scale.ReadFromStream(stream);
		m_Rotation.ReadFromStream(stream);
		m_Translation.ReadFromStream(stream);
	}
}