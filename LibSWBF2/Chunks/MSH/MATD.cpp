#include "stdafx.h"
#include "MATD.h"
#include "FileReader.h"
#include "FileWriter.h"

namespace LibSWBF2::Chunks::MSH
{
	void MATD::RefreshSize()
	{
		m_Name.RefreshSize();
		m_Data.RefreshSize();
		m_Attribute.RefreshSize();
		m_Texture0.RefreshSize();
		m_Texture1.RefreshSize();
		m_Texture2.RefreshSize();
		m_Texture3.RefreshSize();

		m_Size = m_Name.GetDataSize() + m_Data.GetDataSize() + m_Attribute.GetDataSize();

		if (m_Texture0.m_Text.Length() > 0)
		{
			m_Size += m_Texture0.GetDataSize();
		}

		if (m_Texture1.m_Text.Length() > 0)
		{
			m_Size += m_Texture1.GetDataSize();
		}

		if (m_Texture2.m_Text.Length() > 0)
		{
			m_Size += m_Texture2.GetDataSize();
		}

		if (m_Texture3.m_Text.Length() > 0)
		{
			m_Size += m_Texture3.GetDataSize();
		}
	}

	void MATD::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_Name.WriteToStream(stream);
		m_Data.WriteToStream(stream);
		m_Attribute.WriteToStream(stream);

		if (m_Texture0.m_Text.Length() > 0)
		{
			m_Texture0.WriteToStream(stream);
		}

		if (m_Texture1.m_Text.Length() > 0)
		{
			m_Texture1.WriteToStream(stream);
		}

		if (m_Texture2.m_Text.Length() > 0)
		{
			m_Texture2.WriteToStream(stream);
		}

		if (m_Texture3.m_Text.Length() > 0)
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

			if (head == "NAME"_h)
			{
				m_Name.ReadFromStream(stream);
			}
			else if (head == "DATA"_h)
			{
				m_Data.ReadFromStream(stream);
			}
			else if (head == "ATRB"_h)
			{
				m_Attribute.ReadFromStream(stream);
			}
			else if (head == "TX0D"_h)
			{
				m_Texture0.ReadFromStream(stream);
			}
			else if (head == "TX1D"_h)
			{
				m_Texture1.ReadFromStream(stream);
			}
			else if (head == "TX2D"_h)
			{
				m_Texture2.ReadFromStream(stream);
			}
			else if (head == "TX3D"_h)
			{
				m_Texture3.ReadFromStream(stream);
			}
			else
			{
				SkipChunk(stream);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}
}