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
			// there's simply no terrain data present
			return false;
		}

		out.p_Terrain = terrainChunk;

		Vector3 patchOffset = { 0.0f, 0.0f, 0.0f };
		uint16_t numPatchesPerRow = out.p_Terrain->p_Info->m_GridSize / out.p_Terrain->p_Info->m_PatchEdgeSize;
		uint16_t patchColumnIndex = 0;

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

					// apparently patch data overlaps with neighbouring patches by one (e.g. 9x9=81 instead of 8x8=64)
					uint16_t dataEdgeSize = out.p_Terrain->p_Info->m_PatchEdgeSize + 1;
					uint32_t numVertsPerPatch = dataEdgeSize * dataEdgeSize;
					if (buffers[j]->m_ElementCount != numVertsPerPatch)
					{
						LOG_WARN("Expected {} vertices per geometry patch, but got: {}!", numVertsPerPatch, buffers[j]->m_ElementCount);
						continue;
					}

					// calc patch offset
					if (patchColumnIndex >= numPatchesPerRow)
					{
						patchColumnIndex = 0;
						patchOffset.m_Z += out.p_Terrain->p_Info->m_GridUnitSize;
					}
					patchOffset.m_X = patchColumnIndex * out.p_Terrain->p_Info->m_GridUnitSize;
					patchColumnIndex++;

					//LOG_WARN("Patch offset: {}", patchOffset.ToString());

					List<Types::TerrainBufferEntry>& terrainBuffer = buffers[j]->m_TerrainBuffer;
					for (size_t k = 0; k < terrainBuffer.Size(); ++k)
					{
						glm::vec3 pos = ToGLM(terrainBuffer[k].m_Position) + ToGLM(patchOffset);
						out.m_Positions.Add(ToLib(pos));
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

			if (requestedTopology == ETopology::TriangleList)
			{
				uint16_t gridSize = p_Terrain->p_Info->m_GridSize;
				uint16_t patchEdgeSize = p_Terrain->p_Info->m_PatchEdgeSize;
				uint16_t dataEdgeSize = patchEdgeSize + 1;

				uint32_t numPatches = (gridSize * gridSize) / (patchEdgeSize * patchEdgeSize);
				uint32_t verticesPerPatch = dataEdgeSize * dataEdgeSize;

				for (uint16_t i = 0; i < 5/*numPatches*/; ++i)
				{
					// actually z in world space (y is height), but whatever...
					for (uint16_t y = 0; y < dataEdgeSize - 2; ++y)
					{
						for (uint16_t x = 0; x < dataEdgeSize - 2; ++x)
						{
							uint32_t globalX = x + (i * verticesPerPatch);
							uint32_t globalY = y + (i * verticesPerPatch);

							uint16_t a, b, c, d;

							// get 4 points for quad
							a = globalX + (globalY * dataEdgeSize);
							b = globalX + ((globalY + 1) * dataEdgeSize);
							c = (globalX + 1) + (globalY * dataEdgeSize);
							d = (globalX + 1) + ((globalY + 1) * dataEdgeSize);

							// draw triangle 1 clockwise
							indices.Add(a);
							indices.Add(b);
							indices.Add(c);

							// draw triangle 2 clockwise
							indices.Add(c);
							indices.Add(b);
							indices.Add(d);
						}
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