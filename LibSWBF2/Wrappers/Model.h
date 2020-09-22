#pragma once
#include "req.h"
#include "Segment.h"
#include "CollisionPrimitive.h"
#include "CollisionMesh.h"

#include "Chunks/LVL/modl/LVL.modl.h"
#include "Chunks/LVL/skel/skel.h"

namespace LibSWBF2::Wrappers
{
	using Types::List;
	using Types::Vector3;
	using Types::Vector4;
	using Chunks::LVL::modl::modl;
	using Chunks::LVL::modl::segm;
	using Chunks::LVL::skel::skel;
	class Level;

	struct LIBSWBF2_API Bone
	{
		String m_BoneName;
		String m_Parent;
		Vector3 m_Position;
		Vector4 m_Rotation;
	};

	class LIBSWBF2_API Model
	{
	private:
		friend Level;
		friend List<Model>;

		Model() = default;
		~Model() = default;

	private:
		modl* p_Model;
		skel* p_Skeleton;
		List<Segment> m_Segments;

		CollisionMesh m_CollisionMesh;
		List<CollisionPrimitive> m_CollisionPrimitives;

	public:
		static bool FromChunk(Level* mainContainer, modl* modelChunk, Model& out);

		const String& GetName() const;
		const List<Segment>& GetSegments() const;
		bool IsSkeletalMesh() const;
		bool GetSkeleton(List<Bone>& bones) const;

		const CollisionMesh& GetCollisionMesh() const;
		List<CollisionPrimitive> GetCollisionPrimitives(ECollisionMaskFlags mask =
															ECollisionMaskFlags::All) const;
	};
}