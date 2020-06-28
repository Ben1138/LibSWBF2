#include "stdafx.h"
#include "Terrain.h"
#include "InternalHelpers.h"

namespace LibSWBF2::Wrappers
{
	using Chunks::LVL::terrain::PTCH;
	using Chunks::LVL::terrain::VBUF;

	bool Terrain::FromChunk(Level* mainContainer, tern* terrainChunk, Terrain& out)
	{
		if (mainContainer == nullptr)
		{
			LOG_ERROR("Given mainContainer was NULL!");
			return false;
		}
		if (terrainChunk == nullptr)
		{
			LOG_ERROR("Given terrainChunk was NULL!");
			return false;
		}

		out.p_Terrain = terrainChunk;
		List<VBUF*> geometryPatches;

		List<PTCH*>& patches = out.p_Terrain->p_Patches->m_Patches;
		for (size_t i = 0; i < patches.Size(); ++i)
		{
			List<VBUF*>& buffers = patches[i]->m_Buffers;

			for (size_t j = 0; j < buffers.Size(); ++j)
			{
				if (buffers[j]->m_BufferType == ETerrainBufferType::Geometry)
				{
					geometryPatches.Add(buffers[j]);
				}
			}
		}

		return true;
	}

	String Terrain::GetName() const
	{
		return p_Terrain->p_Name->m_Text;
	}
}