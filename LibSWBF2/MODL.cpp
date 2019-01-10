#include "stdafx.h"
#include "MODL.h"

namespace LibSWBF2::Chunks::Mesh
{
	EModelPurpose MODL::GetEstimatedPurpose()
	{
		if (m_Name.m_Text.find("lowrez") != string::npos)
		{
			return EModelPurpose::Mesh_Lowrez;
		}

		// check vehicle collision BEFORE regular collision
		if (m_Name.m_Text.find("v-collision") != string::npos || m_Name.m_Text.find("p_vehicle") != string::npos)
		{
			return EModelPurpose::Mesh_VehicleCollision;
		}
		else if (m_Name.m_Text.find("collision") != string::npos)
		{
			return EModelPurpose::Mesh_Collision;
		}

		if (m_Name.m_Text._Starts_with("sv_"))
		{
			return EModelPurpose::Mesh_ShadowVolume;
		}

		if (m_Name.m_Text.find("terraincutter") != string::npos)
		{
			return EModelPurpose::Mesh_TerrainCut;
		}

		if (m_Name.m_Text._Starts_with("p_") || m_Name.m_Text._Starts_with("c_"))
		{
			return EModelPurpose::Miscellaneous;
		}

		// Sekelton Root and Hard Points sometimes have meshes
		// attached to them (probably for developing purposes)
		// so their Model Type is "Static" and not "Null"
		if (m_Name.m_Text == "bone_root")
		{
			return EModelPurpose::Skeleton_Root;
		}
		else if (m_Name.m_Text._Starts_with("hp_"))
		{
			return EModelPurpose::Point_HardPoint;
		}

		if (m_ModelType.m_ModelType == EModelType::Null || m_ModelType.m_ModelType == EModelType::Envelope)
		{
			if (m_Name.m_Text == "DummyRoot")
			{
				return EModelPurpose::Point_DummyRoot;
			}
			else if (m_Name.m_Text._Starts_with("root_"))
			{
				return EModelPurpose::Skeleton_BoneRoot;
			}
			else if (m_Name.m_Text._Starts_with("bone_"))
			{
				return EModelPurpose::Skeleton_BoneLimb;
			}
			else if (m_Name.m_Text._Starts_with("eff_"))
			{
				return EModelPurpose::Skeleton_BoneEnd;
			}

			return EModelPurpose::Point_EmptyTransform;
		}

		return EModelPurpose::Mesh_Regular;
	}

	void MODL::RefreshSize()
	{
		m_Name.RefreshSize();
		m_ModelType.RefreshSize();
		m_ModelIndex.RefreshSize();
		m_Parent.RefreshSize();
		m_Flags.RefreshSize();
		m_Transition.RefreshSize();
		m_Geometry.RefreshSize();
		m_CollisionPrimitive.RefreshSize();

		m_Size =
			m_Name.GetSize() +
			m_ModelType.GetSize() +
			m_ModelIndex.GetSize() +
			m_Flags.GetSize() +
			m_Transition.GetSize() +
			m_CollisionPrimitive.GetSize();

		if (m_Parent.m_Text.size() > 0)
		{
			m_Size += m_Parent.GetSize();
		}

		if (m_ModelType.m_ModelType != EModelType::Null)
		{
			m_Size += m_Geometry.GetSize();
		}
	}

	void MODL::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_Name.WriteToStream(stream);
		m_ModelType.WriteToStream(stream);
		m_ModelIndex.WriteToStream(stream);

		if (m_Parent.m_Text.size() > 0)
		{
			m_Parent.WriteToStream(stream);
		}

		m_Flags.WriteToStream(stream);
		m_Transition.WriteToStream(stream);
		
		if (m_ModelType.m_ModelType != EModelType::Null)
		{
			m_Geometry.WriteToStream(stream);
		}

		if (m_CollisionPrimitive.m_PrimitiveType != ECollisionPrimitive::None)
		{
			m_CollisionPrimitive.WriteToStream(stream);
		}
	}

	void MODL::ReadFromStream(FileReader& stream)
	{
		BaseChunk::ReadFromStream(stream);

		while (PositionInChunk(stream.GetPosition()))
		{
			ChunkHeader head = stream.ReadChunkHeader(true);

			if (head == HeaderNames::NAME)
			{
				m_Name.ReadFromStream(stream);
			}
			else if (head == HeaderNames::MTYP)
			{
				m_ModelType.ReadFromStream(stream);
			}
			else if (head == HeaderNames::MNDX)
			{
				m_ModelIndex.ReadFromStream(stream);
			}
			else if (head == HeaderNames::PRNT)
			{
				m_Parent.ReadFromStream(stream);
			}
			else if (head == HeaderNames::FLGS)
			{
				m_Flags.ReadFromStream(stream);
			}
			else if (head == HeaderNames::TRAN)
			{
				m_Transition.ReadFromStream(stream);
			}
			else if (head == HeaderNames::GEOM)
			{
				m_Geometry.ReadFromStream(stream);
			}
			else if (head == HeaderNames::SWCI)
			{
				m_CollisionPrimitive.ReadFromStream(stream);
			}
			else
			{
				SkipChunk(stream);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}
}