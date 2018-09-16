#include "stdafx.h"
#include "MSH2.h"

namespace LibSWBF2::Chunks::Mesh
{
	MSH2::MSH2()
	{

	}

	MSH2::~MSH2()
	{

	}

	void MSH2::RefreshSize()
	{
		sinf.RefreshSize();
		matl.RefreshSize();

		Size = sinf.GetSize() + matl.GetSize();
	}

	void MSH2::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		sinf.WriteToStream(stream);
		matl.WriteToStream(stream);
	}

	void MSH2::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		sinf.ReadFromStream(stream);
		matl.ReadFromStream(stream);
	}
}