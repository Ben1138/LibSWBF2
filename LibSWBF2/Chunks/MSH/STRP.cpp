#include "stdafx.h"
#include "STRP.h"

namespace LibSWBF2::Chunks::MSH
{
	void STRP::RefreshSize()
	{
		m_Size = (ChunkSize)(sizeof(uint32_t) + m_Triangles.Size() * sizeof(uint16_t));
	}

	void STRP::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		stream.WriteUInt32((uint32_t)m_Triangles.Size());

		for (size_t i = 0; i < m_Triangles.Size(); ++i)
		{
			stream.WriteUInt16(m_Triangles[i]);
		}
	}

	void STRP::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);
		uint32_t numIndices = stream.ReadUInt32();

		m_Triangles.Clear();
		m_Triangles.Resize(numIndices);

		for (uint32_t i = 0; i < numIndices; ++i)
		{
			m_Triangles.Add(stream.ReadUInt16());
		}

		// in some STRP Chunks, there are an additional two bytes (0x00 each)
		// that are NOT included in the overall Chunk size!
		// So lets mark our position and read 16 bits.
		// If it doesn't equal zero, there weren't any additional bytes
		// in the first place and we have to jump back.
		size_t pos = stream.GetPosition();
		if (stream.ReadUInt16() != 0)
		{
			stream.SetPosition(pos);
		}

		BaseChunk::EnsureEnd(stream);
	}

	void STRP::CalcPolygons()
	{
		m_Polygons.Clear();

		// in MSH, polygons are defined as triangle strips.
		// so we have to strip them ourselfs
		// triangles are listed CW CCW CW CCW...

		size_t triCount = 0;
		Polygon poly;
		bool CW = true;

		for (size_t i = 0; i < m_Triangles.Size(); ++i)
		{
			List<uint16_t>& vInd = poly.m_VertexIndices;
			uint16_t vertex = m_Triangles[i];

			// check if highest bit is set
			// two consecutive indices with the highest bit set indicate the start of a triangle strip
			// so lets AND combine this and the next vertex index and check if the highest bit is still set
			if (i+1 < m_Triangles.Size() && (vertex & m_Triangles[i+1]) & 0x8000)
			{
				vInd.Clear();
				triCount = 0;
				CW = true;
			}

			// always get the real vertex index if the high bit is set
			// by applying a respective bitmask
			if ((vertex & 0x8000) != 0)
			{
				vertex &= 0x7FFF;
			}

			vInd.Add(vertex);
			++triCount;

			if (triCount >= 3)
			{
				i -= 2;
				triCount = 0;

				if (!CW)
				{
					// switch vertices if CCW
					uint16_t temp = vInd[vInd.Size() - 1];
					vInd[vInd.Size() - 1] = vInd[vInd.Size() - 3];
					vInd[vInd.Size() - 3] = temp;
				}
				CW = !CW;

				m_Polygons.Add(poly);
				vInd.Clear();
			}
		}
	}
}