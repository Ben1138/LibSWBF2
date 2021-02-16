#pragma once
#include "Chunks/LVL/modl/LVL.modl.h"
#include "Types/LibString.h"
#include "Types/List.h"
#include "Material.h"

namespace LibSWBF2::Wrappers
{
	using Types::String;
	using Types::Vector2;
	using Types::Vector3;
	using Chunks::LVL::modl::segm;
	using Chunks::LVL::modl::VBUF;

	class Level;
	class Model;


	#pragma pack(push,1)
	struct LIBSWBF2_API VertexWeight
	{
		float_t m_WeightValue;
		uint8_t m_BoneIndex;
	};
	#pragma pack(pop)

	class LIBSWBF2_API Segment
	{
	private:
		friend Model;
		friend List<Segment>;

		Segment() = default;
		~Segment() = default;

	private:
		segm* p_Segment;
		VBUF* p_VertexBuffer;

		Material m_Material;
		List<VertexWeight> m_VertexWeights;

	public:
		static bool FromChunk(Level* mainContainer, segm* segmentChunk, Segment& out);

		ETopology GetTopology() const;
		bool ContainsWeights() const;

		const Material& GetMaterial() const;

		// count is number of indices, NOT number of bytes!
		void GetIndexBuffer(uint32_t& count, uint16_t*& indexBuffer) const;

		// count is number of vectors, NOT number of bytes!
		void GetVertexBuffer(uint32_t& count, Vector3*& vertexBuffer) const;

		// count is number of vectors, NOT number of bytes!
		void GetNormalBuffer(uint32_t& count, Vector3*& normalBuffer) const;

		// count is number of vectors, NOT number of bytes!
		void GetUVBuffer(uint32_t& count, Vector2*& uvBuffer) const;

		// count corresponmds to number of vertices, NOT number of bytes!
		// returns false if there are no vertex weights present
		bool GetVertexWeights(uint32_t& count, VertexWeight*& weightBuffer) const;

		// returns the skeleton bone this segment belongs to
		String GetBone() const;

		bool IsPretransformed() const;
	};
}