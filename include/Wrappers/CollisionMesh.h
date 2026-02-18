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
		friend class Model;
		
	private:

		static bool FromChunk(coll *fieldsChunk, CollisionMesh& out);
		
		CollisionMesh(coll *fieldsChunk);
		CollisionMesh(); 

		coll *p_CollisionChunk = nullptr;
		mutable List<uint16_t> m_Indicies;


	public:
		
		String GetName() const;

		void GetIndexBuffer(ETopology requestedTopology, uint32_t& count, uint16_t*& indexBuffer) const;
		void GetVertexBuffer(uint32_t& count, Vector3*& vertexBuffer) const;

		ECollisionMaskFlags GetMaskFlags() const;

		String ToString() const;

		String GetNodeName() const;
	};
}