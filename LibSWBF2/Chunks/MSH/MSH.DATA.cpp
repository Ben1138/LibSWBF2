#include "stdafx.h"
#include "MSH.DATA.h"
#include "FileReader.h"
#include "FileWriter.h"

namespace LibSWBF2::Chunks::MSH
{
	void DATA::RefreshSize()
	{
		m_Size = Color::SIZE + Color::SIZE + Color::SIZE + sizeof(float_t);
	}

	void DATA::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_Diffuse.WriteToStream(stream);
		m_Specular.WriteToStream(stream);
		m_Ambient.WriteToStream(stream);
		stream.WriteFloat(m_SpecularSharpness);
	}

	void DATA::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_Diffuse.ReadFromStream(stream);
		m_Specular.ReadFromStream(stream);
		m_Ambient.ReadFromStream(stream);
		m_SpecularSharpness = stream.ReadFloat();
		BaseChunk::EnsureEnd(stream);
	}
}