#include "stdafx.h"
#include "Terrain.h"
#include "InternalHelpers.h"

namespace LibSWBF2::Wrappers
{
	using Chunks::LVL::terrain::PTCH;
	using Chunks::LVL::terrain::VBUF;
	using Chunks::LVL::terrain::IBUF;

	bool Terrain::FromChunk(tern* terrainChunk, Terrain& out)
	{
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

	Terrain::Terrain()
	{
		p_HeightMap = nullptr;
		p_BlendMap = nullptr;
	}

	Terrain::~Terrain()
	{
		delete p_HeightMap;
		delete p_BlendMap;
	}


	void Terrain::GetBlendMap(uint32_t& dim, uint32_t& numTexLayers, uint8_t*& finalBlendMapData) const
	{
		auto *info = p_Terrain -> p_Info;
		dim = (uint32_t) info -> m_GridSize;
		numTexLayers = (uint32_t) info -> m_TextureCount;

		if (p_BlendMap == nullptr)
		{
			uint16_t numVertsPerPatchEdge = info->m_PatchEdgeSize;
			uint16_t dataEdgeSize = numVertsPerPatchEdge + 1;
			uint16_t numPatchesPerRow = dim / numVertsPerPatchEdge;

			int dataLength = dim * dim * numTexLayers;
	        p_BlendMap = new uint8_t[dataLength]();

			List<PTCH*>& patches = p_Terrain->p_Patches->m_Patches;

			for (size_t i = 0; i < patches.Size(); i++)
			{	
				auto *curPatch = patches[i];
				auto *patchInfo = curPatch -> p_PatchInfo;
				auto *patchSplatChunk = curPatch -> m_TextureBuffer;
				const List<uint8_t>& curPatchBlendMap = patchSplatChunk -> m_BlendMapData;

	            List<uint32_t>& slotsList = patchInfo -> m_TextureSlotsUsed;
	            int numSlotsInPatch = slotsList.Size();

				int globalPatchY = i / (int) numPatchesPerRow;
				int globalPatchX = i % (int) numPatchesPerRow;

				int patchStartIndex = globalPatchY * numVertsPerPatchEdge * numPatchesPerRow * numVertsPerPatchEdge + globalPatchX * numVertsPerPatchEdge;

				for (int j = 0; j < patchSplatChunk -> m_ElementCount; j++)
				{
					int localPatchY = j / dataEdgeSize; 
					int localPatchX = j % dataEdgeSize;

					//Starting index into final array (finalBlendMapData)
					int globalDataIndex = numTexLayers * (patchStartIndex + localPatchY * numVertsPerPatchEdge * numPatchesPerRow + localPatchX);
					
					//Index into current patch's VBUF's blend data (curPatchBlendMap)
					int localPatchIndex = numSlotsInPatch * (localPatchY * dataEdgeSize + localPatchX);

					for (int k = 0; k < numSlotsInPatch; k++)
					{
						int slot = (int) slotsList[k];
						int finalDataIndex = globalDataIndex + slot;

						if (finalDataIndex < dataLength)
						{	
							p_BlendMap[finalDataIndex] = (uint8_t) curPatchBlendMap[localPatchIndex + k];
						}
					}
				}
			}
		}

		finalBlendMapData = p_BlendMap;  
	}


	bool Terrain::GetIndexBuffer(ETopology requestedTopology, uint32_t& count, uint32_t*& indexBuffer) const
	{
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


	void Terrain::GetHeightMap(uint32_t& dim, uint32_t& dimScale, float_t*& heightData) const
    {
        auto info = p_Terrain -> p_Info;
    	dim = (uint32_t) info -> m_GridSize;
		dimScale = (uint32_t) info -> m_GridUnitSize;

    	if (p_HeightMap == nullptr) //lazy init
    	{
    		LOG_WARN("Initializing heightmap");

	        float_t gridSize     = (float_t) dim;
			float_t gridUnitSize = (float_t) info -> m_GridUnitSize;

			float_t maxY = info -> m_HeightCeiling;
	       	float_t minY = info -> m_HeightFloor;

	       	float_t halfLength = gridSize * gridUnitSize / 2.0f;
	       	float_t maxZ = halfLength, minZ = halfLength * -1.0f;
	       	float_t maxX = halfLength, minX = halfLength * -1.0f;

	       	int heightDataLength = dim * dim;
			p_HeightMap = new float_t[heightDataLength]();

			uint32_t ibufLength;
			uint32_t *ibufData;
			GetIndexBuffer(ETopology::TriangleList, ibufLength, ibufData);

			//Inits to -5.96541e+29
			memset((void *) p_HeightMap, 0xf0, sizeof(float_t) * heightDataLength);

			for (int i = 0; i < (int) ibufLength; i++)
			{
				const Vector3& curVert = m_Positions[ibufData[i]];

				if (fmod(curVert.m_X, gridUnitSize) > .1 || //omit irregularities
					fmod(curVert.m_Z, gridUnitSize) > .1)
				{
					continue;
				}
	        	
	        	uint32_t uIndex = (uint32_t) ((curVert.m_X - minX)/gridUnitSize + .001f);
	        	uint32_t vIndex = (uint32_t) ((curVert.m_Z - minZ)/gridUnitSize + .001f);

	            if (uIndex < dim && vIndex < dim)
	            {
	                p_HeightMap[uIndex + vIndex * dim] = (curVert.m_Y - minY)/(maxY - minY);
	            }
			}
		}

		heightData = p_HeightMap;
	}


	void Terrain::GetHeightBounds(float_t& floor, float_t& ceiling) const 
	{
		ceiling = p_Terrain -> p_Info -> m_HeightCeiling;
       	floor   = p_Terrain -> p_Info -> m_HeightFloor;
	}


	const List<String>& Terrain::GetLayerTextures() const
	{
		return p_Terrain->p_LayerTextures->m_LayerTextures;
	}
}
