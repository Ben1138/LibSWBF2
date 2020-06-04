#pragma once
#include "Chunks\LVL\modl\LVL.modl.h"

namespace LibSWBF2::Tools
{
	using Types::Vector2;
	using Types::Vector3;
	using Chunks::LVL::modl::segm;
	using Chunks::LVL::modl::VBUF;
	class Level;

	class LIBSWBF2_EXP Segment
	{
	private:
		Segment(segm* segment);
		~Segment() = default;

	private:
		segm* p_Segment;
		VBUF* p_VertexBuffer;

	public:
		static Segment* FromChunk(Level* mainContainer, segm* segmentChunk);
		static void Destroy(Segment* segment);

		ETopology GetTopology() const;

		// count is number of indices, NOT number of bytes!
		void GetIndexBuffer(uint32_t& count, uint16_t*& indexBuffer) const;

		// count is number of vectors, NOT number of bytes!
		void GetVertexBuffer(uint32_t& count, Vector3*& vertexBuffer) const;

		// count is number of vectors, NOT number of bytes!
		void GetNormalBuffer(uint32_t& count, Vector3*& normalBuffer) const;

		// count is number of vectors, NOT number of bytes!
		void GetUVBuffer(uint32_t& count, Vector2*& uvBuffer) const;
	};
}