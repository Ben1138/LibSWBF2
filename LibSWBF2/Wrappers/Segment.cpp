#include "stdafx.h"
#include "Segment.h"
#include "Material.h"
#include "Level.h"
#include "Types/List.h"
#include "InternalHelpers.h"

namespace LibSWBF2::Wrappers
{
	using Types::List;

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
}