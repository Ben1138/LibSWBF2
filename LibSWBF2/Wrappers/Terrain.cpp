#include "stdafx.h"
#include "Terrain.h"
#include "InternalHelpers.h"

#include <iostream>
#define COUT(x) std::cout << x << std::endl

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

		uint16_t& gridSize = out.p_Terrain->p_Info->m_GridSize;
		float_t& gridUnitSize = out.p_Terrain->p_Info->m_GridUnitSize;
		uint16_t& numVertsPerPatchEdge = out.p_Terrain->p_Info->m_PatchEdgeSize;
		uint16_t dataEdgeSize = numVertsPerPatchEdge + 1;
		float_t patchDistance = gridUnitSize * numVertsPerPatchEdge;

		uint16_t numPatchesPerRow = gridSize / numVertsPerPatchEdge;
		uint16_t patchColumnIndex = 0;

		float_t terrainEdgeUnitSize = gridSize * gridUnitSize;
		float_t distToCenter = terrainEdgeUnitSize / 2.0f;
		
		// apparently patch data overlaps with neighbouring patches by one (e.g. 9x9=81 instead of 8x8=64)
		uint32_t numVertsPerPatch = dataEdgeSize * dataEdgeSize;

		// start offset in negative size/2, so terrain origin lies in the center
		// For some reason, terrain seems to be offset by gridUnitSize in Z direction...
		glm::vec3 patchOffset = { 0.0f, 0.0f, -distToCenter + gridUnitSize };

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
				LOG_WARN("Specified element count '{}' does not match up with actual buffer size '{}'! Patch index: {}", vertexBuffer->m_ElementCount, terrainBuffer.Size(), i);
				continue;
			}

			if (patches[i]->m_GeometryIndexBuffer == nullptr)
			{
				if (vertexBuffer->m_ElementCount > numVertsPerPatch)
				{
					LOG_WARN("Expected {} vertices per geometry patch, but got: {}! Ignoring remaining...  Patch index: {}", numVertsPerPatch, vertexBuffer->m_ElementCount, i);
				}
				if (vertexBuffer->m_ElementCount < numVertsPerPatch)
				{
					LOG_WARN("Not enough vertices! Expected {} vertices per geometry patch, but got: {}! Skipping VBUF...  Patch index: {}", numVertsPerPatch, vertexBuffer->m_ElementCount, i);
					continue;
				}
			}

			// calc patch offset
			if (patchColumnIndex >= numPatchesPerRow)
			{
				patchColumnIndex = 0;
				patchOffset.z += patchDistance;
			}
			patchOffset.x = (patchColumnIndex * patchDistance) - distToCenter;
			patchColumnIndex++;

			// If a custom index buffer is specified, use the entire provided vertex buffer.
			// If not, just just the expected amount. Apparently there're some VBUFs with more
			// vertices than expected, but no custom index buffer.
			// In those cases, we just ignore all remaining vertices.
			size_t numVertices = patches[i]->m_GeometryIndexBuffer != nullptr ? terrainBuffer.Size() : numVertsPerPatch;
			for (size_t j = 0; j < numVertices; ++j)
			{
				glm::vec3 pos = (ToGLM(terrainBuffer[j].m_Position) + patchOffset);
				out.m_Positions.Add(ToLib(pos));
				out.m_Normals.Add(terrainBuffer[j].m_Normal);
				out.m_Colors.Add(terrainBuffer[j].m_Color);

				// global UV calculation
				//float_t u = ((pos.x + distToCenter) / (terrainEdgeUnitSize)) * 2.0f;
				//float_t v = ((pos.z + distToCenter) / (terrainEdgeUnitSize)) * 2.0f;
				
				// per patch UV calculation
				float_t u = (terrainBuffer[j].m_Position.m_X / (dataEdgeSize * gridUnitSize)) * 2.0f;
				float_t v = (terrainBuffer[j].m_Position.m_Z / (dataEdgeSize * gridUnitSize)) * 2.0f;
				out.m_TexCoords.Add({ u, v });
			}
		}

		return true;
	}

	bool Terrain::GetIndexBuffer(ETopology requestedTopology, uint32_t& count, uint32_t*& indexBuffer) const
	{
		static List<uint32_t> indices;
		static ETopology lastRequestedTopology;

		if (indices.Size() == 0 || requestedTopology != lastRequestedTopology)
		{
			indices.Clear();

			if (requestedTopology == ETopology::TriangleList)
			{
				uint16_t& gridSize = p_Terrain->p_Info->m_GridSize;
				uint16_t& patchEdgeSize = p_Terrain->p_Info->m_PatchEdgeSize;

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

				uint32_t vertexOffset = 0;
				for (uint16_t i = 0; i < numPatches; ++i)
				{
					// geometry index buffer is optional, most patches don't have them.
					// this is most likely only for patches with baked in terrain cuts.
					// if no custom index buffer is specified, we build the index buffer ourselfs
					IBUF* indexBuffer = p_Terrain->p_Patches->m_Patches[i]->m_GeometryIndexBuffer;
					VBUF* vertexBuffer = p_Terrain->p_Patches->m_Patches[i]->m_GeometryBuffer;
					if (indexBuffer != nullptr)
					{
						List<uint32_t> triangleList = TriangleStripToTriangleList(indexBuffer->m_IndexBuffer, vertexOffset);
						indices.Append(triangleList);
						vertexOffset += (uint32_t)vertexBuffer->m_TerrainBuffer.Size();
					}
					else
					{
						// actually z in world space (y is height), but whatever...
						for (uint16_t y = 0; y < patchEdgeSize; ++y)
						{
							for (uint16_t x = 0; x < patchEdgeSize; ++x)
							{
								uint32_t globalX = x + vertexOffset;
								uint32_t globalY = y + vertexOffset;

								uint32_t a, b, c, d;

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

						vertexOffset += verticesPerPatch;
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

	void Terrain::GetVertexBufferRaw(uint32_t& count, float_t*& buffer) const
	{
        Vector3 *vertexBuffer = m_Positions.GetArrayPtr();
        uint32_t numVerts = m_Positions.Size();
        float_t *rawVerts = new float_t[numVerts * 3];
        
        for (int i = 0; i < numVerts; i++)
        {
            Vector3& curVert = vertexBuffer[i];
            rawVerts[i * 3]     = curVert.m_X;
            rawVerts[i * 3 + 1] = curVert.m_Y;
            rawVerts[i * 3 + 2] = curVert.m_Z;
        }
        
        count = numVerts;
        buffer = rawVerts;
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


	void Terrain::GetHeights(uint32_t& width, uint32_t& height, float_t*& heightData) const {

		float_t maxY = p_Terrain -> p_Info -> m_HeightCeiling;
       	float_t minY = p_Terrain -> p_Info -> m_HeightFloor;

        Vector3 *vertexBuffer = m_Positions.GetArrayPtr();
        uint32_t numVerts = m_Positions.Size();

		//These may already exist in member vars...
        float_t minX=1000000.0f,maxX=-100000.0f;
        float_t minZ=1000000.0f,maxZ=-100000.0f;

        //Hardcode for testing
		heightData = new float_t[256 * 81]();

        for (int i = 0; i < numVerts; i++)
        {
            Vector3& curVert = vertexBuffer[i];

        	minX = curVert.m_X < minX ? curVert.m_X : minX;
        	maxX = curVert.m_X > maxX ? curVert.m_X : maxX;

        	minZ = curVert.m_Z < minZ ? curVert.m_Z : minZ;
        	maxZ = curVert.m_Z > maxZ ? curVert.m_Z : maxZ;
        }

        //COUT("ABOUT TO READ HEIGHTS");

        for (int i = 0; i < numVerts; i++)
        {
        	Vector3& curVert = vertexBuffer[i];
        	float_t xFrac = (curVert.m_X - minX)/(maxX - minX);
        	float_t yFrac = (curVert.m_Y - minY)/(maxY - minY);
        	float_t zFrac = (curVert.m_Z - minZ)/(maxZ - minZ);

        	if (((int)curVert.m_X) % 128 == 0){
        		COUT(curVert.m_X);
        	}

        	int uIndex = (int) (xFrac * 9.0f * 16.0f + .00001f);
        	int vIndex = (int) (zFrac * 9.0f * 16.0f + .00001f);

        	heightData[uIndex + vIndex * 9 * 16] = yFrac;
        }

        auto info = p_Terrain -> p_Info;

       	COUT("Num verts: " << m_Positions.Size());
       	COUT(fmt::format("Gridsize: {}, Gridunitsize: {}, Patchedgesize: {}",
       					info -> m_GridSize,
       					info -> m_GridUnitSize,
       					info -> m_PatchEdgeSize));

       	COUT("Max X found: " << maxX);
       	COUT("Min X found: " << minX);
       	COUT("Max Z found: " << maxZ);
       	COUT("Min Z found: " << minZ);

        width = 9 * 16;
        height = 9 * 16;
	}



	const List<String>& Terrain::GetLayerTextures() const
	{
		return p_Terrain->p_LayerTextures->m_LayerTextures;
	}
}
