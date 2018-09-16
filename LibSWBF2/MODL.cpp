#include "stdafx.h"
#include "MODL.h"

namespace LibSWBF2::Chunks::Mesh
{
	MODL::MODL()
	{

	}

	MODL::~MODL()
	{

	}

	void MODL::RefreshSize()
	{
		/*sinf.RefreshSize();
		matl.RefreshSize();

		Size = sinf.GetSize() + matl.GetSize();*/
	}

	void MODL::WriteToStream(FileWriter& stream)
	{
		/*BaseChunk::WriteToStream(stream);
		sinf.WriteToStream(stream);
		matl.WriteToStream(stream);*/
	}

	void MODL::ReadFromStream(FileReader& stream)
	{
		/*BaseChunk::ReadFromStream(stream);
		sinf.ReadFromStream(stream);
		matl.ReadFromStream(stream);*/
	}
}