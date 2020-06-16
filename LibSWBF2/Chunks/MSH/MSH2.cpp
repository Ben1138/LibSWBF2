#include "stdafx.h"
#include "MSH2.h"
#include "FileReader.h"
#include "FileWriter.h"

namespace LibSWBF2::Chunks::MSH
{
	void MSH2::RefreshSize()
	{
		m_SceneInformation.RefreshSize();
		m_MaterialList.RefreshSize();

		m_Size = m_SceneInformation.GetDataSize() + m_MaterialList.GetDataSize();
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

			if (head == "SINF"_h)
			{
				m_SceneInformation.ReadFromStream(stream);
			}
			else if (head == "CAMR"_h)
			{
				//CAMR Chunks not supported
				SkipChunk(stream, false);
			}
			else if (head == "MATL"_h)
			{
				m_MaterialList.ReadFromStream(stream);
			}
			else if (head == "MODL"_h)
			{
				MODL& model = m_Models.Emplace();
				model.ReadFromStream(stream);
			}
			else
			{
				SkipChunk(stream);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}
}