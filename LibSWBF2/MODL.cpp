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
		m_Name.RefreshSize();
		m_ModelType.RefreshSize();
		m_Parent.RefreshSize();
		m_Flags.RefreshSize();
		m_Transition.RefreshSize();

		m_Size = m_Name.GetSize() + m_ModelType.GetSize() + m_Parent.GetSize() + m_Flags.GetSize() + m_Transition.GetSize();
	}

	void MODL::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_Name.WriteToStream(stream);
		m_ModelType.WriteToStream(stream);
		m_Parent.WriteToStream(stream);
		m_Flags.WriteToStream(stream);
		m_Transition.WriteToStream(stream);
	}

	void MODL::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		m_Name.ReadFromStream(stream);
		m_ModelType.ReadFromStream(stream);
		m_Parent.ReadFromStream(stream);
		m_Flags.ReadFromStream(stream);
		m_Transition.ReadFromStream(stream);
	}
}