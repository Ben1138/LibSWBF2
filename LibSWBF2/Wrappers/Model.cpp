#include "stdafx.h"
#include "Level.h"
#include "InternalHelpers.h"

static LibSWBF2::String empty = "";

namespace LibSWBF2::Wrappers
{
	bool Model::FromChunk(Level* mainContainer, modl* modelChunk, Model& out)
	{
		if (mainContainer == nullptr)
		{
			LOG_ERROR("Given mainContainer was NULL!");
			return false;
		}
		if (modelChunk == nullptr)
		{
			LOG_ERROR("Given modelChunk was NULL!");
			return false;
		}

		out.p_Model = modelChunk;
		out.p_Skeleton = mainContainer->FindSkeleton(out.p_Model->p_Name->m_Text);

		List<segm*>& segments = modelChunk->m_Segments;
		for (size_t i = 0; i < segments.Size(); ++i)
		{
			Segment segment;
			if (Segment::FromChunk(mainContainer, segments[i], segment))
			{
				out.m_Segments.Add(segment);
			}
		}
		return true;
	}

	String Model::GetName() const
	{
		return p_Model->p_Name->m_Text;
	}

	const List<Segment>& Model::GetSegments() const
	{
		return m_Segments;
	}

	bool Model::IsSkeletalMesh() const
	{
		if (p_Skeleton == nullptr)
			return false;

		for (size_t i = 0; i < m_Segments.Size(); ++i)
		{
			if (m_Segments[i].ContainsWeights())
			{
				return true;
			}
		}
		return false;
	}

	bool Model::GetSkeleton(List<Bone>& bones) const
	{
		if (p_Skeleton == nullptr)
			return false;

		uint32_t count = p_Skeleton->p_Info->m_BoneCount;
		List<String>& names = p_Skeleton->p_BoneNames->m_Texts;
		List<String>& parents = p_Skeleton->p_BoneParents->m_Texts;
		List<Matrix3x3>& rotations = p_Skeleton->p_BoneTransforms->m_BoneRotations;
		List<Vector3>& positions = p_Skeleton->p_BoneTransforms->m_BonePositions;

		// there's always one less parent, because root (DummyRoot) doesn't have one =P
		size_t equalParents = parents.Size() + 1;
		if (count != names.Size() || count != equalParents || count != rotations.Size() || count != positions.Size())
		{
			LOG_ERROR(
				"Broken Skeleton! Sizes don't match up!\n"
				"\tCount: {}\n"
				"\tNames: {}\n"
				"\tParents (-1): {}\n"
				"\tRotations: {}\n"
				"\tPositions: {}",
				count,
				names.Size(),
				parents.Size(),
				rotations.Size(),
				positions.Size()
			);
			return false;
		}

		bones.Clear();
		for (size_t i = 0; i < p_Skeleton->p_Info->m_BoneCount; ++i)
		{
			// first entry (root) doesn't have a parent
			bones.Add({ names[i], i > 0 ? parents[i - 1] : empty, positions[i], MatrixToQuaternion(rotations[i]) });
		}
		return true;
	}


	const CollisionMesh& Model::GetCollisionMesh() const
	{
		return m_CollisionMesh;
	}


	List<CollisionPrimitive> Model::GetCollisionPrimitives(ECollisionMaskFlags mask) const
	{
		List<CollisionPrimitive> maskedPrimitives;
		
		for (int i = 0; i < m_CollisionPrimitives.Size(); i++)
		{
			const CollisionPrimitive& curPrimitive = m_CollisionPrimitives[i];

			if ((curPrimitive.GetMaskFlags() & mask) != 0)
			{
				maskedPrimitives.Add(curPrimitive);
			}
		}

		return maskedPrimitives;
	}
}