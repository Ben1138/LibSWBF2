#include "stdafx.h"
#include "Terrain.h"
#include "InternalHelpers.h"

namespace LibSWBF2::Wrappers
{
	using Chunks::LVL::terrain::PTCH;
	using Chunks::LVL::terrain::VBUF;
	using Chunks::LVL::terrain::IBUF;

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

		float_t& gridUnitSize = out.p_Terrain->p_Info->m_GridUnitSize;
		uint16_t& patchEdgeSize = out.p_Terrain->p_Info->m_PatchEdgeSize;
		float_t patchDistance = gridUnitSize * patchEdgeSize;

		uint16_t numPatchesPerRow = out.p_Terrain->p_Info->m_GridSize / out.p_Terrain->p_Info->m_PatchEdgeSize;
		uint16_t patchColumnIndex = 0;

		// start offset in negative size/2, so terrain origin lies in the center
		float_t distToCenter = (out.p_Terrain->p_Info->m_GridSize * gridUnitSize) / 2.0f;
		glm::vec3 patchOffset = { -distToCenter, 0.0f, -distToCenter };

		List<PTCH*>& patches = out.p_Terrain->p_Patches->m_Patches;

		for (size_t i = 0; i < patches.Size(); ++i)
		{
			VBUF* vertexBuffer = patches[i]->m_GeometryBuffer;
			if (vertexBuffer == nullptr)
			{
				LOG_WARN("Patch with index {} does not have any vertex buffer! Skipping...", i);
				continue;
			}

			if (vertexBuffer->m_ElementSize != 28)
			{
				LOG_WARN("Expected terrain VBUF buffer entry size of 28, but got {}! Patch index: {}", vertexBuffer->m_ElementSize, i);
				continue;
			}

			List<Types::TerrainBufferEntry>& terrainBuffer = vertexBuffer->m_TerrainBuffer;
			if (vertexBuffer->m_ElementCount != terrainBuffer.Size())
			{
				LOG_ERROR("Specified element count '{}' does not match up with actual buffer size '{}'! Patch index: {}", vertexBuffer->m_ElementCount, terrainBuffer.Size(), i);
				continue;
			}

			// apparently patch data overlaps with neighbouring patches by one (e.g. 9x9=81 instead of 8x8=64)
			uint16_t dataEdgeSize = patchEdgeSize + 1;
			uint32_t numVertsPerPatch = dataEdgeSize * dataEdgeSize;
			if (vertexBuffer->m_ElementCount > numVertsPerPatch)
			{
				LOG_WARN("Expected {} vertices per geometry patch, but got: {}! Ignoring remaining...  Patch index: {}", numVertsPerPatch, vertexBuffer->m_ElementCount, i);
			}
			if (vertexBuffer->m_ElementCount < numVertsPerPatch)
			{
				LOG_WARN("Not enough vertices! Expected {} vertices per geometry patch, but got: {}! Skipping VBUF...  Patch index: {}", numVertsPerPatch, vertexBuffer->m_ElementCount, i);
				continue;
			}

			// calc patch offset
			if (patchColumnIndex >= numPatchesPerRow)
			{
				patchColumnIndex = 0;
				patchOffset.z += patchDistance;
			}
			patchOffset.x = (patchColumnIndex * patchDistance) - distToCenter;
			patchColumnIndex++;
				
			uint32_t index = 0;
			for (uint32_t x = 0; x < dataEdgeSize; ++x)
			{
				for (uint32_t y = 0; y < dataEdgeSize; ++y)
				{
					glm::vec3 pos = (ToGLM(terrainBuffer[index].m_Position) + patchOffset);
					out.m_Positions.Add(ToLib(pos));
					out.m_Normals.Add(terrainBuffer[index].m_Normal);
					out.m_Colors.Add(terrainBuffer[index].m_Color);

					float_t u = ((float_t)x / (float_t)(dataEdgeSize-1)) * 2.0f;
					float_t v = ((float_t)y / (float_t)(dataEdgeSize-1)) * 2.0f;
					out.m_TexCoords.Add({ u, v });

					++index;
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

				// apparently patch data overlaps with neighbouring patches by one (e.g. 9x9=81 instead of 8x8=64)
				uint16_t dataEdgeSize = patchEdgeSize + 1;

				uint32_t numPatches = (gridSize * gridSize) / (patchEdgeSize * patchEdgeSize);
				uint32_t verticesPerPatch = dataEdgeSize * dataEdgeSize;

				size_t numStoredPatches = p_Terrain->p_Patches->m_Patches.Size();
				if (numStoredPatches != numPatches)
				{
					LOG_ERROR("Expected {} patches according to info data, but found {}!", numPatches, numStoredPatches);
					return false;
				}

				for (uint16_t i = 0; i < numPatches; ++i)
				{
					// geometry index buffer is optional, most patches don't have them.
					// this is most likely only for patches with baked in terrain cuts.
					// if no custom index buffer is specified, build the index buffer ourselfs
					IBUF* indexBuffer = p_Terrain->p_Patches->m_Patches[i]->m_GeometryIndexBuffer;
					if (indexBuffer != nullptr)
					{
						indices.Append(TriangleStripToTriangleList(indexBuffer->m_IndexBuffer, i * verticesPerPatch));
					}
					else
					{
						// actually z in world space (y is height), but whatever...
						for (uint16_t y = 0; y < patchEdgeSize; ++y)
						{
							for (uint16_t x = 0; x < patchEdgeSize; ++x)
							{
								uint32_t globalX = x + (i * verticesPerPatch);
								uint32_t globalY = y + (i * verticesPerPatch);

								uint16_t a, b, c, d;

								// get 4 points for quad
								a = globalX + (y * dataEdgeSize);
								b = globalX + ((y + 1) * dataEdgeSize);
								c = (globalX + 1) + (y * dataEdgeSize);
								d = (globalX + 1) + ((y + 1) * dataEdgeSize);

								// triangle 1 clockwise
								indices.Add(a);
								indices.Add(b);
								indices.Add(c);

								// triangle 2 clockwise
								indices.Add(c);
								indices.Add(b);
								indices.Add(d);
							}
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

	void Terrain::GetUVBuffer(uint32_t& count, Vector2*& uvBuffer) const
	{
		count = (uint32_t)m_TexCoords.Size();
		uvBuffer = m_TexCoords.GetArrayPtr();
	}

	String Terrain::GetName() const
	{
		return p_Terrain->p_Name->m_Text;
	}
}