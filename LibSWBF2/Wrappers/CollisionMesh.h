#pragma once
#include "Chunks/LVL/coll/coll.h"
#include "Chunks/STR.h"

#include "Types/Vector3.h"


namespace LibSWBF2::Wrappers
{
	using namespace LibSWBF2::Chunks::LVL::coll;
	using namespace LibSWBF2::Types;
	using namespace LibSWBF2::Chunks;

	class LIBSWBF2_API CollisionMesh
	{
		friend class Level;
		friend class List<CollisionMesh>;

		CollisionMesh() = default;
		
	private:
		coll *p_CollisionChunk;
		List<uint32_t> m_Indicies;

	public:
		static bool FromChunk(coll *fieldsChunk, CollisionMesh& out);
	
		CollisionMesh(coll *fieldsChunk);

		String GetName() const;

		void GetIndexBuffer(ETopology requestedTopology, uint32_t& count, uint32_t*& indexBuffer);
		void GetVertexBuffer(uint32_t& count, Vector3*& vertexBuffer) const;
		
		String ToString() const;
	};
}