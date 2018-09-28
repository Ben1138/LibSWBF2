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
		m_NAME.RefreshSize();
		m_MTYP.RefreshSize();
		m_PRNT.RefreshSize();
		m_FLGS.RefreshSize();
		m_TRAN.RefreshSize();

		m_Size = m_NAME.GetSize() + m_MTYP.GetSize() + m_PRNT.GetSize() + m_FLGS.GetSize() + m_TRAN.GetSize();
	}

	void MODL::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_NAME.WriteToStream(stream);
		m_MTYP.WriteToStream(stream);
		m_PRNT.WriteToStream(stream);
		m_FLGS.WriteToStream(stream);
		m_TRAN.WriteToStream(stream);
	}

	void MODL::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_NAME.ReadFromStream(stream);
		m_MTYP.ReadFromStream(stream);
		m_PRNT.ReadFromStream(stream);
		m_FLGS.ReadFromStream(stream);
		m_TRAN.ReadFromStream(stream);
	}
}