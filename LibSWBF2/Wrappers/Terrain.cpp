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
		if (terrainChunk->p_Patches == nullptr || terrainChunk->p_Patches->m_Patches.Size() == 0)
		{
			// there is simply no terrain data present
			return false;
		}

		out.p_Terrain = terrainChunk;

		List<PTCH*>& patches = out.p_Terrain->p_Patches->m_Patches;
		for (size_t i = 0; i < patches.Size(); ++i)
		{
			List<VBUF*>& buffers = patches[i]->m_Buffers;
			for (size_t j = 0; j < buffers.Size(); ++j)
			{
				if (buffers[j]->m_BufferType == ETerrainBufferType::Geometry)
				{
					if (buffers[j]->m_ElementSize != 28)
					{
						LOG_WARN("Expected terrain VBUF buffer entry size of 28, but got {}!", buffers[j]->m_ElementSize);
						continue;
					}

					// apparently patch data overlaps with neighbouring patches by one (9x9=81 instead of 8x8=64)
					uint16_t dataEdgeSize = out.p_Terrain->p_Info->m_PatchEdgeSize + 1;
					uint32_t numVertsPerPatch = dataEdgeSize * dataEdgeSize;
					if (buffers[j]->m_ElementCount != numVertsPerPatch)
					{
						LOG_WARN("Expected {} vertices per geometry patch, but got: {}!", numVertsPerPatch, buffers[j]->m_ElementCount);
						continue;
					}

					List<Types::TerrainBufferEntry>& terrainBuffer = buffers[j]->m_TerrainBuffer;
					for (size_t k = 0; k < terrainBuffer.Size(); ++k)
					{
						out.m_Positions.Add(terrainBuffer[k].m_Position);
						out.m_Normals.Add(terrainBuffer[k].m_Normal);
						out.m_Colors.Add(terrainBuffer[k].m_Color);
					}
				}
			}
		}

		return true;
	}

	bool Terrain::GetIndexBuffer(ETopology requestedTopology, uint32_t& count, uint16_t*& indexBuffer) const
	{
		static List<uint16_t> indices;
		static ETopology lastRequestedTopology;

		if (indices.Size() == 0 || requestedTopology != lastRequestedTopology)
		{
			indices.Clear();

			bool bClockwise = true;
			if (requestedTopology == ETopology::TriangleList)
			{
				uint16_t dataEdgeSize = p_Terrain->p_Info->m_PatchEdgeSize + 1;
				// actually z in world space (y is height), but whatever...
				for (uint16_t y = 0; y < dataEdgeSize; ++y)
				{
					for (uint16_t x = 0; x < dataEdgeSize; ++x)
					{
						// skip the overlapping vertices
						if (x >= dataEdgeSize - 2 && y >= dataEdgeSize - 2)
						{
							continue;
						}
						if (bClockwise)
						{
							// clockwise
							indices.Add(x + (y * dataEdgeSize));
							indices.Add(x + ((y + 1) * dataEdgeSize));
							indices.Add((x + 1) + (y * dataEdgeSize));
						}
						else
						{
							indices.Add((x + 1) + (y * dataEdgeSize));
							indices.Add(x + (y * dataEdgeSize));
							indices.Add(x + ((y + 1) * dataEdgeSize));
						}
						bClockwise = !bClockwise;
					}
				}
			}
			else
			{
				LOG_WARN("Requested terrain index buffer as (yet) unsupported topology '{}'!", TopologyToString(requestedTopology));
				return false;
			}

			lastRequestedTopology = requestedTopology;
		}

		count = (uint32_t)indices.Size();
		indexBuffer = indices.GetArrayPtr();
		return true;
	}

	void Terrain::GetVertexBuffer(uint32_t& count, Vector3*& vertexBuffer) const
	{
		count = (uint32_t)m_Positions.Size();
		vertexBuffer = m_Positions.GetArrayPtr();
	}

	void Terrain::GetNormalBuffer(uint32_t& count, Vector3*& normalBuffer) const
	{
		count = (uint32_t)m_Normals.Size();
		normalBuffer = m_Normals.GetArrayPtr();
	}

	void Terrain::GetColorBuffer(uint32_t& count, Color*& colorBuffer) const
	{
		count = (uint32_t)m_Colors.Size();
		colorBuffer = m_Colors.GetArrayPtr();
	}

	String Terrain::GetName() const
	{
		return p_Terrain->p_Name->m_Text;
	}
}