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
		Size = Color::Size + Color::Size + Color::Size + sizeof(float_t);
	}

	void MATD_DATA::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		Diffuse.WriteToStream(stream);
		Specular.WriteToStream(stream);
		Ambient.WriteToStream(stream);
		stream.WriteFloat(SpecularSharpness);
	}

	void MATD_DATA::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		Diffuse.ReadFromStream(stream);
		Specular.ReadFromStream(stream);
		Ambient.ReadFromStream(stream);
		SpecularSharpness = stream.ReadFloat();
	}
}