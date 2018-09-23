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
		m_NAME.RefreshSize();
		m_DATA.RefreshSize();
		m_TX0D.RefreshSize();
		m_TX1D.RefreshSize();
		m_TX2D.RefreshSize();
		m_TX3D.RefreshSize();

		m_Size = m_NAME.GetSize() + m_DATA.GetSize();

		if (m_TX0D.m_Text.size() > 0)
			m_Size += m_TX0D.GetSize();

		if (m_TX1D.m_Text.size() > 0)
			m_Size += m_TX1D.GetSize();

		if (m_TX2D.m_Text.size() > 0)
			m_Size += m_TX2D.GetSize();

		if (m_TX3D.m_Text.size() > 0)
			m_Size += m_TX3D.GetSize();
	}

	void MATD::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_NAME.WriteToStream(stream);
		m_DATA.WriteToStream(stream);

		if (m_TX0D.m_Text.size() > 0)
			m_TX0D.WriteToStream(stream);

		if (m_TX1D.m_Text.size() > 0)
			m_TX1D.WriteToStream(stream);

		if (m_TX2D.m_Text.size() > 0)
			m_TX2D.WriteToStream(stream);

		if (m_TX3D.m_Text.size() > 0)
			m_TX3D.WriteToStream(stream);
	}

	void MATD::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		ChunkHeader head = stream.ReadChunkHeader(true);

		if (head == HeaderNames::NAME)
		{
			m_NAME.ReadFromStream(stream);
		}
		else if (head == HeaderNames::DATA)
		{
			m_DATA.ReadFromStream(stream);
		}
		else if (head == HeaderNames::TX0D)
		{
			m_TX0D.ReadFromStream(stream);
		}
		else if (head == HeaderNames::TX1D)
		{
			m_TX1D.ReadFromStream(stream);
		}
		else if (head == HeaderNames::TX2D)
		{
			m_TX2D.ReadFromStream(stream);
		}
		else if (head == HeaderNames::TX3D)
		{
			m_TX3D.ReadFromStream(stream);
		}
		else
		{
			LOG("Unknown Chunk found: " + HeaderNames::GetHeaderString(head), ELogType::Warning);
		}
	}
}