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
		m_SINF.RefreshSize();
		m_MATL.RefreshSize();

		m_Size = m_SINF.GetSize() + m_MATL.GetSize();
	}

	void MSH2::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_SINF.WriteToStream(stream);
		m_MATL.WriteToStream(stream);
	}

	void MSH2::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_SINF.ReadFromStream(stream);
		m_MATL.ReadFromStream(stream);
	}
}