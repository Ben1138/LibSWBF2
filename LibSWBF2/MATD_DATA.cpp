#include "stdafx.h"
#include "MATD_DATA.h"

namespace LibSWBF2::Chunks::Mesh
{
	MATD_DATA::MATD_DATA()
	{

	}

	MATD_DATA::~MATD_DATA()
	{

	}

	void MATD_DATA::RefreshSize()
	{
		m_Size = Color::SIZE + Color::SIZE + Color::SIZE + sizeof(float_t);
	}

	void MATD_DATA::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_Diffuse.WriteToStream(stream);
		m_Specular.WriteToStream(stream);
		m_Ambient.WriteToStream(stream);
		stream.WriteFloat(m_SpecularSharpness);
	}

	void MATD_DATA::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_Diffuse.ReadFromStream(stream);
		m_Specular.ReadFromStream(stream);
		m_Ambient.ReadFromStream(stream);
		m_SpecularSharpness = stream.ReadFloat();
		BaseChunk::EnsureEnd(stream);
	}
}