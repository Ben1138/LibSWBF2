#include "stdafx.h"
#include "MSH2.h"

namespace LibSWBF2::Chunks::Mesh
{
	void MSH2::RefreshSize()
	{
		m_SceneInformation.RefreshSize();
		m_MaterialList.RefreshSize();

		m_Size = m_SceneInformation.GetSize() + m_MaterialList.GetSize();
	}

	void MSH2::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_SceneInformation.WriteToStream(stream);
		m_MaterialList.WriteToStream(stream);
	}

	void MSH2::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		while (PositionInChunk(stream.GetPosition()))
		{
			ChunkHeader head = stream.ReadChunkHeader(true);

			if (head == HeaderNames::SINF)
			{
				m_SceneInformation.ReadFromStream(stream);
			}
			else if (head == HeaderNames::MATL)
			{
				m_MaterialList.ReadFromStream(stream);
			}
			else if (head == HeaderNames::MODL)
			{
				MODL& model = m_Models.emplace_back();
				model.ReadFromStream(stream);
			}
			else
			{
				UnexpectedChunk(stream);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}
}