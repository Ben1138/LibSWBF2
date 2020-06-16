#include "stdafx.h"
#include "MSH.h"
#include "Logging/Logger.h"
#include "FileReader.h"
#include "FileWriter.h"

namespace LibSWBF2::Chunks::MSH
{
	MSH* MSH::Create()
	{
		return new MSH();
	}

	void MSH::Destroy(MSH* msh)
	{
		delete msh;
	}

	void MSH::RefreshSize()
	{
		m_ShadowVolume.RefreshSize();
		m_MeshBlock.RefreshSize();
		m_Animations.RefreshSize();

		m_Size = m_ShadowVolume.GetDataSize() + m_MeshBlock.GetDataSize() + m_Animations.GetDataSize();
	}

	void MSH::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_ShadowVolume.WriteToStream(stream);
		m_MeshBlock.WriteToStream(stream);
		m_Animations.WriteToStream(stream);
	}

	void MSH::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		if (m_Header != "HEDR"_h)
		{
			LOG_ERROR("This is not a valid MSH file!");
		}

		while (PositionInChunk(stream.GetPosition()))
		{
			ChunkHeader head = stream.ReadChunkHeader(true);

			// sadly, switch-case is not possible here (Error C2051)
			if (head == "SHVO"_h)
			{
				m_ShadowVolume.ReadFromStream(stream);
			}
			else if (head == "MSH2"_h)
			{
				m_MeshBlock.ReadFromStream(stream);
			}
			else if (head == "BLN2"_h)
			{
				// Blend Chunks not supported
				SkipChunk(stream, false);
			}
			else if (head == "SKL2"_h)
			{
				// possibly deprecated, not supported
				SkipChunk(stream, false);
			}
			else if (head == "ANM2"_h)
			{
				m_Animations.ReadFromStream(stream);
			}
			else if (head == "CL1L"_h)
			{
				// EoF reached;
				LOG_INFO("Reached end of file!");
				return;
			}
			else
			{
				SkipChunk(stream);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}
}