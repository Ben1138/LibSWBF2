#include "stdafx.h"
#include "MODL.h"

namespace LibSWBF2::Chunks::MSH
{
	EModelPurpose MODL::GetPurpose()
	{
		// TODO: Implement own find/starts with methods
		string stdStr = m_Name.m_Text.Buffer();

		if (stdStr.find("lowrez") != string::npos)
		{
			return EModelPurpose::Mesh_Lowrez;
		}

		// check vehicle collision BEFORE regular collision
		if (stdStr.find("v-collision") != string::npos || stdStr.find("p_vehicle") != string::npos)
		{
			return EModelPurpose::Mesh_VehicleCollision;
		}
		else if (stdStr.find("collision") != string::npos)
		{
			return EModelPurpose::Mesh_Collision;
		}

		if (stdStr._Starts_with("sv_"))
		{
			return EModelPurpose::Mesh_ShadowVolume;
		}

		if (stdStr.find("terraincutter") != string::npos)
		{
			return EModelPurpose::Mesh_TerrainCut;
		}

		if (stdStr._Starts_with("p_") || stdStr._Starts_with("c_"))
		{
			return EModelPurpose::Miscellaneous;
		}

		// Sekelton Root and Hard Points sometimes have meshes
		// attached to them (probably for developing purposes)
		// so their Model Type is "Static" and not "Null"
		if (stdStr == "bone_root")
		{
			return EModelPurpose::Skeleton_Root;
		}
		else if (stdStr._Starts_with("hp_"))
		{
			return EModelPurpose::Point_HardPoint;
		}

		if (m_ModelType.m_ModelType == EModelType::Null || m_ModelType.m_ModelType == EModelType::Envelope)
		{
			if (stdStr == "DummyRoot")
			{
				return EModelPurpose::Point_DummyRoot;
			}
			else if (stdStr._Starts_with("root_"))
			{
				return EModelPurpose::Skeleton_BoneRoot;
			}
			else if (stdStr._Starts_with("bone_"))
			{
				return EModelPurpose::Skeleton_BoneLimb;
			}
			else if (stdStr._Starts_with("eff_"))
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
			m_Name.GetDataSize() +
			m_ModelType.GetDataSize() +
			m_ModelIndex.GetDataSize() +
			m_Flags.GetDataSize() +
			m_Transition.GetDataSize() +
			m_CollisionPrimitive.GetDataSize();

		if (m_Parent.m_Text.Length() > 0)
		{
			m_Size += m_Parent.GetDataSize();
		}

		if (m_ModelType.m_ModelType != EModelType::Null)
		{
			m_Size += m_Geometry.GetDataSize();
		}
	}

	void MODL::WriteToStream(FileWriter& stream)
	{
		BaseChunk::WriteToStream(stream);
		m_Name.WriteToStream(stream);
		m_ModelType.WriteToStream(stream);
		m_ModelIndex.WriteToStream(stream);

		if (m_Parent.m_Text.Length() > 0)
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

			if (head == "NAME"_h)
			{
				m_Name.ReadFromStream(stream);
			}
			else if (head == "MTYP"_h)
			{
				m_ModelType.ReadFromStream(stream);
			}
			else if (head == "MNDX"_h)
			{
				m_ModelIndex.ReadFromStream(stream);
			}
			else if (head == "PRNT"_h)
			{
				m_Parent.ReadFromStream(stream);
			}
			else if (head == "FLGS"_h)
			{
				m_Flags.ReadFromStream(stream);
			}
			else if (head == "TRAN"_h)
			{
				m_Transition.ReadFromStream(stream);
			}
			else if (head == "GEOM"_h)
			{
				m_Geometry.ReadFromStream(stream);
			}
			else if (head == "SWCI"_h)
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