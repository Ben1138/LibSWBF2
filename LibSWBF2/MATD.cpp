#include "stdafx.h"
#include "MATD.h"

namespace LibSWBF2::Chunks::Mesh
{
	MATD::MATD()
	{

	}

	MATD::~MATD()
	{

	}

	void MATD::RefreshSize()
	{
		m_Name.RefreshSize();
		m_Data.RefreshSize();
		m_Attribute.RefreshSize();
		m_Texture0.RefreshSize();
		m_Texture1.RefreshSize();
		m_Texture2.RefreshSize();
		m_Texture3.RefreshSize();

		m_Size = m_Name.GetSize() + m_Data.GetSize() + m_Attribute.GetSize();

		if (m_Texture0.m_Text.size() > 0)
		{
			m_Size += m_Texture0.GetSize();
		}

		if (m_Texture1.m_Text.size() > 0)
		{
			m_Size += m_Texture1.GetSize();
		}

		if (m_Texture2.m_Text.size() > 0)
		{
			m_Size += m_Texture2.GetSize();
		}

		if (m_Texture3.m_Text.size() > 0)
		{
			m_Size += m_Texture3.GetSize();
		}
	}

	void MATD::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_Name.WriteToStream(stream);
		m_Data.WriteToStream(stream);
		m_Attribute.WriteToStream(stream);

		if (m_Texture0.m_Text.size() > 0)
		{
			m_Texture0.WriteToStream(stream);
		}

		if (m_Texture1.m_Text.size() > 0)
		{
			m_Texture1.WriteToStream(stream);
		}

		if (m_Texture2.m_Text.size() > 0)
		{
			m_Texture2.WriteToStream(stream);
		}

		if (m_Texture3.m_Text.size() > 0)
		{
			m_Texture3.WriteToStream(stream);
		}
	}

	void MATD::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		while (PositionInChunk(stream.GetPosition()))
		{
			ChunkHeader head = stream.ReadChunkHeader(true);

			if (head == HeaderNames::NAME)
			{
				m_Name.ReadFromStream(stream);
			}
			else if (head == HeaderNames::DATA)
			{
				m_Data.ReadFromStream(stream);
			}
			else if (head == HeaderNames::ATRB)
			{
				m_Attribute.ReadFromStream(stream);
			}
			else if (head == HeaderNames::TX0D)
			{
				m_Texture0.ReadFromStream(stream);
			}
			else if (head == HeaderNames::TX1D)
			{
				m_Texture1.ReadFromStream(stream);
			}
			else if (head == HeaderNames::TX2D)
			{
				m_Texture2.ReadFromStream(stream);
			}
			else if (head == HeaderNames::TX3D)
			{
				m_Texture3.ReadFromStream(stream);
			}
			else
			{
				UnexpectedChunk(stream);
			}
		}
	}
}