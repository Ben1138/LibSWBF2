#include "stdafx.h"
#include "Segment.h"
#include "Types\List.h"
#include "Logging\Logger.h";

namespace LibSWBF2::Tools
{
	using Logging::ELogType;
	using Types::List;

	Segment::Segment(segm* SegmentChunk)
	{
		p_Segment = SegmentChunk;
	}

	Segment* Segment::FromChunk(Level* mainContainer, segm* segmentChunk)
	{
		if (segmentChunk == nullptr)
		{
			LOG("Given SegmentChunk was NULL!", ELogType::Error);
			return nullptr;
		}

		List<VBUF*>& vBuffs = segmentChunk->m_VertexBuffers;
		if (vBuffs.Size() == 0)
		{
			LOG("Segment Chunk does not contain any data!", ELogType::Warning);
			return nullptr;
		}

		Segment* result = new Segment(segmentChunk);

		result->p_VertexBuffer = nullptr;
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
				result->p_VertexBuffer = vBuffs[i];
				break;
			}
		}

		if (result->p_VertexBuffer == nullptr)
		{
			result->p_VertexBuffer = vBuffs[0];
		}

		return result;
	}

	void Segment::Destroy(Segment* Segment)
	{
		if (Segment == nullptr)
		{
			LOG("Given Segment was NULL!", ELogType::Error);
			return;
		}

		delete Segment;
	}

	ETopology Segment::GetTopology() const
	{
		return p_Segment->p_Info->m_Topology;
	}

	void Segment::GetIndexBuffer(uint32_t& count, uint16_t*& indexBuffer) const
	{
		count = p_Segment->p_IndexBuffer->m_IndicesCount;
		indexBuffer = p_Segment->p_IndexBuffer->m_Indices.GetArrayPtr();
	}

	void Segment::GetVertexBuffer(uint32_t& count, Vector3*& vertexBuffer) const
	{
		count = p_VertexBuffer->m_Positions.Size();
		vertexBuffer = p_VertexBuffer->m_Positions.GetArrayPtr();
	}

	void Segment::GetNormalBuffer(uint32_t& count, Vector3*& normalBuffer) const
	{
		count = p_VertexBuffer->m_Normals.Size();
		normalBuffer = p_VertexBuffer->m_Normals.GetArrayPtr();
	}

	void Segment::GetUVBuffer(uint32_t& count, Vector2*& uvBuffer) const
	{
		count = p_VertexBuffer->m_TexCoords.Size();
		uvBuffer = p_VertexBuffer->m_TexCoords.GetArrayPtr();
	}
}