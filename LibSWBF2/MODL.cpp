#include "stdafx.h"
#include "MODL.h"

namespace LibSWBF2::Chunks::Mesh
{
	EModelPurpose MODL::GetEstimatedPurpose()
	{
		if (m_Name.m_Text.find("lowrez") != string::npos)
		{
			return EModelPurpose::LowrezMesh;
		}

		// check vehicle collision BEFORE regular collision
		if (m_Name.m_Text.find("v-collision") != string::npos || m_Name.m_Text.find("p_vehicle") != string::npos)
		{
			return EModelPurpose::VehicleCollision;
		}
		else if (m_Name.m_Text.find("collision") != string::npos)
		{
			return EModelPurpose::Collision;
		}

		if (m_Name.m_Text._Starts_with("sv_"))
		{
			return EModelPurpose::ShadowVolume;
		}

		if (m_Name.m_Text.find("terraincutter") != string::npos)
		{
			return EModelPurpose::TerrainCut;
		}

		if (m_Name.m_Text._Starts_with("p_"))
		{
			return EModelPurpose::Miscellaneous;
		}

		// Bones and stuff
		if (m_ModelType.m_ModelType == EModelType::Null || m_ModelType.m_ModelType == EModelType::Envelope)
		{
			if (m_Name.m_Text._Starts_with("hp_"))
			{
				return EModelPurpose::HardPoint;
			}
			else if (m_Name.m_Text._Starts_with("root_"))
			{
				return EModelPurpose::BoneRoot;
			}
			else if (m_Name.m_Text._Starts_with("bone_"))
			{
				return EModelPurpose::BoneLimb;
			}
			else if (m_Name.m_Text._Starts_with("eff_"))
			{
				return EModelPurpose::BoneEnd;
			}

			return EModelPurpose::EmptyTransform;
		}

		return EModelPurpose::RegularMesh;
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

		m_Size =
			m_Name.GetSize() +
			m_ModelType.GetSize() +
			m_ModelIndex.GetSize() +
			m_Flags.GetSize() +
			m_Transition.GetSize();

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
			else
			{
				UnexpectedChunk(stream);
			}
		}

		BaseChunk::EnsureEnd(stream);
	}
}