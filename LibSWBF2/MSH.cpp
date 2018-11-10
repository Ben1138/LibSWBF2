#include "stdafx.h"
#include "MSH.h"

namespace LibSWBF2::Chunks::Mesh
{
	LIBSWBF2_EXP MSH* MSH::Create()
	{
		return new MSH();
	}

	LIBSWBF2_EXP void MSH::Destroy(MSH* msh)
	{
		if (msh == nullptr)
		{
			LOG("Given MSH Pointer was NULL!", ELogType::Error);
			return;
		}

		delete msh;
	}

	void MSH::RefreshSize()
	{
		m_ShadowVolume.RefreshSize();
		m_MeshBlock.RefreshSize();
		m_Animations.RefreshSize();

		m_Size = m_ShadowVolume.GetSize() + m_MeshBlock.GetSize() + m_Animations.GetSize();
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

		while (PositionInChunk(stream.GetPosition()))
		{
			ChunkHeader head = stream.ReadChunkHeader(true);

			// sadly, switch-case is not possible here (Error C2051)
			if (head == HeaderNames::SHVO)
			{
				m_ShadowVolume.ReadFromStream(stream);
			}
			else if (head == HeaderNames::MSH2)
			{
				m_MeshBlock.ReadFromStream(stream);
			}
			else if (head == HeaderNames::BLN2)
			{
				// Blend Chunks not supported
				SkipChunk(stream, false);
			}
			else if (head == HeaderNames::ANM2)
			{
				m_Animations.ReadFromStream(stream);
			}
			else if (head == HeaderNames::CL1L)
			{
				// EoF reached;
				LOG("Reached end of file!", ELogType::Info);
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