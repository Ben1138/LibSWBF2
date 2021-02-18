#include "stdafx.h"
#include "Segment.h"
#include "Level.h"
#include "InternalHelpers.h"

#include "Chunks/LVL/modl/LVL.modl.h"
#include "Chunks/LVL/modl/modl.segm.h"


namespace LibSWBF2::Wrappers
{
	using Types::List;
	using LibSWBF2::Chunks::LVL::modl::SKIN;
	using LibSWBF2::Chunks::LVL::modl::BMAP;
	using LibSWBF2::Chunks::LVL::modl::modl;
	using LibSWBF2::Chunks::LVL::skel::skel;


	bool Segment::FromChunk(Level* mainContainer, segm* segmentChunk, Segment& out)
	{
		if (segmentChunk == nullptr)
		{
			LOG_ERROR("Given SegmentChunk was NULL!");
			return false;
		}

		List<VBUF*>& vBuffs = segmentChunk->m_VertexBuffers;
		if (vBuffs.Size() == 0)
		{
			LOG_WARN("Segment Chunk does not contain any data!");
			return false;
		}

		out.p_Segment = segmentChunk;

		// find the VBUF we want to use, preferably one without compression
		out.p_VertexBuffer = nullptr;
		for (size_t i = 0; i < vBuffs.Size(); ++i)
		{
			// TODO: better selection / sorting?
			if ((vBuffs[i]->m_Flags & EVBUFFlags::Position) != 0 &&
				(vBuffs[i]->m_Flags & EVBUFFlags::Normal) != 0 &&
				(vBuffs[i]->m_Flags & EVBUFFlags::TexCoord) != 0 &&
				(vBuffs[i]->m_Flags & EVBUFFlags::PositionCompressed) == 0 &&
				(vBuffs[i]->m_Flags & EVBUFFlags::NormalCompressed) == 0 &&
				(vBuffs[i]->m_Flags & EVBUFFlags::TexCoordCompressed) == 0)
			{
				out.p_VertexBuffer = vBuffs[i];
				break;
			}
		}

		if (out.p_VertexBuffer == nullptr)
		{
			out.p_VertexBuffer = vBuffs[0];
		}

		if (!Material::FromChunk(mainContainer, segmentChunk->p_Material, out.m_Material))
		{
			LOG_WARN("Could not read Material!");
		}

		// Create weight buffer
		modl* parent = dynamic_cast<modl*>(out.p_Segment->GetParent());
		skel* skeleton = mainContainer->FindSkeleton(parent->p_Name->m_Text);
		if (skeleton != nullptr)
		{
			SKIN* skin = out.p_Segment->p_Skin;
			BMAP* boneMap = out.p_Segment->p_BoneMap;

			auto& boneIndicies = out.p_VertexBuffer -> m_BoneIndicies;
			auto& boneWeights  = out.p_VertexBuffer -> m_Weights;

			if (boneIndicies.Size() > 0)
			{
				if (boneMap == nullptr)
				{
					LOG_ERROR("Bone map missing...");
					return true;			
				}

				if (boneWeights.Size() != 0)
				{
					for (int i = 0; i < boneIndicies.Size(); i++)
					{
						uint8_t index =  boneIndicies[i].m_X;
						uint8_t index1 = boneIndicies[i].m_Y;
						uint8_t index2 = boneIndicies[i].m_Z;

						if (index  >= boneMap->m_IndexCount || 
							index1 >= boneMap->m_IndexCount ||
							index2 >= boneMap->m_IndexCount)
						{
							LOG_ERROR("Softskin index ({},{},{}) is >= bone map length {}", index, index1, index2, boneMap->m_IndexCount);
						}
						else 
						{
							index = (uint8_t)  boneMap->m_IndexMap[index];
							index1 = (uint8_t) boneMap->m_IndexMap[index1];
							index2 = (uint8_t) boneMap->m_IndexMap[index2];
						}

						out.m_VertexWeights.Add({ boneWeights[i].m_X, index });
						out.m_VertexWeights.Add({ boneWeights[i].m_Y, index1 });
						out.m_VertexWeights.Add({ boneWeights[i].m_Z, index2 });
					}
				}
				else 
				{
					for (int i = 0; i < boneIndicies.Size(); i++)
					{
						uint8_t index = boneIndicies[i].m_X;

						if (index >= boneMap->m_IndexCount)
						{
							LOG_ERROR("Index {} is >= bone map length {}", index, boneMap->m_IndexCount);
						}
						else 
						{
							index = (uint8_t) boneMap->m_IndexMap[index];
						}

						out.m_VertexWeights.Add({ 1.0f, index });
					}
				}
			}
		}

		return true;
	}

	ETopology Segment::GetTopology() const
	{
		return p_Segment->p_Info->m_Topology;
	}

	const Material& Segment::GetMaterial() const
	{
		return m_Material;
	}

	void Segment::GetIndexBuffer(uint32_t& count, uint16_t*& indexBuffer) const
	{
		count = p_Segment->p_IndexBuffer->m_IndicesCount;
		indexBuffer = p_Segment->p_IndexBuffer->m_Indices.GetArrayPtr();
	}

	void Segment::GetVertexBuffer(uint32_t& count, Vector3*& vertexBuffer) const
	{
		count = (uint32_t)p_VertexBuffer->m_Positions.Size();
		vertexBuffer = p_VertexBuffer->m_Positions.GetArrayPtr();
	}

	void Segment::GetNormalBuffer(uint32_t& count, Vector3*& normalBuffer) const
	{
		count = (uint32_t)p_VertexBuffer->m_Normals.Size();
		normalBuffer = p_VertexBuffer->m_Normals.GetArrayPtr();
	}

	void Segment::GetUVBuffer(uint32_t& count, Vector2*& uvBuffer) const
	{
		count = (uint32_t)p_VertexBuffer->m_TexCoords.Size();
		uvBuffer = p_VertexBuffer->m_TexCoords.GetArrayPtr();
	}

	bool Segment::ContainsWeights() const
	{
		return p_Segment->p_Skin != nullptr;
	}

	bool Segment::GetVertexWeights(uint32_t& count, VertexWeight*& weightBuffer) const
	{
		count = 0;
		weightBuffer = nullptr;

		if (!ContainsWeights())
			return false;

		count = (uint32_t)m_VertexWeights.Size();
		weightBuffer = m_VertexWeights.GetArrayPtr();
		return count > 0;
	}


	String Segment::GetBone() const
	{
		if (p_Segment -> p_Parent != nullptr)
		{
			return p_Segment -> p_Parent -> m_Text;
		}

		return "";
	}


	bool Segment::IsPretransformed() const
	{
		auto flags = p_VertexBuffer -> m_Flags;
		return ((flags & EVBUFFlags::Unknown1) != 0 &&
				(flags & EVBUFFlags::BlendWeight) == 0);
	}
}