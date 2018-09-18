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
		m_MATL.RefreshSize();

		Size = sinf.GetSize() + m_MATL.GetSize();*/
	}

	void MODL::WriteToStream(FileWriter& stream)
	{
		/*BaseChunk::WriteToStream(stream);
		sinf.WriteToStream(stream);
		m_MATL.WriteToStream(stream);*/
	}

	void MODL::ReadFromStream(FileReader& stream)
	{
		/*BaseChunk::ReadFromStream(stream);
		sinf.ReadFromStream(stream);
		m_MATL.ReadFromStream(stream);*/
	}
}